#pragma once

#include <FlexLexer.h>
#include <iostream>
#include <cassert>
#include <stack>
#include <sstream>

#include "parser/parser.hh"
#include "AST.hpp"
#include "SymTbl.hpp"
#include "TokenNames.hpp"

namespace yy {

    using token_t = PCL_Parser::token_type;
    using var_t = SymTbl::Table::VarDec;

    /**
     * parsing driver
     */
    struct PCL_Driver final {

        yyFlexLexer                 plex_;
        SymTbl                      symtbl_;
        AST::INode*                 root_;
        uint32_t                    err_counter_;
        SymTbl::tbl_ident           cur_id_;
        std::deque<SymTbl::Table*>  env_;

        explicit PCL_Driver(std::istream* is);

        ~PCL_Driver();

        PCL_Driver(const PCL_Driver&) = delete;

        token_t
        yylex(yy::PCL_Parser::semantic_type* yylval, yy::PCL_Parser::location_type* yylloc);

        int parse();

    };

}