#include "AST.hpp"

#ifdef DEBUG
void AST::INode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << std::endl;
}
#endif
//


#ifdef DEBUG
void AST::IdNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << " [name:] " << name_ << std::endl;
}
#endif

//

#ifdef DEBUG
void AST::NumNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << " [num]: " << num_ << std::endl;
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
              << tname_ << " [left:] " << std::hex << left_ << " [right:] " << right_ << std::dec << std::endl;
    if(left_)
        left_ -> print();
    if(right_)
        right_ -> print();
}
#endif

AST::INode *AST::TwoKidsNode::GetKid(char side) const {
    switch(side) {
        case 'l':
            return left_;
        case 'r':
            return right_;
        default:
            return nullptr;
    }
}

void AST::TwoKidsNode::SetKid(char side, AST::INode *val) {
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

AST::ListNode::~ListNode() {
    for_each(kids_.begin(), kids_.end(), [](INode* node) {delete node;});
}

#ifdef DEBUG
void AST::ListNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << std::hex << " [kids:]";
    for_each(kids_.begin(), kids_.end(), [](INode* node) {std::cout << " " << node;});
    std::cout << std::dec << std::endl;
    for_each(kids_.begin(), kids_.end(), [](INode* node) { if(node) node -> print();});
}
#endif

AST::INode *AST::ListNode::operator[](int idx) const{
    if(idx >= kids_.size() || idx < 0)
        return nullptr;

    auto iter = kids_.begin();
    for(int i = 0; i < idx; i++)
        ++iter;

    return *iter;
}
//

AST::IfNode::~IfNode() {
    delete expr_;
    delete stmt_;
    delete else_;
}

AST::INode *AST::IfNode::GetKid(char side) const{
    switch(side) {
        case 'l':
            return expr_;
        case 'r':
            return else_;
        case 'm':
            return stmt_;
        default:
            return nullptr;
    }
}

void AST::IfNode::SetKid(char side, AST::INode *val) {
    switch(side) {
        case 'l':
            expr_ = val;
            break;
        case 'r':
            else_ = val;
            break;
        case 'm':
            stmt_ = val;
            break;
    }
}

#ifdef DEBUG
void AST::IfNode::print() {
    std::cout << "  [this:] " << std::hex << this << std::dec << " [token:] "
              << tname_ << " [expression:] " << std::hex << expr_ << " [statement:] " << stmt_
                << " [else:] " << else_ << std::dec << std::endl;
    if(expr_)
        expr_ -> print();
    if(stmt_)
        stmt_ -> print();
    if(else_)
        else_ -> print();
}
#endif