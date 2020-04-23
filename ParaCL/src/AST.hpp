#pragma once

#include "TokenNames.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <deque>
#include <cassert>

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
"T_RETURNPOINT"
};
#endif

    // base node
	class INode {
	protected:
	    TokenName tname_;
	public:
	    explicit INode(TokenName tname) noexcept
                :
                tname_(tname)
        {}

        INode(const INode&) = delete;
	    INode& operator= (const INode&) = delete;

	    TokenName GetType() const noexcept {
	        return tname_;
	    }

	    virtual ~INode() = default;

#ifdef DEBUG
        virtual void print() const;
#endif
	};

	// id node, using only in expression and statements
	// all declarations are in Symbol Table
	class IdNode final : public INode {
	    std::string name_;
	public:
        IdNode(TokenName tname, std::string name) noexcept
                :
                INode(tname),
                name_(std::move(name))
        {}

        IdNode(const IdNode&) = delete;
        IdNode& operator= (const IdNode) = delete;

#ifdef DEBUG
        void print() const override;
#endif
        [[nodiscard]]
        std::string GetName() const {
            return name_;
        }
	};

    inline std::string GetName (INode* node) {
        return static_cast<IdNode*>(node) -> GetName();
    }

	// integer literal node
	class NumNode final : public INode {
        int num_;
    public:
        NumNode(TokenName tname, int num) noexcept
                :
                INode(tname),
                num_(num)
        {}

        NumNode(const NumNode&) = delete;
        NumNode& operator= (const NumNode) = delete;

#ifdef DEBUG
        void print() const override;
#endif
        int GetNum() const noexcept {
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
        TwoKidsNode(TokenName tname, AST::INode *left, AST::INode *right) noexcept
                :
                INode(tname),
                left_(left),
                right_(right)
        {}

        TwoKidsNode(const TwoKidsNode&) = delete;
        TwoKidsNode& operator= (const TwoKidsNode) = delete;

        ~TwoKidsNode();

#ifdef DEBUG
        void print() const override;
#endif
	    INode* GetLeftKid() const noexcept { return left_; }

	    INode* GetRightKid() const noexcept { return right_; }
	};

    // Node for sequence of instructions or expressions
    class ListNode final : public INode {
        using container_t = std::vector<INode*>;
        container_t kids_;
        // if this node used as SCOPE then id_ == scope table identifier
        int id_ = 0;
    public:
        explicit ListNode(TokenName tname) noexcept
                :
                INode(tname)
        {}

        /**
         * this constructor is used by parser
         * to create T_SCOPE and T_FUNCTION_SCOPE nodes from T_STMTLIST
         * @param tname
         * @param donor
         * @param id
         */
        ListNode(TokenName tname, ListNode&& donor, int id) noexcept
            :
                INode(tname),
                kids_(std::move(donor.kids_)),
                id_(id)
        {}

        ListNode(const ListNode&) = delete;
        ListNode& operator= (const ListNode) = delete;

        ~ListNode();

#ifdef DEBUG
        void print() const override;
#endif
        void push_kid(AST::INode *kid) {

            if (!kid)
                throw std::logic_error("nullptr in push_kid function");
            kids_.push_back(kid);
        }

        int size() const noexcept {
            return kids_.size();
        }

        int GetTable_id() const noexcept {
            return id_;
        }

        INode* operator[] (int idx) {
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

        IfNode(TokenName tname, AST::INode *expr, AST::INode *stmt, AST::INode *_else = nullptr) noexcept
                :
                INode(tname),
                expr_(expr),
                stmt_(stmt),
                else_(_else)
        {}

        IfNode(const IfNode&) = delete;
        IfNode& operator= (const IfNode) = delete;

        ~IfNode();

        INode* GetExpr() const noexcept { return expr_; }

        INode* GetStmt() const noexcept { return stmt_; }

        INode* GetElse() const noexcept { return else_; }

#ifdef DEBUG
        void print() const override;
#endif
    };
}
