#include "Interpreter.hpp"
#include <cassert>
#include <sstream>
#include <memory>

yy::Interpreter::Interpreter(AST::INode* root, SymTbl& symtbl, SymTbl::Table* global_table)
    :
        root_(root),
        symtbl_(symtbl),
        max_funccall_stack_sz(MAX_FUNCCALL_STACK_SIZE)
{
    // global scope frame
    env_.emplace_front(false, global_table);
    // creating global expression frame in-place
    expression_stack_.emplace_front();
}

yy::Interpreter::~Interpreter() {
    std::transform(instructions_stack_.begin(), instructions_stack_.end(), instructions_stack_.begin(),
            [] (const instruction_t& pair) -> instruction_t
    {
        auto node = pair.second;
        if (node) {
            switch (node->GetType()) {
                case T_SCOPEEND:
                    [[fallthrough]];
                case T_FUNCEND:
                    [[fallthrough]];
                case T_RETURNPOINT:
                    delete node;
                    break;
            }
        }
        return {false, nullptr};
    });

    std::transform(env_.begin(), env_.end(), env_.begin(),
            [] (scope_t& pair) -> scope_t
    {
        if (pair.first)
            delete pair.second;
        return {false, nullptr};
    });
}

int yy::Interpreter::interpretate() {
    if (!root_)
        return 0;

    instructions_stack_.emplace_front(false, root_);

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

            case T_SCOPE: 
                interpretate_T_SCOPE(node);
                break;

            case T_FUNCTION_SCOPE: 
                interpretate_T_FUNCTION_SCOPE(node);
                break;

            case T_STMLST:
                [[fallthrough]];
            case T_EXPRLIST: 
                interpretate_T_EXPRLIST(node);
                break;

            case T_SCOPEEND: 
                interpretate_T_SCOPEEND(node);
                break;

            case T_FUNCEND:
                interpretate_T_SCOPEEND(node);
                funccall_stack_.pop_front();
                break;


            case T_FUNCNAME:
                interpretate_T_FUNCNAME(node);
                break;

            case T_FUNCCALL:
                interpretate_T_FUNCCALL(node);
                break;

            case T_IF:
                interpretate_T_IF(calculated, node);
                break;

            case T_WHILE:
                interpretate_T_WHILE(calculated, node);
                break;

            case T_RETURN:
                interpretate_T_RETURN(calculated, node);
                break;

            case T_OUTPUT:
                interpretate_T_OUTPUT(calculated, node);
                break;

            case T_ASSIGN:
                interpretate_T_ASSIGN(calculated, node);
                break;

            case T_RETURNPOINT:
                interpretate_T_RETURNPOINT(node);
                break;

            case T_FUNCDEC:
                break;

            default: {
                postorder_traversing(node);
                auto call = calc_expression();
                if (call) {
                    // function call or scope in expression
                    instructions_stack_.emplace_front(false, new AST::INode(T_RETURNPOINT));
                    instructions_stack_.emplace_front(false, call);
                }
            }
                break;
        }
    }
    return 0;
}

static bool has_left_kid(AST::INode*);
static bool has_right_kid(AST::INode*);
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
        (env_.front().second -> find(GET_ID(funccall_stack_.front())));
    assert(func_decl);

    auto& args = func_decl -> arg_names_;

    assert(ACCUMULATED_VALS.size() >= args.size());

#ifdef DEBUG
    std::cout << "function args:";
#endif

    for(const auto& arg : args) {
        auto var = static_cast<VarDec_t*>(env_.front().second -> find(arg));
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
    bool allocated = false;
    SymTbl::Table* scope_frame = nullptr;
    std::unique_ptr<SymTbl::Table> scope_frame_ptr;

    if (funccall_stack_.empty())
        scope_frame = symtbl_.find_tbl(id);
    else {
        // scope inside function call need new symtbl
        scope_frame = new
                SymTbl::Table(*symtbl_.find_tbl(id));
        allocated = true;
        scope_frame -> prev_ = env_.front().second;
        scope_frame_ptr = std::unique_ptr<SymTbl::Table>(scope_frame);
    }

    auto fi = std::front_inserter(instructions_stack_);
    std::transform(scopenode -> rbegin(), scopenode -> rend(), fi, 
    [] (AST::INode* node) -> instruction_t { return {false, node}; });

    env_.emplace_front(allocated, scope_frame);

    scope_frame_ptr.release();
}

void yy::Interpreter::delete_frame() noexcept {
    if(env_.front().first)
        delete env_.front().second;
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
        if (has_left_kid(node))
            s1.push_front(static_cast<AST::TwoKidsNode *>(node)->GetLeftKid());
        if (has_right_kid(node))
            s1.push_front(static_cast<AST::TwoKidsNode *>(node)->GetRightKid());
    }
}

int yy::Interpreter::get_value(AST::INode* node) const {
    switch (node->GetType()) {
        case T_NUM:
            return static_cast<AST::NumNode *>(node)->GetNum();

        case T_ID: {
            auto decl = static_cast<VarDec_t *>(env_.front().second->find(GET_ID(node)));
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

void yy::Interpreter::interpretate_T_SCOPE(AST::INode* node) {
    auto scopenode = static_cast<AST::ListNode*>(node);
    instructions_stack_.emplace_front(false, new AST::INode(T_SCOPEEND));

    // creating new expression frame in-place
    expression_stack_.emplace_front();

    // creating new scope frame
    create_frame(scopenode -> GetTable_id(), scopenode);
}

void yy::Interpreter::interpretate_T_FUNCTION_SCOPE(AST::INode* node) {
    assert(!funccall_stack_.empty());
    auto funcscopenode = static_cast<AST::ListNode*>(node);

    instructions_stack_.emplace_front(false, new AST::INode(T_FUNCEND));

    // expression frame already created at T_FUNCCALL

    create_frame(funcscopenode -> GetTable_id(), funcscopenode);

    assign_function_arguments();
}

void yy::Interpreter::interpretate_T_EXPRLIST(AST::INode* node) {
    auto listnode = static_cast<AST::ListNode *>(node);
    auto fi = std::front_inserter(instructions_stack_);
    std::transform(listnode -> rbegin(), listnode -> rend(), fi,
                   [] (AST::INode* node) -> instruction_t { return {false, node}; });
}

void yy::Interpreter::interpretate_T_SCOPEEND(AST::INode* node) {
    auto retval = ACCUMULATED_VALS.empty() ? 0 : ACCUMULATED_VALS.front();
    delete_frame();
    ACCUMULATED_VALS.push_front(retval);
    delete node;
}

void yy::Interpreter::interpretate_T_FUNCNAME(AST::INode* node) {
    funccall_stack_.push_front(node);
    if(funccall_stack_.size() > max_funccall_stack_sz)
        throw std::runtime_error("max function call stack size reached!");
}

void yy::Interpreter::interpretate_T_FUNCCALL(AST::INode* node) {
    auto funccallnode = static_cast<AST::TwoKidsNode*>(node);

    auto func_decl = static_cast<FuncDec_t*>
    (env_.front().second -> find(GET_ID(funccallnode -> GetLeftKid())));
    assert(func_decl);

    auto funcscope_node = func_decl -> function_body_;
    assert(funcscope_node);

    // creating new expression frame in-place
    expression_stack_.emplace_front();

    funccallnode -> GetLeftKid() -> SetType(T_FUNCNAME);

    instructions_stack_.emplace_front(false, funcscope_node); // T_FUNCTION_SCOPE
    instructions_stack_.emplace_front(false, funccallnode -> GetLeftKid()); // T_FUNCNAME
    if (funccallnode -> GetRightKid())
        instructions_stack_.emplace_front(false, funccallnode -> GetRightKid()); // expression list
}

void yy::Interpreter::interpretate_T_IF(bool calculated, AST::INode* node) {
    auto ifnode = static_cast<AST::IfNode*>(node);

    if (calculated) {
        assert(!ACCUMULATED_VALS.empty());
        auto expr = ACCUMULATED_VALS.front();
        ACCUMULATED_VALS.pop_front();

        if (expr)
            instructions_stack_.emplace_front(false, ifnode -> GetStmt());
        else
        if (ifnode -> GetElse())
            instructions_stack_.emplace_front(false, ifnode -> GetElse());
    } else {
        instructions_stack_.emplace_front(true, ifnode);
        instructions_stack_.emplace_front(false, ifnode->GetExpr());
    }
}

void yy::Interpreter::interpretate_T_WHILE(bool calculated, AST::INode* node) {
    auto whilenode = static_cast<AST::TwoKidsNode*>(node);

    if (calculated) {
        assert(!ACCUMULATED_VALS.empty());
        auto expr = ACCUMULATED_VALS.front();
        ACCUMULATED_VALS.pop_front();

        if (expr) {
            instructions_stack_.emplace_front(false, whilenode);
            instructions_stack_.emplace_front(false, whilenode -> GetRightKid());
        }

    } else {
        instructions_stack_.emplace_front(true, whilenode);
        instructions_stack_.emplace_front(false, whilenode->GetLeftKid());
    }
}

void yy::Interpreter::interpretate_T_RETURN(bool calculated, AST::INode* node) {
    auto retnode = static_cast<AST::TwoKidsNode*>(node);

    if (calculated) {
        assert(!ACCUMULATED_VALS.empty());
        auto marker = funccall_stack_.empty() ? T_SCOPEEND : T_FUNCEND;

        auto retval = ACCUMULATED_VALS.front();
        ACCUMULATED_VALS.pop_front();


        auto marker_it = std::find_if(instructions_stack_.begin(), instructions_stack_.end(),
              [this, marker] (const instruction_t& instruction) mutable
              {
                  auto [pop_bool, pop_node] = instruction;
                  if (pop_node) {
                      auto type = pop_node -> GetType();
                      switch (type) {
                          case T_FUNCEND:
                              delete_frame();
                              delete pop_node;
                              funccall_stack_.pop_front();
                              break;

                          case T_SCOPEEND:
                              delete_frame();
                              delete pop_node;
                              break;

                          case T_RETURNPOINT:
                              delete pop_node;
                              break;
                      }
                      return type == marker;
                  }
                  return false;
              });

        assert(marker_it != instructions_stack_.end());
        instructions_stack_.erase(instructions_stack_.begin(), std::next(marker_it));

        ACCUMULATED_VALS.push_front(retval);

    } else {
        instructions_stack_.emplace_front(true, retnode);
        instructions_stack_.emplace_front(false, retnode->GetRightKid());
    }
}

void yy::Interpreter::interpretate_T_OUTPUT(bool calculated, AST::INode* node) {
    auto outputnode = static_cast<AST::TwoKidsNode *>(node);

    if (calculated) {
        assert(!ACCUMULATED_VALS.empty());
        std::cout << ACCUMULATED_VALS.front() << std::endl;
    } else {
        instructions_stack_.emplace_front(true, outputnode);
        instructions_stack_.emplace_front(false, outputnode->GetRightKid());
    }
}

void yy::Interpreter::interpretate_T_ASSIGN(bool calculated, AST::INode* node) {
    auto assign = static_cast<AST::TwoKidsNode *>(node);

    if (calculated) {
        assert(!ACCUMULATED_VALS.empty());
        auto lvalue = env_.front().second->find(GET_ID(assign->GetLeftKid()));
        assert(lvalue);

        static_cast<VarDec_t *>(lvalue)->value_ = ACCUMULATED_VALS.front();
    } else {
        instructions_stack_.emplace_front(true, assign);
        instructions_stack_.emplace_front(false, assign->GetRightKid());
    }
}

void yy::Interpreter::interpretate_T_RETURNPOINT(AST::INode* node) {
    auto call = calc_expression();
    if(call) {
        // function call or scope in expression
        instructions_stack_.emplace_front(false, new AST::INode(T_RETURNPOINT));
        instructions_stack_.emplace_front(false, call);
    } else
        delete node;
}

static bool has_left_kid(AST::INode* node) {
    assert(node);

    if (is_operator(node)) {
        return static_cast<AST::TwoKidsNode*>(node) -> GetLeftKid() != nullptr;
    } else {
        // keep in mind that print is statement
        if (node -> GetType() == T_OUTPUT)
            return static_cast<AST::TwoKidsNode*>(node) -> GetLeftKid() != nullptr;
        return false;
    }
}

static bool has_right_kid(AST::INode* node) {
    assert(node);

    if (is_operator(node)) {
        return static_cast<AST::TwoKidsNode*>(node) -> GetRightKid() != nullptr;
    } else {
        // keep in mind that print is statement
        if (node -> GetType() == T_OUTPUT)
            return static_cast<AST::TwoKidsNode*>(node) -> GetRightKid() != nullptr;
        return false;
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
    if (!is_operator(node))
        return false;

    switch(node -> GetType()) {
        case T_ADD     :
            [[fallthrough]];
        case T_SUB     :
            if (static_cast<AST::TwoKidsNode*>(node) -> GetLeftKid())
                return false;
        case T_EXCLAM  :
            return true;
    }

    return false;
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
