#include "PCL_Driver.hpp"

yy::PCL_Driver::PCL_Driver(std::istream *is)
        :
        plex_(is),
        symtbl_(),
        root_(nullptr),
        err_counter_(0),
        recursion_deepness_(0),
        cur_id_(1),
        env_()
{
    env_.push_front(new SymTbl::Table(nullptr, 0));
    symtbl_.add_tbl(0, env_.front());
}

yy::PCL_Driver::~PCL_Driver() {
    delete root_;
}

yy::token_t yy::PCL_Driver::yylex(yy::PCL_Parser::semantic_type *yylval, yy::PCL_Parser::location_type *yylloc) {
    token_t tt = static_cast<token_t>(plex_.yylex());
    *yylloc = plex_.lineno();

    while(tt == token_t::TERR) {
        std::cerr << "  error: unknown symbol: " << plex_.YYText()[0]
                  << " at line: " << *yylloc << std::endl;
        ++err_counter_;
        tt = static_cast<token_t>(plex_.yylex());
    }

    switch(tt) {
        case token_t::TNUM: {
            int val = 0; // in current version all numbers are integers

            try {
                val = std::stoi(std::string(plex_.YYText(), plex_.YYLeng()));
            } catch(std::out_of_range&) {
                std::cerr << "  error: line: " << *yylloc << " integer overflow: "
                          << plex_.YYText() << std::endl;
                ++err_counter_;
                *yylval = nullptr;
                break;
            }

            *yylval = new AST::NumNode(TokenName::T_NUM, val);
            break;
        }

        case token_t::TID:
            *yylval = new AST::IdNode(T_ID, std::string(plex_.YYText(), plex_.YYLeng()));
            break;

        default:
            *yylval = nullptr;
    }
    return tt;
}

int yy::PCL_Driver::parse() {
    PCL_Parser parser(this);
    return parser.parse();
}

void yy::PCL_Driver::interpretate(AST::INode* node) {
    if (err_counter_ != 0)
        return;

    if (env_.size() != 1) // only global scope is in deque
        throw std::runtime_error("expected env_ size == 1");

    if (node) {
        auto lst = static_cast<AST::ListNode*>(node);
        for(int i = 0; i < lst -> size(); ++i)
            interpretate_stmt((*lst)[i]);
    }
}

std::pair<bool, int> yy::PCL_Driver::interpretate_stmt(AST::INode *node) {
    // empty scope came as expression
    if(!node)
        return {false, 0};

    switch(node -> GetType()) {

        case T_IF: {
            auto ifnode = static_cast<AST::IfNode*>(node);
            if(ifnode -> GetKid('r')) {
                // interpretated code
                if (calc_expression(ifnode -> GetKid('l'))) {
                    if( (ifnode -> GetKid('m')) && (ifnode -> GetKid('m') -> GetType() == T_SCOPE) ){
                        auto [first, second] = calc_scope(ifnode -> GetKid('m'));
                        if(first)
                            return {true, second};
                    } else {
                        auto [first, second] = interpretate_stmt(ifnode -> GetKid('m'));
                        if(first)
                            return {true, second};
                    }
                } else {
                    if( (ifnode -> GetKid('r')) && (ifnode -> GetKid('r') -> GetType() == T_SCOPE) ){
                        auto [first, second] = calc_scope(ifnode -> GetKid('r'));
                        if(first)
                            return {true, second};
                    } else {
                        if(ifnode) {
                            auto [first, second] = interpretate_stmt(ifnode -> GetKid('r'));
                            if(first)
                                return {true, second};
                        }
                    }
                }
                //
            } else {
                // interpretated code
                if (calc_expression(ifnode -> GetKid('l'))) {
                    if( (ifnode -> GetKid('m')) && (ifnode -> GetKid('m') -> GetType() == T_SCOPE) ){
                        auto [first, second] = calc_scope(ifnode -> GetKid('m'));
                        if(first)
                            return {true, second};
                    } else {
                        auto [first, second] = interpretate_stmt(ifnode -> GetKid('m'));
                        if(first)
                            return {true, second};
                    }
                }
                //
            }
            return {false, 0};
        }

        case T_WHILE: {
            auto whilenode = static_cast<AST::TwoKidsNode*>(node);
            // interpretated code
            while ( calc_expression(whilenode -> GetKid('l')) ) {
                if( (whilenode -> GetKid('r')) && (whilenode -> GetKid('r') -> GetType() == T_SCOPE) ){
                    auto [first, second] = calc_scope(whilenode -> GetKid('r'));
                    if(first)
                        return {true, second};
                } else {
                    if(whilenode) {
                        auto [first, second] = interpretate_stmt(whilenode -> GetKid('r'));
                        if(first)
                            return {true, second};
                    }
                }
            }
            //
            return {false, 0};
        }

        case T_OUTPUT: {
            auto printnode = static_cast<AST::TwoKidsNode*>(node);
            // interpretated code
            std::cout << calc_expression(printnode -> GetKid('r')) << std::endl;
            //
            return {false, 0};
        }

        case T_RETURN: {
            auto returnnode = static_cast<AST::TwoKidsNode*>(node);
            return {true, calc_expression(returnnode -> GetKid('r'))};
        }

        case T_FUNCDEC:
            return {false, 0};

        default:
            return {false, calc_expression(node)};
    }
}

int yy::PCL_Driver::calc_expression(AST::INode* node) {
    // if node is assign expression then calculate rvalue
    // and put it in lvalue then return
    if(!node)
        return 0; // empty scope case

    switch (node -> GetType()) {
        case T_ASSIGN: {
            AST::INode* left_kid = static_cast<AST::TwoKidsNode*>(node) -> GetKid('l');
            assert(left_kid);
            AST::INode* right_kid = static_cast<AST::TwoKidsNode*>(node) -> GetKid('r');

            auto lvalue = env_.front() -> find(GET_ID(left_kid));
            assert(lvalue);
            assert(lvalue -> type_ != FUNC);
            static_cast<VarDec_t*>(lvalue) -> value_ = calc_expression(right_kid);
            return static_cast<VarDec_t*>(lvalue) -> value_;
        }

        case T_FUNCCALL:
            return calc_function(node);

        case T_SCOPE:
            return (calc_scope(node)).second;
    }


    std::stack<AST::INode*> postfix_notation;
    std::stack<int>         accumulated_vals;
    int lhs;
    int rhs;
    AST::INode* opertr;

    post_order_trav(node, postfix_notation);

#ifdef DEBUG
    std::stack<AST::INode*> other(postfix_notation);
    std::cout << "post order:" << std::endl;
    while(!other.empty()) {
        other.top() -> print(); std::cout << std::endl;
        other.pop();
    }
    std::cout << std::endl;
    //!
#endif


    while(!postfix_notation.empty()) {
        if(is_operator(postfix_notation.top())) {
            opertr = postfix_notation.top();
            postfix_notation.pop();

            assert(!accumulated_vals.empty());
            rhs = accumulated_vals.top();
            accumulated_vals.pop();

            if(is_unary_operator(opertr))
                accumulated_vals.push(calc_operator(opertr, rhs));
            else {
                assert(!accumulated_vals.empty());
                lhs = accumulated_vals.top();
                accumulated_vals.pop();

                accumulated_vals.push(calc_operator(opertr, lhs, rhs));
            }
        } else {
            switch(postfix_notation.top() -> GetType()) {
                case T_SCOPE:
                case T_FUNCCALL:
                    accumulated_vals.push(calc_expression(postfix_notation.top()));
                    break;
                default:
                    accumulated_vals.push(get_value(postfix_notation.top()));
            }
            postfix_notation.pop();
        }
    }

    assert(accumulated_vals.size() == 1);
    return accumulated_vals.top();
}

std::pair<bool, int> yy::PCL_Driver::calc_scope(AST::INode *node) {
    if(!node)
        return {false, 0};

    assert(node && node -> GetType() == T_SCOPE);

    auto scope_node = static_cast<AST::ListNode*>(node);
    std::pair<bool, int> return_val;

    SymTbl::Table* scope_frame = nullptr;
    if(recursion_deepness_ == 0)
        scope_frame = symtbl_.find_tbl(scope_node -> GetTable_id());
    else {
        scope_frame = new SymTbl::Table(*symtbl_.find_tbl(scope_node -> GetTable_id()));
        scope_frame -> prev_ = env_.front();
    }

    env_.push_front(scope_frame);

    try {
        for(int i  = 0; i < scope_node -> size(); i++) {
            return_val = interpretate_stmt((*scope_node)[i]);
            if (return_val.first) {
                if(recursion_deepness_ != 0)
                    delete scope_frame;
                break;
            }
        }

        env_.pop_front();

        if(recursion_deepness_ != 0)
            delete scope_frame;
    } catch(...) {
        if(recursion_deepness_ != 0)
            delete scope_frame;
        throw;
    }
    return {return_val.first, return_val.second};
}

int yy::PCL_Driver::calc_function(AST::INode *node) {
    assert(node && node -> GetType() == T_FUNCCALL);

    auto function_node  = static_cast<AST::TwoKidsNode*>(node);
    auto expr_lst       = static_cast<AST::ListNode*>(function_node -> GetKid('r'));
    auto func_decl      = static_cast<FuncDec_t*>( env_.front() -> find(GET_ID(function_node -> GetKid('l'))) );
    auto& args          = func_decl -> arg_names_;

    assert(args.size() == (expr_lst ? expr_lst -> size() : 0));

    auto function_frame = new SymTbl::Table(*symtbl_.find_tbl(func_decl -> tbl_id_));
    ++recursion_deepness_;

    try {

        for(int i = 0; i < args.size(); i++) {
            auto var = static_cast<VarDec_t*>(function_frame -> find(args[i]));
            var -> value_ = calc_expression((*expr_lst)[i]);
        }

        env_.push_front(function_frame);
        std::pair<bool, int> return_val(false, 0);

        if (func_decl -> function_body_) {
            auto scope_node = static_cast<AST::ListNode*>(func_decl -> function_body_);
            for(int i  = 0; i < scope_node ->  size(); i++) {
                return_val = interpretate_stmt((*scope_node)[i]);
                if (return_val.first)
                    break;
            }
        }

        env_.pop_front();

        delete function_frame;

        --recursion_deepness_;
        return return_val.second;
    } catch(...) {
        delete function_frame;
        throw;
    }
}

// post order expression sub tree traversing
// if node is SCOPE or FUNCCALL then subtree doesn't traversing
// check function has_kid
void yy::PCL_Driver::post_order_trav(AST::INode *node, std::stack<AST::INode*> &s2) {
    if (!node)
        return;

    // Create first stack; s2 - second stack
    std::stack<AST::INode*> s1;

    // push root to first stack
    s1.push(node);

    // Run while first stack is not empty
    while (!s1.empty()) {
        // Pop an item from s1 and push it to s2
        node = s1.top();
        s1.pop();
        s2.push(node);

        // Push left and right children
        // of removed item to s1
        if (has_kid(node, 'l'))
            s1.push(static_cast<AST::TwoKidsNode*>(node) -> GetKid('l'));
        if (has_kid(node, 'r'))
            s1.push(static_cast<AST::TwoKidsNode*>(node) -> GetKid('r'));
    }
}

// all predicates and "int return" functions lower
// expect that they have node that used in expressions(except assign node)
// otherwise they throw runtime_error

bool yy::PCL_Driver::has_kid(AST::INode* node, char side) {
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
            return static_cast<AST::TwoKidsNode*>(node) -> GetKid(side) != nullptr;

        default: {
            std::stringstream ss("bad node type: ");
            ss << node -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}

bool yy::PCL_Driver::is_operator(AST::INode* node) {
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

bool yy::PCL_Driver::is_unary_operator(AST::INode *node) {
    switch(node -> GetType()) {
        case T_ADD     :
        case T_SUB     :
            if(static_cast<AST::TwoKidsNode*>(node) -> GetKid('l'))
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

int yy::PCL_Driver::get_value(AST::INode* node) {
    switch(node -> GetType()) {
        case T_NUM:
            return static_cast<AST::NumNode*>(node) -> GetNum();

        case T_ID: {
            auto decl = static_cast<VarDec_t*>(env_.front() -> find(GET_ID(node)));
            if(!decl)
                throw std::runtime_error("can't find id in get value func");
            return decl -> value_;
        }

        case T_INPUT: {
            int input = -230;
            std::cin >> input;
            if(!std::cin)
                throw std::runtime_error("bad input");
            return input;
        }

        default: {
            std::stringstream ss;
            ss << "bad node type: " << node -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}

// binary operator calculator
int yy::PCL_Driver::calc_operator(AST::INode *opertr, int lhs, int rhs) {
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

// unary operator calculator
// only unary operators allowed
int yy::PCL_Driver::calc_operator(AST::INode *opertr, int rhs) {
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