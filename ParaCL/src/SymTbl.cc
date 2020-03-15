#include "SymTbl.hpp"
#include <sstream>

SymTbl::Table::IDec* SymTbl::Table::find(const std::string &name) const {
    auto it = tbl_.find(name);
    if(it == tbl_.end()) {
        if(prev_)
            return prev_ -> find(name);
        else
            return nullptr;
    } else
        return it -> second;
}

#ifdef DEBUG
void SymTbl::Table::print() {
    std::cout << "\t|scope size:|" << tbl_.size() << std::endl;
    for(auto& [name, decl] : tbl_) {
        if(decl -> type_ == DECL_TYPE::VAR)
            std::cout << "\tVARIABLE \n\t|name:| " << name << std::endl << "\t|value:| "
                      << static_cast<VarDec*>(decl) -> value_ << std::endl << "\t|line:| "
                      << decl -> line_ << std::endl << std::endl;
        else
            std::cout << "\tFUNCTION \n\t|name:| " << name << std::endl << "\t|arguments number:| "
                      << static_cast<FuncDec*>(decl) -> arg_names_.size() << std::endl
                      << "\t|functions scope id:| " <<  static_cast<FuncDec*>(decl) -> tbl_id_ << std::endl << "\t|line:| "
                      << decl -> line_ << std::endl << std::endl;
    }
}
#endif

SymTbl::Table* SymTbl::find_tbl(SymTbl::tbl_ident id) {
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
    for(auto& elem : env_)
        delete elem.second;
}

#ifdef DEBUG
void SymTbl::print() {
    int i = 0;
    for( auto& elem : env_) {
        std::cout << "SCOPE: " << elem.first << std::endl;
        elem.second -> print();
    }
}
#endif