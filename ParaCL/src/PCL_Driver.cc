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
            *yylval = new AST::IdNode(T_ID, new std::string(plex_.YYText(), plex_.YYLeng()));
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

int yy::PCL_Driver::interpretate(AST::INode *node) {

    assert(node);
    switch(node -> GetType()) {

        case T_SCOPE:
            saved_ = top_;
            top_ = symtbl_.find_tbl(static_cast<AST::ListNode*>(node) -> GetTable_id());
        case T_STMLST: {
            auto* lst_node = static_cast<AST::ListNode*>(node);
            for(int i = 0; i < lst_node -> size(); i++) {
                interpretate((*lst_node)[i]);
            }
            if(lst_node -> GetType() == T_SCOPE)
                top_ = saved_;
        }   break;

        case T_ASSIGN: {
            auto* asgn_node = static_cast<AST::_2kidsNode*>(node);
            auto* id_node = static_cast<AST::IdNode*>(asgn_node -> GetKid('l'));
            assert(id_node);
            var_t* var = top_ -> find(*(id_node -> get_id()));
            assert(var);
            assert(asgn_node -> GetKid('r'));
            var -> value_ = interpretate(asgn_node -> GetKid('r'));
        }   break;

        case T_OUTPUT:
            assert(static_cast<AST::_2kidsNode*>(node) -> GetKid('r'));
            std::cout << interpretate(static_cast<AST::_2kidsNode*>(node) -> GetKid('r')) << std::endl;
            break;

        case T_NUM:
            return static_cast<AST::NumNode*>(node) -> GetNum();

        case T_ID: {
            auto* id_node = static_cast<AST::IdNode*>(node);
            var_t* var = top_ -> find(*(id_node -> get_id()));
            assert(var);
            return var -> value_;
        }

        case T_WHILE: {
            auto* while_node = static_cast<AST::_2kidsNode*>(node);
            assert(while_node -> GetKid('l'));
            assert(while_node -> GetKid('r'));

            while(interpretate(while_node -> GetKid('l')))
                interpretate(while_node -> GetKid('r'));
        }   break;

        case T_IF: {
            auto* if_node = static_cast<AST::_2kidsNode*>(node);
            assert(if_node -> GetKid('l'));
            assert(if_node -> GetKid('r'));

            if(interpretate(if_node -> GetKid('l')))
                interpretate(if_node -> GetKid('r'));
        }   break;

            // binary operators except + and -
        case T_OR:
        case T_AND:
        case T_LESS:
        case T_GR:
        case T_LESS_EQ:
        case T_GR_EQ:
        case T_EQUAL:
        case T_NEQUAL:
        case T_MUL:
        case T_DIV:
        {
            auto* binary_node = static_cast<AST::_2kidsNode*>(node);
            assert(binary_node -> GetKid('l'));
            assert(binary_node -> GetKid('r'));

            switch(binary_node -> GetType()) {
                case T_OR:
                    return interpretate(binary_node -> GetKid('l'))
                           || interpretate(binary_node -> GetKid('r'));
                case T_AND:
                    return interpretate(binary_node -> GetKid('l'))
                           && interpretate(binary_node -> GetKid('r'));
                case T_LESS:
                    return interpretate(binary_node -> GetKid('l'))
                           < interpretate(binary_node -> GetKid('r'));
                case T_GR:
                    return interpretate(binary_node -> GetKid('l'))
                           > interpretate(binary_node -> GetKid('r'));
                case T_LESS_EQ:
                    return interpretate(binary_node -> GetKid('l'))
                           <= interpretate(binary_node -> GetKid('r'));
                case T_GR_EQ:
                    return interpretate(binary_node -> GetKid('l'))
                           >= interpretate(binary_node -> GetKid('r'));
                case T_EQUAL:
                    return interpretate(binary_node -> GetKid('l'))
                           == interpretate(binary_node -> GetKid('r'));
                case T_NEQUAL:
                    return interpretate(binary_node -> GetKid('l'))
                           != interpretate(binary_node -> GetKid('r'));
                case T_MUL:
                    return interpretate(binary_node -> GetKid('l'))
                           * interpretate(binary_node -> GetKid('r'));
                case T_DIV:
                    return interpretate(binary_node -> GetKid('l'))
                           / interpretate(binary_node -> GetKid('r'));
            }
        }

        case T_ADD:
        case T_SUB:
        {
            auto* binary_node = static_cast<AST::_2kidsNode*>(node);
            assert(binary_node -> GetKid('r'));

            if(binary_node -> GetKid('l')) {
                if (binary_node->GetType() == T_ADD)
                    return interpretate(binary_node->GetKid('l')) +
                           interpretate(binary_node->GetKid('r'));
                else
                    return interpretate(binary_node->GetKid('l')) -
                           interpretate(binary_node->GetKid('r'));
            } else {
                if (binary_node->GetType() == T_ADD)
                    return interpretate(binary_node->GetKid('r'));
                else
                    return 1 * interpretate(binary_node->GetKid('r'));
            }
        }

        case T_INPUT: {
            int input_var = 0;
            std::cin >> input_var;

            if(!std::cin)
                std::cerr << "bad data!" << std::endl;

            return input_var;
        }
    }
    return 0;
}
