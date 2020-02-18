#pragma once

#include "TokenNames.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iostream>

namespace AST {

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
        IdNode(TokenName tname, std::string&& name)
                :
                INode(tname),
                name_(name)
        {}

#ifdef DEBUG
        void print() override;
#endif
        std::string& get_id() {
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

        ~TwoKidsNode();

#ifdef DEBUG
        void print() override;
#endif
	    INode* GetKid(char side) const;
	    void SetKid(char side, INode* val);
	};

    // Node for sequence of instructions or expressions
    class ListNode final : public INode {
        std::list<INode*> kids_;
        // if this node used as SCOPE then id_ == scope table identifier
        int id_ = 0;
    public:
        explicit ListNode(TokenName tname)
                :
                INode(tname)
        {}

        ~ListNode();

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

        INode* operator[] (int idx) const;
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

        ~IfNode();
        INode* GetKid(char side) const;
        void SetKid(char side, INode* val);
#ifdef DEBUG
        void print() override;
#endif
    };

}