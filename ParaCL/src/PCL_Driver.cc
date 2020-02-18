#include "PCL_Driver.hpp"

yy::PCL_Driver::PCL_Driver(std::istream *is)
        :
        plex_(is),
        symtbl_(),
        root_(nullptr),
        err_counter_(0),
        cur_id_(1),
        top_(nullptr),
        saved_(nullptr)
{
    top_ = new SymTbl::Table(nullptr, 0);
    symtbl_.add_tbl(0, top_);
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
    if(node && err_counter_ == 0)
        interpretate_stmtlst(node);
}

void yy::PCL_Driver::interpretate_stmt(AST::INode *node) {
    assert(node);

    switch(node -> GetType()) {
        case T_IF: {
            auto ifnode = static_cast<AST::IfNode*>(node);
            if(ifnode -> GetKid('r')) {
                // interpretated code
                if (calc_expression(ifnode -> GetKid('l')))
                    interpretate_stmt(ifnode -> GetKid('m'));
                else
                    interpretate_stmt(ifnode -> GetKid('r'));
                //
            } else {
                // interpretated code
                if (calc_expression(ifnode -> GetKid('l')))
                    interpretate_stmt(ifnode -> GetKid('m'));
                //
            }
        } break;

        case T_WHILE: {
            auto whilenode = static_cast<AST::TwoKidsNode*>(node);
            // interpretated code
            while (calc_expression(whilenode -> GetKid('l')))
                interpretate_stmt(whilenode -> GetKid('r'));
            //
        } break;

        case T_OUTPUT: {
            auto prntnode = static_cast<AST::TwoKidsNode*>(node);
            // interpretated code
            std::cout << calc_expression(prntnode -> GetKid('r')) << std::endl;
            //
        } break;

        case T_SCOPE: {
            auto scp_node = static_cast<AST::ListNode*>(node);
            saved_ = top_;
            top_ = symtbl_.find_tbl(scp_node -> GetTable_id());
            interpretate_stmtlst(scp_node);
            top_ = saved_;
        } break;

        case T_STMLST:
            interpretate_stmtlst(node);
            break;

        default:
            calc_expression(node);
    }
}

void yy::PCL_Driver::interpretate_stmtlst(AST::INode *node) {
    assert(node);
    assert(node -> GetType() == T_STMLST || node -> GetType() == T_SCOPE);

    auto lst = static_cast<AST::ListNode*>(node);
    for(int i = 0; i < lst -> size(); ++i)
        interpretate_stmt((*lst)[i]);
}


int yy::PCL_Driver::calc_expression(AST::INode* node) {

    // if node is assign expression then calculate rvalue
    // and put it in lvalue then return
    if(node -> GetType() == T_ASSIGN) {
        AST::INode* left_kid = static_cast<AST::TwoKidsNode*>(node) -> GetKid('l');
        assert(left_kid);
        AST::INode* right_kid = static_cast<AST::TwoKidsNode*>(node) -> GetKid('r');
        assert(right_kid);

        auto* lvalue = top_ -> find(static_cast<AST::IdNode*>(left_kid) -> get_id());
        lvalue -> value_ = calc_expression(right_kid);
        return lvalue -> value_;
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
        std::cout << other.top() -> GetType();
        if(other.top() -> GetType() == T_ID
            || other.top() -> GetType() == T_NUM)
            std::cout << " " << get_value(other.top()) << std::endl;
        else std::cout << std::endl;
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
            accumulated_vals.push(get_value(postfix_notation.top()));
            postfix_notation.pop();
        }
    }

    assert(accumulated_vals.size() == 1);
    return accumulated_vals.top();
}

void yy::PCL_Driver::post_order_trav(AST::INode *node, std::stack<AST::INode*> &s2) {
    if (node == nullptr)
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
            return false;

        default: {
            std::stringstream ss("bad node type: ");
            ss << node -> GetType();
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
            return false;

        default: {
            std::stringstream ss("bad node type: ");
            ss << node -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}

int yy::PCL_Driver::get_value(AST::INode* node) {
    switch(node -> GetType()) {
        case T_NUM:
            return static_cast<AST::NumNode*>(node) -> GetNum();

        case T_ID:
            return top_ -> find(static_cast<AST::IdNode*>(node) -> get_id()) -> value_;

        case T_INPUT: {
            int input = -230;
            std::cin >> input;
            if(!std::cin)
                throw std::runtime_error("bad input");
            return input;
        }

        default: {
            std::stringstream ss("bad node type: ");
            ss << node -> GetType();
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
            return lhs / rhs;
        case T_PERCENT :
            return lhs % rhs;

        default: {
            std::stringstream ss("bad node type: ");
            ss << opertr -> GetType();
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
            std::stringstream ss("bad node type: ");
            ss << opertr -> GetType();
            throw std::runtime_error(ss.str());
        }
    }
}