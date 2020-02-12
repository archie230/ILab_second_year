#pragma once

#include <FlexLexer.h>
#include <iostream>
#include <cassert>
#include "parser/parser.hh"
#include "AST.hpp"
#include "SymTbl.hpp"
#include "TokenNames.hpp"

namespace yy {

using token_t = PCL_Parser::token_type;
using var_t = SymTbl::Table::VarDec;

    struct PCL_Driver final {
        yyFlexLexer plex_;
        SymTbl      symtbl_;
        AST::INode* root_;
        uint32_t    err_counter_;
        SymTbl::tbl_ident cur_id_; // current table ident
        SymTbl::Table* top_; // current table
        SymTbl::Table* saved_; // prev table

    	explicit PCL_Driver(std::istream* is);
        ~PCL_Driver();
    	token_t yylex(yy::PCL_Parser::semantic_type* yylval, yy::PCL_Parser::location_type* yylloc);
    	int parse();
    	int interpretate(AST::INode* node);
    };

}