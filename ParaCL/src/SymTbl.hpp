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

            IDec(DECL_TYPE type, uint32_t line)
                :
                type_(type),
                line_(line)
            {}

            virtual ~IDec() = default;

            virtual IDec* copy() const = 0;
        };

        struct VarDec final : public IDec {
            int value_;

            VarDec(DECL_TYPE type, uint32_t line, int value)
                :
                IDec(type, line),
                value_(value)
            {}

            ~VarDec() override = default;

            [[nodiscard]]
            IDec* copy() const override {
                return new VarDec(*this);
            }
        };

        struct FuncDec final : public IDec {
            tbl_ident   tbl_id_; // function scope identifier
            std::deque<std::string> arg_names_;
            AST::INode* function_body_;

            FuncDec(DECL_TYPE type, uint32_t line, tbl_ident tbl_id, AST::INode* function_body = nullptr )
                :
                IDec(type, line),
                tbl_id_(tbl_id),
                function_body_(function_body)
            {}


            ~FuncDec() override = default;

            [[nodiscard]]
            IDec* copy() const override {
                return new FuncDec(*this);
            }
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
            for(auto& [str, ptr] : tbl_)
                ptr = other.tbl_.find(str) -> second -> copy();
        }

        ~Table() {
            for(auto& elem : tbl_)
                delete elem.second;
        }

        IDec* find(const std::string& name) const;

        void insert(const std::string &name, IDec* decl) {
            if (tbl_.find(name) != tbl_.end())
                throw std::runtime_error("variable already exists");

            tbl_.insert({name, decl});
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
        if (env_.find(id) != env_.end())
            throw std::runtime_error("table already exists");

        env_.insert({id, tbl});
    }

    ~SymTbl();
#ifdef DEBUG
    void print();
#endif
};