#include "SymTbl.hpp"

SymTbl::Table::Table(SymTbl::Table *prev, SymTbl::tbl_ident id)
        :
        prev_(prev),
        id_(id)
{}

SymTbl::Table::VarDec *SymTbl::Table::find(const std::string &name) {
    auto it = tbl_.find(name);
    if(it == tbl_.end()) {
        if(prev_)
            return prev_ -> find(name);
        else return nullptr;
    } else
        return &(it -> second);
}

void SymTbl::Table::insert(const std::string &name, const SymTbl::Table::VarDec &decl) {
    tbl_[name] = decl;
}

#ifdef _DEBUG
void SymTbl::Table::print() {
    std::cout << "|scope:" << id_ << "| size:" << tbl_.size() << std::endl;
    for(auto& pair : tbl_) {
        std::cout << "\t|name:| " << pair.first << std::endl << "\t|init_val:| " << std::hex
                  << pair.second.decl_<< std::dec << std::endl << "\t|line:| " << pair.second.line_ << std::endl << std::endl;
    }
}
#endif

SymTbl::Table *SymTbl::find_tbl(SymTbl::tbl_ident id) {
    auto it = env_.find(id);
    if(it == env_.end())
        return nullptr;
    else
        return it -> second;
}

void SymTbl::add_tbl(SymTbl::tbl_ident id, SymTbl::Table *tbl) {
    env_[id] = tbl;
}

SymTbl::~SymTbl() {
    for(auto elem : env_)
        delete elem.second;
}

#ifdef _DEBUG
void SymTbl::print() {
    int i = 0;
    for( auto& elem : env_)
        elem.second -> print();
}
#endif