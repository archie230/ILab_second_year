#include "Interpreter.hpp"
#include <cassert>
#include <sstream>

yy::Interpreter::Interpreter(AST::INode* root, SymTbl& symtbl, SymTbl::Table* global_table)
    :
        root_(root),
        symtbl_(symtbl),
        max_recursion_deepness(2500)
{
    // global frame
    env_.push_front(global_table);
    expression_stack_.emplace_front();
}

yy::Interpreter::~Interpreter() {
    std::for_each(instructions_stack_.begin(), instructions_stack_.end(),
    [this] (instruction_t& pair) mutable
    {
        auto node = pair.second;
        switch (node -> GetType()) {
            case T_SCOPEEND:
                delete node;
                if (!funccall_stack_.empty())
                    delete env_.front();
                env_.pop_front();
            break;

            case T_FUNCEND:
                delete node;
                funccall_stack_.pop_front();
                delete env_.front();
                env_.pop_front();
            break;

            case T_RETURNPOINT:
                delete node;
            break;
        }
    });
}

int yy::Interpreter::interpretate() {
    if (!root_)
        return 0;

    instructions_stack_.push_front(std::make_pair(false, root_));

    while (!instructions_stack_.empty()) {
        auto [calculated, node] = instructions_stack_.front();
        instructions_stack_.pop_front();

#ifdef DEBUG
        if(node)
            std::cout << "intterpretating: " << AST::names[node -> GetType()] << " " << std::hex << node << std::dec
                    << " calculated: " << calculated << std::endl;
        else
            std::cout << std::hex << node << std::dec << std::endl;

        if (node && node -> GetType() == T_FUNCCALL)
            std::cout << std::endl << std::endl;

        std::cout << "====ACCUMULATED STACK====" << std::endl;
        for(auto& elem : expression_stack_) {
            for(auto& elem1 : elem.second)
                std::cout << " " << elem1;
            std::cout << std::endl;
        }
#endif

        if (!node) {
            ACCUMULATED_VALS.push_front(0);
            continue;
        }

        switch (node -> GetType()) {

            case T_SCOPE: { 
                auto scopenode = static_cast<AST::ListNode*>(node);
                instructions_stack_.push_front(std::make_pair(false, new AST::INode(T_SCOPEEND)));

                expression_stack_.emplace_front();
                create_frame(scopenode -> GetTable_id(), scopenode);
            }
                break;

            case T_FUNCTION_SCOPE: {
                assert(!funccall_stack_.empty());
                auto funcscopenode = static_cast<AST::ListNode*>(node);

                instructions_stack_.push_front(std::make_pair(false, new AST::INode(T_FUNCEND)));
                create_frame(funcscopenode -> GetTable_id(), funcscopenode);
                assign_function_arguments();
            }
                break;

            case T_STMLST:
            case T_EXPRLIST: {
                auto listnode = static_cast<AST::ListNode *>(node);

                std::for_each(listnode -> rbegin(), listnode -> rend(),
                              [this](AST::INode *node) mutable
                                    { instructions_stack_.push_front(std::make_pair(false, node)); });
            }
                break;

            case T_SCOPEEND: {
                auto retval = ACCUMULATED_VALS.empty() ? 0 : ACCUMULATED_VALS.front();
                delete_frame();
                ACCUMULATED_VALS.push_front(retval);
                delete node;
            }
                break;

            case T_FUNCEND: {
                auto retval = ACCUMULATED_VALS.empty() ? 0 : ACCUMULATED_VALS.front();
                delete_frame();
                ACCUMULATED_VALS.push_front(retval);
                funccall_stack_.pop_front();
                delete node;
            }

            case T_FUNCNAME:
                funccall_stack_.push_front(node);
                if(funccall_stack_.size() > max_recursion_deepness)
                    throw std::runtime_error("max recursion deepness reached!");
                break;

            case T_FUNCCALL: {
                auto funccallnode = static_cast<AST::TwoKidsNode*>(node);
                auto func_decl = static_cast<FuncDec_t*>
                        (env_.front() -> find(GET_ID(funccallnode -> GetLeftKid())));
                assert(func_decl);
                auto funcscope_node = static_cast<AST::ListNode*>(func_decl -> function_body_);

                expression_stack_.emplace_front();

                funccallnode -> GetLeftKid() -> SetType(T_FUNCNAME);

                instructions_stack_.push_front(std::make_pair(false, funcscope_node)); // T_FUNCTION_SCOPE
                instructions_stack_.push_front(std::make_pair(false, funccallnode -> GetLeftKid())); // T_FUNCNAME
                if (funccallnode -> GetRightKid())
                    instructions_stack_.push_front(std::make_pair(false, funccallnode -> GetRightKid())); // expression list
            }
                break;

            case T_IF: {
                auto ifnode = static_cast<AST::IfNode*>(node);

                if (calculated) {
                    assert(!ACCUMULATED_VALS.empty());
                    auto expr = ACCUMULATED_VALS.front();
                    ACCUMULATED_VALS.pop_front();

                    if (expr)
                        instructions_stack_.push_front(std::make_pair(false, ifnode -> GetStmt()));
                    else
                        if (ifnode -> GetElse())
                            instructions_stack_.push_front(std::make_pair(false, ifnode -> GetElse()));
                } else {
                    instructions_stack_.push_front(std::make_pair(true, ifnode));
                    instructions_stack_.push_front(std::make_pair(false, ifnode->GetExpr()));
                }
            }
                break;

            case T_WHILE: {
                auto whilenode = static_cast<AST::TwoKidsNode*>(node);

                if (calculated) {
                    assert(!ACCUMULATED_VALS.empty());
                    auto expr = ACCUMULATED_VALS.front();
                    ACCUMULATED_VALS.pop_front();

                    if (expr) {
                        instructions_stack_.push_front(std::make_pair(false, whilenode));
                        instructions_stack_.push_front(std::make_pair(false, whilenode -> GetRightKid()));
                    }

                } else {
                    instructions_stack_.push_front(std::make_pair(true, whilenode));
                    instructions_stack_.push_front(std::make_pair(false, whilenode->GetLeftKid()));
                }
            }
                break;

            case T_RETURN: {
                auto retnode = static_cast<AST::TwoKidsNode*>(node);

                if (calculated) {
                    assert(!ACCUMULATED_VALS.empty());
                    auto marker = funccall_stack_.empty() ? T_SCOPEEND : T_FUNCEND;

                    auto retval = ACCUMULATED_VALS.front();
                    ACCUMULATED_VALS.pop_front();

                    while (!instructions_stack_.empty())
                    {
                        auto [pop_bool, pop_node] = instructions_stack_.front();
                        if (pop_node) {
                            if (pop_node -> GetType() == marker)
                                break;

                            switch (pop_node -> GetType()) {
                                case T_SCOPEEND:
                                    delete_frame();
                                    delete pop_node;
                                    break;

                                case T_RETURNPOINT:
                                    delete pop_node;
                                    break;
                            }
                        }
                        instructions_stack_.pop_front();
                    }

                    delete_frame();

                    if (marker == T_FUNCEND)
                        funccall_stack_.pop_front();

                    ACCUMULATED_VALS.push_front(retval);
                    delete instructions_stack_.front().second;
                    instructions_stack_.pop_front();

                } else {
                    instructions_stack_.push_front(std::make_pair(true, retnode));
                    instructions_stack_.push_front(std::make_pair(false, retnode->GetRightKid()));
                }
            }
                break;

            case T_OUTPUT: {
                auto outputnode = static_cast<AST::TwoKidsNode *>(node);

                if (calculated) {
                    assert(!ACCUMULATED_VALS.empty());
                    std::cout << ACCUMULATED_VALS.front() << std::endl;
                } else {
                    instructions_stack_.push_front(std::make_pair(true, outputnode));
                    instructions_stack_.push_front(std::make_pair(false, outputnode->GetRightKid()));
                }
            }
                break;

            case T_ASSIGN: {
                auto assign = static_cast<AST::TwoKidsNode *>(node);

                if (calculated) {
                    assert(!ACCUMULATED_VALS.empty());
                    auto lvalue = env_.front()->find(GET_ID(assign->GetLeftKid()));
                    assert(lvalue);

                    static_cast<VarDec_t *>(lvalue)->value_ = ACCUMULATED_VALS.front();
                } else {
                    instructions_stack_.push_front(std::make_pair(true, assign));
                    instructions_stack_.push_front(std::make_pair(false, assign->GetRightKid()));
                }
            }
                break;

            case T_RETURNPOINT: {
                auto call = calc_expression();
                if(call) {
                    // function call or scope in expression
                    instructions_stack_.push_front(std::make_pair(false, new AST::INode(T_RETURNPOINT)));
                    instructions_stack_.push_front(std::make_pair(false, call));
                } else
                    delete node;
            }
                break;

            case T_FUNCDEC:
                break;

            default: {
                postorder_traversing(node);
                auto call = calc_expression();
                if (call) {
                    // function call or scope in expression
                    instructions_stack_.push_front(std::make_pair(false, new AST::INode(T_RETURNPOINT)));
                    instructions_stack_.push_front(std::make_pair(false, call));
                }
            }
                break;
        }
    }
    return 0;
}

static bool has_kid(AST::INode*, char);
static bool is_operator(AST::INode*);
static bool is_unary_operator(AST::INode*);
static int calc_operator(AST::INode*, int, int);
static int calc_operator(AST::INode*, int);

AST::INode* yy::Interpreter::calc_expression() {
    assert(!expression_stack_.empty());

    while(!POSTFIX_NOTATION.empty()) {
        if(is_operator(POSTFIX_NOTATION.front())) {
            auto opertr = POSTFIX_NOTATION.front();
            POSTFIX_NOTATION.pop_front();

            assert(!ACCUMULATED_VALS.empty());
            auto rhs = ACCUMULATED_VALS.front();
            ACCUMULATED_VALS.pop_front();

            if(is_unary_operator(opertr))
                ACCUMULATED_VALS.push_front(calc_operator(opertr, rhs));
            else {
                assert(!ACCUMULATED_VALS.empty());
                auto lhs = ACCUMULATED_VALS.front();
                ACCUMULATED_VALS.pop_front();

                ACCUMULATED_VALS.push_front(calc_operator(opertr, lhs, rhs));
            }
        } else {
            switch(POSTFIX_NOTATION.front() -> GetType()) {
                case T_SCOPE:
                case T_FUNCCALL: {
                    auto scp = POSTFIX_NOTATION.front();
                    POSTFIX_NOTATION.pop_front();
                    return scp;
                }
                default:
                    ACCUMULATED_VALS.push_front(get_value(POSTFIX_NOTATION.front()));
            }
            POSTFIX_NOTATION.pop_front();
        }
    }

    return nullptr;
}

void yy::Interpreter::assign_function_arguments() {
    auto func_decl  =
    static_cast<FuncDec_t*>
        (env_.front() -> find(GET_ID(funccall_stack_.front())));
    assert(func_decl);

    auto& args = func_decl -> arg_names_;

    assert(ACCUMULATED_VALS.size() >= args.size());

#ifdef DEBUG
    std::cout << "function args:";
#endif

    for(const auto& arg : args) {
        auto var = static_cast<VarDec_t*>(env_.front() -> find(arg));
        assert(var);
        var -> value_ = ACCUMULATED_VALS.front();
        ACCUMULATED_VALS.pop_front();

#ifdef DEBUG
        std::cout << " " << var -> value_;
#endif
    }
#ifdef DEBUG
    std::cout << std::endl;
#endif
}

void yy::Interpreter::create_frame(SymTbl::tbl_ident id, AST::ListNode* scopenode) {
    SymTbl::Table* scope_frame = nullptr;

    if (funccall_stack_.empty())
        scope_frame = symtbl_.find_tbl(id);
    else {
        // scope inside function call need new symtbl
        scope_frame = new
                SymTbl::Table(*symtbl_.find_tbl(id)); // DON'T FORGET TO CLEAR MEMORY
        scope_frame -> prev_ = env_.front();
    }

    // creating new frame
    try {
        env_.push_front(scope_frame);
    } catch (...) {
        if (!funccall_stack_.empty())
            delete scope_frame;
        throw;
    }

    try {
        std::for_each(scopenode -> rbegin(), scopenode -> rend(),
          [this](AST::INode *node) mutable
                { instructions_stack_.push_front(std::make_pair(false, node)); });
    } catch (...) {
        if(!funccall_stack_.empty())
            delete env_.front();
        env_.pop_front();
        throw;
    }
}

void yy::Interpreter::delete_frame() {
    if(!funccall_stack_.empty())
        delete env_.front();
    env_.pop_front();
    expression_stack_.pop_front();
}

void yy::Interpreter::postorder_traversing(AST::INode *node) {
    if (!node)
        return;

    // Create first stack; s2 - second stack
    std::deque<AST::INode *> s1;

    // push root to first stack
    s1.push_front(node);

    // Run while first stack is not empty
    while (!s1.empty()) {
        // Pop an item from s1 and push it to s2
        node = s1.front();
        s1.pop_front();

        POSTFIX_NOTATION.push_front(node);

        // Push left and right children
        // of removed item to s1
        if (has_kid(node, 'l'))
            s1.push_front(static_cast<AST::TwoKidsNode *>(node)->GetLeftKid());
        if (has_kid(node, 'r'))
            s1.push_front(static_cast<AST::TwoKidsNode *>(node)->GetRightKid());
    }
}

int yy::Interpreter::get_value(AST::INode* node) {
    switch (node->GetType()) {
        case T_NUM:
            return static_cast<AST::NumNode *>(node)->GetNum();

        case T_ID: {
            auto decl = static_cast<VarDec_t *>(env_.front()->find(GET_ID(node)));
            if (!decl)
                throw std::runtime_error("can't find id in get_value func");
            return decl->value_;
        }

        case T_INPUT: {
            int input = -230;
            std::cin >> input;
            if (!std::cin)
                throw std::runtime_error("bad input");
            return input;
        }

        default: {
            std::stringstream ss;
            ss << "bad node type: " << node->GetType();
            throw std::runtime_error(ss.str());
        }
    }
}

static bool has_kid(AST::INode* node, char side) {
    assert(side == 'l' || side == 'r');

    switch(node -> GetType()) {
        case T_NUM     :
        case T_ID      :
        case T_INPUT   :
        case T_FUNCCALL:
        case T_SCOPE   :
            return false;

        case T_OR      :
        case T_AND     :
        case T_LESS    :
        case T_GR      :
        case T_LESS_EQ :
        case T_GR_EQ   :
        case T_EQUAL   :
        case T_NEQUAL  :
        case T_ADD     :
        case T_SUB     :
        case T_MUL     :
        case T_DIV     :
        case T_OUTPUT  :
        case T_PERCENT :
        case T_EXCLAM  :
            if (side == 'l')
                return static_cast<AST::TwoKidsNode*>(node) -> GetLeftKid() != nullptr;
            else
                return static_cast<AST::TwoKidsNode*>(node) -> GetRightKid() != nullptr;

        default: {
            std::stringstream ss("bad node type: ");
            ss << node -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}

static bool is_operator(AST::INode* node) {
    switch(node -> GetType()) {
        case T_OR      :
        case T_AND     :
        case T_LESS    :
        case T_GR      :
        case T_LESS_EQ :
        case T_GR_EQ   :
        case T_EQUAL   :
        case T_NEQUAL  :
        case T_ADD     :
        case T_SUB     :
        case T_MUL     :
        case T_DIV     :
        case T_PERCENT :
        case T_EXCLAM  :
            return true;

        case T_NUM     :
        case T_ID      :
        case T_INPUT   :
        case T_FUNCCALL:
        case T_SCOPE   :
            return false;

        default: {
            std::stringstream ss;
            ss << "bad node type: " << node -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}

bool is_unary_operator(AST::INode* node) {
    switch(node -> GetType()) {
        case T_ADD     :
        case T_SUB     :
            if (static_cast<AST::TwoKidsNode*>(node) -> GetLeftKid())
                return false;
        case T_EXCLAM  :
            return true;

        case T_MUL     :
        case T_DIV     :
        case T_PERCENT :
        case T_NUM     :
        case T_ID      :
        case T_INPUT   :
        case T_OR      :
        case T_AND     :
        case T_LESS    :
        case T_GR      :
        case T_LESS_EQ :
        case T_GR_EQ   :
        case T_EQUAL   :
        case T_NEQUAL  :
        case T_FUNCCALL:
        case T_SCOPE   :
            return false;

        default: {
            std::stringstream ss;
            ss << "bad node type: " << node -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}

int calc_operator(AST::INode * opertr, int lhs, int rhs) {
    assert(opertr);
    switch(opertr -> GetType()) {
        case T_OR      :
            return lhs || rhs;
        case T_AND     :
            return lhs && rhs;
        case T_LESS    :
            return lhs < rhs;
        case T_GR      :
            return lhs > rhs;
        case T_LESS_EQ :
            return lhs <= rhs;
        case T_GR_EQ   :
            return lhs >= rhs;
        case T_EQUAL   :
            return lhs == rhs;
        case T_NEQUAL  :
            return lhs != rhs;
        case T_ADD     :
            return lhs + rhs;
        case T_SUB     :
            return lhs - rhs;
        case T_MUL     :
            return lhs * rhs;
        case T_DIV     :
            if (rhs == 0) {
                std::cerr << "\tdivision by zero! " << std::endl;
                return INT32_MAX;
            }
            return lhs / rhs;
        case T_PERCENT :
            if (rhs == 0) {
                std::cerr << "\tdivision by zero! " << std::endl;
                return INT32_MAX;
            }
            return lhs % rhs;

        default: {
            std::stringstream ss;
            ss << "bad node type: " << opertr -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}

static int calc_operator(AST::INode *opertr, int rhs) {
    switch(opertr -> GetType()) {
        case T_ADD:
            return rhs;
        case T_SUB:
            return -1 * rhs;
        case T_EXCLAM:
            return !rhs;

        default: {
            std::stringstream ss;
            ss << "bad node type: " << opertr -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}
