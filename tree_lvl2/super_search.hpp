#include "super_tree.hpp"
#include <cassert>

namespace cxx_containers {
    template<typename Key, typename Compare = std::less<Key>>
    class SuperSearch final {
        super_tree<Key, Compare> tree_;
    public:
        SuperSearch() = default;

        explicit SuperSearch(const Compare& comp)
            :
            tree_(comp) {}

        void push(const Key& elem) noexcept{
            tree_.root_ = tree_.insert(tree_.root_, elem);
        }

        void remove(const Key& elem) noexcept{
            auto node = tree_.remove(tree_.root_, elem);
            if(!node) return;
            tree_.root_ = node;
        }

        bool exists(const Key& elem) const noexcept{
            return tree_.find(tree_.root_, elem) != nullptr;
        }

        const Key& min() const noexcept{
            auto min = tree_.findmin(tree_.root);
            return min ? min->key_:Key();
        }

        const Key& max() const noexcept{
            auto max = tree_.findmax(tree_.root);
            return max ? max->key_ : Key();
        }

        int size() const noexcept {
            if(tree_)
                return tree_.size_;
            return 0;
        }

        const Key& k_min(int k) const {
            if(k <= 0)
                throw std::runtime_error("k less than or equal zero");
            if(k > tree_.size_)
                throw std::out_of_range("k greater than tree size");

            typename super_tree<Key, Compare>::node_t* answ = nullptr;
            answ = tree_.k_min(k, tree_.root_);
            assert(answ);
            return answ -> key_;
        }

        int less_than(const Key& elem) const noexcept {
            return tree_.less_than(elem, tree_.root_, 0);
        }
    };
}