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
            try {
                const Key& min = tree_.findmin();
                return min;
            } catch(...) {
                throw;
            }
        }

        const Key& max() const {
            try {
                const Key& max = tree_.findmax();
                return max;
            } catch(...) {
                throw;
            }
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
