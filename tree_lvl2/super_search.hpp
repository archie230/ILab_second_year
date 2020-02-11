#pragma once
#include "super_tree.hpp"

namespace cxx_containers {

    template<typename Key, typename Compare = std::less<Key>>
    class SuperSearch final {
        super_tree<Key, Compare> tree_;
    public:
        SuperSearch() = default;

        explicit SuperSearch(const Compare& comp)
            :
            tree_(comp) {}

        void push(const Key& elem) {
            tree_.insert(elem);
        }

        void remove(const Key& elem) {
            tree_.remove(elem);
        }

        bool exists(const Key& elem) const noexcept {
            return tree_.find(elem);
        }

        const Key& min() const {
            return tree_.findmin();
        }

        const Key& max() const {
            return tree_.findmax();
        }

        int size() const noexcept {
            return tree_.size();
        }

        const Key& k_min(int k) const {
            try {
                const Key& k_minimal = tree_.k_min(k);
                return k_minimal;
            } catch(...) {
                throw;
            }
        }

        int less_than(const Key& elem) const noexcept {
            return tree_.less_than(elem);
        }
    };

}
