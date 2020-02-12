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
	    explicit INode(TokenName tname);
        virtual ~INode() = default;
#ifdef _DEBUG
        virtual void print();
#endif
        void SetType(TokenName tname);
        TokenName GetType();
	};

	// id node, using only in expression and statements
	// all declarations are in Symbol Table
	class IdNode final : public INode {
	    std::string* name_;
	public:
	    IdNode(TokenName tname, std::string* name);
        ~IdNode();
#ifdef _DEBUG
        void print() override;
#endif
        std::string* get_id();
	};

	// integer literal node
	class NumNode final : public INode {
        int num_;
    public:
        NumNode(TokenName tname, int num);

#ifdef _DEBUG
        void print() override;
#endif
        int GetNum();
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
	class _2kidsNode final: public INode {
	    INode* left_;
	    INode* right_;
	public:
	    _2kidsNode(TokenName tname, INode* left, INode* right);
        ~_2kidsNode();

#ifdef _DEBUG
        void print() override;
#endif
	    INode* GetKid(char side);
	    void SetKid(char side, INode* val);
	};

    // Node for sequence of instructions or expressions
    class ListNode final: public INode {
        std::list<INode*> kids_;
        // if this node used as SCOPE then id_ == scope table identifier
        int id_ = 0;
    public:
        explicit ListNode(TokenName tname);

        ~ListNode();

#ifdef _DEBUG
        void print() override;
#endif
        void push_kid(INode* kid);
        int size();
        int GetTable_id();
        void SetTable_id(int id);
        INode* operator[] (int idx);
    };
}