#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <map>
#include <algorithm>
#include "AST.hpp"

struct SymTbl final {
    using tbl_ident = int;
    struct Table final {

        struct VarDec final {
            AST::INode* decl_   = nullptr;
            uint32_t line_      = 0;
            int value_          = 0;
        };

        std::unordered_map<std::string, VarDec> tbl_;
        Table* prev_;
        tbl_ident id_;

        Table(Table* prev, tbl_ident id);
        VarDec* find(const std::string& name);
        void insert(const std::string& name, const VarDec& decl);
#ifdef _DEBUG
        void print();
#endif
    };

private:
    // sym table is a hierarchy of tables
    std::map<tbl_ident, Table*> env_;

public:

    Table* find_tbl(tbl_ident id);
    void add_tbl(tbl_ident id, Table* tbl);
    ~SymTbl();
#ifdef _DEBUG
    void print();
#endif
};