#pragma once

#include <cstdint>
#include <functional>
#include "AVL_tree.hpp"

namespace cxx_containers {
    // Binary search tree with unique keys, which based on AVL-Tree
    /**
     * @tparam Key
     * @tparam Compare is functor, for which is true:
     *                      if lhs < rhs then Compare(lhs, rhs)=true
     */
    template <typename Key, typename Compare = std::less<Key>>
    class SearchTree final{
        AVL_tree<Key, Compare> tree_;
    public:
        SearchTree() = default;

        explicit SearchTree(const Compare& comp)
            :
            tree_(comp) {}

        void push(const Key& elem) {
            tree_.root_ = tree_.insert(tree_.root_, elem);
        }

        void remove(const Key& elem) {
            auto node = tree_.remove(tree_.root_, elem);
            if(!node) return;
            tree_.root_ = node;
        }

        bool exists(const Key& elem) const{
            return tree_.find(tree_.root_, elem) != nullptr;
        }

        const Key& min() const {
            auto min = tree_.findmin(tree_.root);
            return min ? min->key_:Key();
        }

        const Key& max() const {
            auto max = tree_.findmax(tree_.root);
            return max ? max->key_ : Key();
        }
    };
}