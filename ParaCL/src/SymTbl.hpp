#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <deque>
#include "AST.hpp"

struct SymTbl final {
    using tbl_ident = int;

    struct Table final {
        enum DECL_TYPE {
            VAR  ,
            FUNC ,
        };

        struct IDec {
            DECL_TYPE type_; // which declaration
            uint32_t  line_;
        };

        struct VarDec : public IDec {
            int value_;
        };

        struct FuncDec : public IDec {
            tbl_ident   tbl_id_; // function scope identifier
            std::deque<std::string> arg_names_;
            AST::INode* function_body_;
        };

        std::unordered_map<std::string, IDec*> tbl_;
        Table* prev_;
        tbl_ident id_;

        Table(SymTbl::Table *prev, tbl_ident id)
                :
                prev_(prev),
                id_(id)
        {}

        Table(const Table& other)
            :
                tbl_(other.tbl_),
                prev_(other.prev_),
                id_(other.id_)
        {
#ifdef DEBUG
            std::cout << "created frame" << std::endl;
#endif
            for(auto& [str, ptr] : tbl_) {
                if(ptr -> type_ == VAR)
                    ptr = new VarDec(*static_cast<VarDec*>(other.tbl_.find(str) -> second));
                else
                    ptr = new FuncDec(*static_cast<FuncDec*>(other.tbl_.find(str) -> second));
            }
        }

        ~Table() {
            std::for_each(tbl_.begin(), tbl_.end(),
                          [] (const std::pair<std::string, IDec*>& p) { if(p.second -> type_ == VAR)
                                                                                delete p.second;
                                                                           else
                                                                                delete static_cast<FuncDec*>(p.second);
                                                                        });
        }

        IDec* find(const std::string& name) const;

        void insert(const std::string &name, IDec* decl) {
            auto [it, flag] = tbl_.insert({name, decl});
            if(!flag)
                throw std::runtime_error("variable already exists");
        }

#ifdef DEBUG
        void print();
#endif
    };

private:
    // sym table is a hierarchy of tables
    std::unordered_map<tbl_ident, Table*> env_;

public:

    Table* find_tbl(tbl_ident id);

    void add_tbl(SymTbl::tbl_ident id, SymTbl::Table *tbl) {
        auto [it, flag] = env_.insert({id, tbl});
        if(!flag)
            throw std::runtime_error("table already exists");
    }

    ~SymTbl();
#ifdef DEBUG
    void print();
#endif
};