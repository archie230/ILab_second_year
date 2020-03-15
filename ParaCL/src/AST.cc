#include "AST.hpp"

#ifdef DEBUG
void AST::INode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << names[tname_] << std::endl;
}
#endif
//


#ifdef DEBUG
void AST::IdNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << names[tname_] << " [name:] " << name_ << std::endl;
}
#endif

//

#ifdef DEBUG
void AST::NumNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << names[tname_] << " [num]: " << num_ << std::endl;
}
#endif

//

// 2 kids node

AST::TwoKidsNode::~TwoKidsNode() {
    delete left_;
    delete right_;
}

#ifdef DEBUG
void AST::TwoKidsNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << names[tname_] << " [left:] " << std::hex << left_ << " [right:] " << right_ << std::dec << std::endl;
    if(left_)
        left_ -> print();
    if(right_)
        right_ -> print();
}
#endif
//

// list node

AST::ListNode::~ListNode() {
    for_each(kids_.begin(), kids_.end(), [](INode* node) {delete node;});
}

#ifdef DEBUG
void AST::ListNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << names[tname_] << " [table_id:] " << id_ << std::hex << " [kids:]";
    for_each(kids_.begin(), kids_.end(), [](INode* node) {std::cout << " " << node;});
    std::cout << std::dec << std::endl;
    for_each(kids_.begin(), kids_.end(), [](INode* node) { if(node) node -> print();});
}
#endif

AST::INode *AST::ListNode::operator[](int idx) const{
    if(idx >= kids_.size())
        throw std::out_of_range("idx greater than kids_ container size");

    return kids_[idx];
}
//

AST::IfNode::~IfNode() {
    delete expr_;
    delete stmt_;
    delete else_;
}

#ifdef DEBUG
void AST::IfNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << names[tname_] << " [expression:] " << std::hex << expr_ << " [statement:] " << stmt_
                << " [else:] " << else_ << std::dec << std::endl;
    if(expr_)
        expr_ -> print();
    if(stmt_)
        stmt_ -> print();
    if(else_)
        else_ -> print();
}
#endif