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

    struct PCL_Driver final {

        yyFlexLexer                 plex_;
        SymTbl                      symtbl_;
        AST::INode*                 root_;
        uint32_t                    err_counter_;
        int                         recursion_deepness_;

        SymTbl::tbl_ident           cur_id_;
        std::deque<SymTbl::Table*>  env_;

        explicit PCL_Driver(std::istream* is);
        ~PCL_Driver();
        token_t yylex(yy::PCL_Parser::semantic_type* yylval, yy::PCL_Parser::location_type* yylloc);
        int parse();
        void interpretate(AST::INode* node);

    private:
        int calc_expression(AST::INode* node);

        /**
         * @return first == true if there is explicit return
         * second - return value;
         */
        std::pair<bool, int> calc_scope(AST::INode* node);
        int calc_function(AST::INode* node);
        std::pair<bool, int> interpretate_stmt(AST::INode* node);
        void post_order_trav(AST::INode *node, std::stack<AST::INode*> &s2);

        // all predicates and "int return" functions lower
        // expect that they have node that used in expressions(except assign node)
        // otherwise they throw runtime_error
        bool has_kid(AST::INode* node, char side);
        bool is_operator(AST::INode* node);
        bool is_unary_operator(AST::INode* node);
        int get_value(AST::INode* node);
        int calc_operator(AST::INode* opertr, int lhs, int rhs);
        int calc_operator(AST::INode* opertr, int rhs);
    };

}