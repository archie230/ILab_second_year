#include "AST.hpp"

// interface node
AST::INode::INode(TokenName tname)
        :
        tname_(tname)
{}

#ifdef _DEBUG
void AST::INode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << std::endl;
}
#endif

void AST::INode::SetType(TokenName tname) {
    tname_ = tname;
}

TokenName AST::INode::GetType() {
    return tname_;
}
//

// id node
AST::IdNode::IdNode(TokenName tname, std::string *name)
        :
        INode(tname),
        name_(name)
{}

AST::IdNode::~IdNode() {
    delete name_;
}

#ifdef _DEBUG
void AST::IdNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << " [name:] " << *name_ << std::endl;
}
#endif

std::string *AST::IdNode::get_id() {
    return name_;
}
//

// num node
AST::NumNode::NumNode(TokenName tname, int num)
        :
        INode(tname),
        num_(num)
{}

#ifdef _DEBUG
void AST::NumNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << " [num]: " << num_ << std::endl;
}
#endif

int AST::NumNode::GetNum() {
    return num_;
}
//

// 2 kids node
AST::_2kidsNode::_2kidsNode(TokenName tname, AST::INode *left, AST::INode *right)
        :
        INode(tname),
        left_(left),
        right_(right)
{}

AST::_2kidsNode::~_2kidsNode() {
    delete left_;
    delete right_;
}

#ifdef _DEBUG
void AST::_2kidsNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << " [left:] " << std::hex << left_ << " [right:] " << right_ << std::dec << std::endl;
    if(left_)
        left_ -> print();
    if(right_)
        right_ -> print();
}
#endif

AST::INode *AST::_2kidsNode::GetKid(char side) {
    switch(side) {
        case 'l':
            return left_;
        case 'r':
            return right_;
        default:
            return nullptr;
    }
}

void AST::_2kidsNode::SetKid(char side, AST::INode *val) {
    switch(side) {
        case 'l':
            left_ = val;
            break;
        case 'r':
            right_ = val;
            break;
    }
}
//

// list node
AST::ListNode::ListNode(TokenName tname)
        :
        INode(tname)
{}

AST::ListNode::~ListNode() {
    for_each(kids_.begin(), kids_.end(), [](INode* node) {delete node;});
}

#ifdef _DEBUG
void AST::ListNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << std::hex << " [kids:]";
    for_each(kids_.begin(), kids_.end(), [](INode* node) {std::cout << " " << node;});
    std::cout << std::dec << std::endl;
    for_each(kids_.begin(), kids_.end(), [](INode* node) { if(node) node -> print();});
}
#endif

void AST::ListNode::push_kid(AST::INode *kid) {
    if(!kid)
        return;
    kids_.push_back(kid);
}

int AST::ListNode::size() {
    return kids_.size();
}

int AST::ListNode::GetTable_id() {
    return id_;
}

void AST::ListNode::SetTable_id(int id) {
    id_ = id;
}

AST::INode *AST::ListNode::operator[](int idx) {
    if(idx >= kids_.size() || idx < 0)
        return nullptr;

    auto iter = kids_.begin();
    for(int i = 0; i < idx; i++)
        ++iter;

    return *iter;
}
//