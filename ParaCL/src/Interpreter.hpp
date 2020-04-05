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
        // first == true if scope is not symtbl_ invariant
        // i.e. was created as copy of existing scope
        using scope_t            = std::pair<bool, SymTbl::Table*>;
    private:
        // Intermidiate Representation
        AST::INode*                     root_;
        SymTbl&                         symtbl_;

        // Service Structures:

        // called function's ids T_FUNCNAME tokens
        std::deque<AST::INode*>             funccall_stack_;
        std::deque<AST::INode*>::size_type  max_funccall_stack_sz;

        // frames:
        // "variable container"
        std::deque<scope_t>      env_;
        // stack of stacks to calculate expressions
        std::deque<expression_frame_t>  expression_stack_;
        //

        // stack for control flow traversal
        std::deque<instruction_t>       instructions_stack_;

#define ACCUMULATED_VALS expression_stack_.front().second
#define POSTFIX_NOTATION expression_stack_.front().first
#define MAX_FUNCCALL_STACK_SIZE 2500

    public:

        Interpreter(AST::INode* root, SymTbl& symtbl, SymTbl::Table* global_table);

        ~Interpreter();

        Interpreter(const Interpreter&) = delete;

        int interpretate();

        void set_recursion_deepness(std::deque<AST::INode*>::size_type deepness)
        { max_funccall_stack_sz = deepness; }

    private:

        AST::INode* calc_expression();
        void assign_function_arguments();
        void create_frame(SymTbl::tbl_ident id, AST::ListNode* listnode);
        void delete_frame() noexcept;
        void postorder_traversing(AST::INode* node);
        int get_value(AST::INode* node) const;

        void interpretate_T_SCOPE(AST::INode*);
        void interpretate_T_FUNCTION_SCOPE(AST::INode*);
        void interpretate_T_EXPRLIST(AST::INode*);
        void interpretate_T_SCOPEEND(AST::INode*);
        void interpretate_T_FUNCNAME(AST::INode*);
        void interpretate_T_FUNCCALL(AST::INode*);
        void interpretate_T_IF(bool, AST::INode*);
        void interpretate_T_WHILE(bool, AST::INode*);
        void interpretate_T_RETURN(bool, AST::INode*);
        void interpretate_T_OUTPUT(bool, AST::INode*);
        void interpretate_T_ASSIGN(bool, AST::INode*);
        void interpretate_T_RETURNPOINT(AST::INode*);
    };

}