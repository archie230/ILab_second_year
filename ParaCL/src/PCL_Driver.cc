#include "PCL_Driver.hpp"

yy::PCL_Driver::PCL_Driver(std::istream *is)
        :
        plex_(is),
        symtbl_(),
        root_(nullptr),
        err_counter_(0),
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
    auto tt = static_cast<token_t>(plex_.yylex());
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