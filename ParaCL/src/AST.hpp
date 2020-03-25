#pragma once

#include "TokenNames.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <deque>

namespace AST {

#ifdef DEBUG
const std::vector<std::string> names = {
"T_NUM      ",
"T_ID       ",
"T_WHILE    ",
"T_IF       ",
"T_OR       ",
"T_AND      ",
"T_LESS     ",
"T_GR       ",
"T_LESS_EQ  ",
"T_GR_EQ    ",
"T_EQUAL    ",
"T_NEQUAL   ",
"T_ADD      ",
"T_SUB      ",
"T_MUL      ",
"T_DIV      ",
"T_INPUT    ",
"T_OUTPUT   ",
"T_ASSIGN   ",
"T_STMLST   ",
"T_SCOPE    ",
"T_PERCENT  ",
"T_RETURN   ",
"T_FUNCDEC  ",
"T_FUNCCALL ",
"T_ARGLIST  ",
"T_EXPRLIST ",
"T_EXCLAM   ",
"T_FUNCTION_SCOPE",
"T_SCOPEEND" ,
"T_FUNCEND"  ,
"T_FUNCNAME",
"T_RETURNPOINT",
"T_WHILE_CALC_EXPR",
"T_IF_CALC_EXPR",
"T_OUTPUT_CALC_EXPR",
"T_RETURN_CALC_EXPR",
"T_ASSIGN_CALC_EXPR"
};
#endif

    // base node
	class INode {
	protected:
	    TokenName tname_;
	public:
	    explicit INode(TokenName tname)
                :
                tname_(tname)
        {}

        virtual ~INode() = default;

#ifdef DEBUG
        virtual void print();
#endif
        void SetType(TokenName tname) {
            tname_ = tname;
        }

        TokenName GetType() const {
            return tname_;
        }
	};

	// id node, using only in expression and statements
	// all declarations are in Symbol Table
	class IdNode final : public INode {
	    std::string name_;
	public:
        IdNode(TokenName tname, const std::string&  name)
                :
                INode(tname),
                name_(name)
        {}

        ~IdNode() override = default;

#ifdef DEBUG
        void print() override;
#endif
        std::string get_id() const {
            return name_;
        }
	};

	// integer literal node
	class NumNode final : public INode {
        int num_;
    public:
        NumNode(TokenName tname, int num)
                :
                INode(tname),
                num_(num)
        {}

        ~NumNode() override = default;

#ifdef DEBUG
        void print() override;
#endif
        int GetNum() const {
            return num_;
        }
	};
	
    // in case if this is a unary operator:
    // left_ = nullptr for prefix one
    // right_ = nullptr for postfix
    //
    // also this node describes:
    // -program root
    //  left = declarations, right = stmts
    // -while(expression) stmt instruction
    //  left_ = expression and right_ = stmt
	class TwoKidsNode : public INode {
	    INode* left_;
	    INode* right_;
	public:
        TwoKidsNode(TokenName tname, AST::INode *left, AST::INode *right)
                :
                INode(tname),
                left_(left),
                right_(right)
        {}

        ~TwoKidsNode() override;

#ifdef DEBUG
        void print() override;
#endif
	    INode* GetLeftKid() const { return left_; }

	    INode* GetRightKid() const { return right_; }

	    void SetLeftKid(INode* val) { left_ = val; }

	    void SetRightKid(INode* val) { right_ = val; }
	};

    // Node for sequence of instructions or expressions
    class ListNode final : public INode {
        using container_t = std::deque<INode*>;
        container_t kids_;
        // if this node used as SCOPE then id_ == scope table identifier
        int id_ = 0;
    public:
        explicit ListNode(TokenName tname)
                :
                INode(tname)
        {}

        ~ListNode() override;

#ifdef DEBUG
        void print() override;
#endif
        void push_kid(AST::INode *kid) {
            if(!kid)
                return;
            kids_.push_back(kid);
        }

        int size() const {
            return kids_.size();
        }

        int GetTable_id() const {
            return id_;
        }

        void SetTable_id(int id) {
            id_ = id;
        }

        INode*& operator[] (int idx) {
            return kids_[idx];
        }

        container_t::iterator begin() { return kids_.begin(); }
        container_t::iterator end()   { return kids_.end(); }

        container_t::reverse_iterator rbegin() { return kids_.rbegin(); }
        container_t::reverse_iterator rend()   { return kids_.rend(); }

    };

// If statement node
    // if "If statement node" is "elseless", then else_ = nullptr
    class IfNode final: public INode {
        INode* expr_;
        INode* stmt_;
        INode* else_;
    public:

        IfNode(TokenName tname, AST::INode *expr, AST::INode *stmt, AST::INode *_else = nullptr)
        :
        INode(tname),
        expr_(expr),
        stmt_(stmt),
        else_(_else)
        {}

        ~IfNode() override;

        INode* GetExpr() const { return expr_; }

        INode* GetStmt() const { return stmt_; }

        INode* GetElse() const { return else_; }

        void SetExpr(INode* val) { expr_ = val; }

        void SetStmt(INode* val) { stmt_ = val; }

        void SetElse(INode* val) { else_ = val; }

#ifdef DEBUG
        void print() override;
#endif
    };

}