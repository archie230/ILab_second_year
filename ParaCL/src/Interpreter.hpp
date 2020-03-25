#pragma once

#include "AST.hpp"
#include "SymTbl.hpp"
#include "TokenNames.hpp"

#include "parser/parser.hh"
#include <deque>

namespace yy {

    class Interpreter final {
    public:
        // first contains post order traversal of expression subtree
        // second contains accumulated values
        using expression_frame_t = std::pair<std::deque<AST::INode*>, std::deque<int>>;
        // first == true if statement has calculated expression
        // for example if (expr) {...} with calculated expr
        // first == false if expression is not calculated
        using instruction_t      = std::pair<bool, AST::INode*>;
    private:
        // Intermidiate Representation
        AST::INode*                     root_;
        SymTbl&                         symtbl_;

        // Service Structures:

        // called function's ids T_FUNCNAME tokens
        std::deque<AST::INode*>             funccall_stack_;
        std::deque<AST::INode*>::size_type  max_recursion_deepness;

        // frames:
        // "variable container"
        std::deque<SymTbl::Table*>      env_;
        // stack of stacks to calculate expressions
        std::deque<expression_frame_t>  expression_stack_;
        //

        // stack for control flow traversal
        std::deque<instruction_t>       instructions_stack_;

#define ACCUMULATED_VALS expression_stack_.front().second
#define POSTFIX_NOTATION expression_stack_.front().first

    public:

        Interpreter(AST::INode* root, SymTbl& symtbl, SymTbl::Table* global_table);

        ~Interpreter();

        Interpreter(const Interpreter&) = delete;

        int interpretate();

        void set_recursion_deepness(std::deque<AST::INode*>::size_type deepness)
        { max_recursion_deepness = deepness; }

    private:

        AST::INode* calc_expression();

        void assign_function_arguments();

        void create_frame(SymTbl::tbl_ident id, AST::ListNode* listnode);
        void delete_frame();

        void postorder_traversing(AST::INode* node);

        int get_value(AST::INode* node);
    };

}