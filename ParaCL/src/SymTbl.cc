#include "SymTbl.hpp"
#include <sstream>

SymTbl::Table::VarDec* SymTbl::Table::find(const std::string &name) {
    auto it = tbl_.find(name);
    if(it == tbl_.end()) {
        if(prev_)
            return prev_ -> find(name);
        else {
            std::stringstream str("can't find elem ");
            str << name;
            throw std::out_of_range(str.str());
        }
    } else
        return &(it -> second);
}

#ifdef DEBUG
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
    if(it == env_.end()) {
        std::stringstream str("can't find table with id: ");
        str << id;
        throw std::out_of_range(str.str());
    }
    else
        return it -> second;
}

SymTbl::~SymTbl() {
    for(auto elem : env_)
        delete elem.second;
}

#ifdef DEBUG
void SymTbl::print() {
    int i = 0;
    for( auto& elem : env_)
        elem.second -> print();
}
#endif