#pragma once

#include <bits/stdc++.h>
#include <queue>

namespace cxx_containers {

    /*
     * super tree is based on AVLTree
     */
    template<typename Key, typename Compare>
    class super_tree final {
#ifdef OPEN_SRC_FOR_UNIT_TST_
    public:
#endif

        using comp_t = Compare;
        using node_t = struct AVLTreeNode {
            Key key_;
            int height_     = 0;
            int lsubnum_    = 1; // number of elements in left subtree including current elem

            AVLTreeNode* parent_ = nullptr;
            AVLTreeNode* left_ = nullptr;
            AVLTreeNode* right_ = nullptr;

            AVLTreeNode() = default;
            AVLTreeNode(const AVLTreeNode&) = delete;
            AVLTreeNode operator=(const AVLTreeNode&) = delete;
            AVLTreeNode(AVLTreeNode&&) = delete;
            AVLTreeNode operator=(AVLTreeNode&&) = delete;
            
            explicit AVLTreeNode(const Key &key, int height = 0, int lsubnum = 1, AVLTreeNode *parent = nullptr,
                                 AVLTreeNode *left = nullptr, AVLTreeNode *right = nullptr)
                    :
                    key_(key),
                    height_(height),
                    lsubnum_(lsubnum),
                    parent_(parent),
                    left_(left),
                    right_(right) {}

            int BalanceFactor() const noexcept {
                return (right_ ? right_ -> height_ : 0) - (left_ ? left_ -> height_ : 0);
            }

            void CalcHeight() noexcept {
                int lh = left_ ? left_ -> height_ : 0;
                int rh = right_ ? right_ -> height_ : 0;
                height_ = (lh > rh ? lh : rh) + 1;
            }
        };

        comp_t comparator_;
        node_t* root_   = nullptr;
        int size_       = 0;

    public:

        super_tree() = default;

        explicit super_tree(comp_t cmp)
                :
                comparator_(cmp),
                root_(nullptr),
                size_(0)
        {}

        super_tree(const super_tree &other)
                :
                comparator_(other.comparator_),
                root_(nullptr),
                size_(0)
        {
            Copy(other.root_);
        }

        super_tree(super_tree&& other)
                :
                comparator_(other.comparator_),
                root_(other.root_),
                size_(other.size_)
        {
            other.root_ = nullptr;
            other.size_ = 0;
        }

        super_tree& operator=(const super_tree &other) {
            if(this == &other)
                return *this;

            Clear();
            Copy(other.root_);
            comparator_ = other.comparator_;

            return *this;
        }

        super_tree& operator=(super_tree&& other) {
            if(this == &other)
                return *this;

            Clear();
            root_       = other.root_;
            other.root_ = nullptr;
            size_       = other.size_;
            other.size_ = 0;
            comparator_ = other.comparator_;
        }
        
        int size() const noexcept {
            return size_;
        }
        
        void insert(const Key& elem) {
            root_ = insert_intern(root_, elem);
        }
        
        void remove(const Key& elem) {
            node_t* node = remove_intern(root_, elem);
            if(!node) return;
            root_ = node;
        }
        
        bool find(const Key& elem) const noexcept {
            return find_intern(root_, elem) != nullptr;
        }

        const Key& findmax() const{
            if(!root_)
                throw std::runtime_error("emprty tree");
            return findmax_intern(root_) -> key_;
        }

        const Key& findmin() const{
            if(!root_)
                throw std::runtime_error("emprty tree");
            return findmin_intern(root_) -> key_;
        }
        
        const Key& k_min(int k) const {
            if(k <= 0)
                throw std::runtime_error("k less than or equal zero");
            if(k > size_)
                throw std::out_of_range("k greater than tree size");

            node_t* answ = nullptr;
            answ = k_min_intern(k, root_);
            assert(answ);
            return answ -> key_;
        }
        
        int less_than(const Key& elem) const noexcept {
            return less_than_intern(elem, root_, 0);
        }

        ~super_tree() {
            Clear();
        }

    private:
#ifdef OPEN_SRC_FOR_UNIT_TST_
    public:
#endif

        //deep copy tree with other root to our tree
        void Copy(node_t* other) {
            std::queue<node_t*> remaining;
            node_t* node = nullptr;

            remaining.push(other);

            while (!remaining.empty()) {
                node = remaining.front();
                remaining.pop();

                root_ = insert_intern(root_, node -> key_);

                if(node -> left_ != nullptr)
                    remaining.push(node -> left_);
                if(node -> right_ != nullptr)
                    remaining.push(node -> right_);
            }
        }

        //clearing tree
        void Clear() {
            std::queue<node_t*> remaining;
            node_t* node = nullptr;

            if(!root_)
                return;

            remaining.push(root_);

            while (!remaining.empty()) {
                node = remaining.front();
                remaining.pop();

                if(node -> left_ != nullptr)
                    remaining.push(node -> left_);
                if(node -> right_ != nullptr)
                    remaining.push(node -> right_);

                delete node;
            }

            root_ = nullptr;
            size_ = 0;
        }

        void add_left(node_t* parent, node_t* left_child) noexcept {
            if(!parent || parent -> left_ == left_child)
                return;

            parent -> left_ = left_child;

            if(left_child)
                left_child -> parent_ = parent;
        }

        void add_right(node_t* parent, node_t* right_child) noexcept {
            if(!parent || parent -> right_ == right_child)
                return;

            parent -> right_ = right_child;

            if(right_child)
                right_child -> parent_ = parent;
        }

        /**
         * simple left rotation about node as root
         * @param node
         * @return
         */
        node_t* RotateLeft(node_t* node) {
            node_t* save = node -> right_;

            add_right(node, node -> right_ -> left_);
            add_left(save, node);

            node -> CalcHeight();
            calculate_lsubnum(node);
            save -> CalcHeight();
            calculate_lsubnum(save);

            return save;
        }

        /**
         * simple right rotation about node as root
         * @param node
         * @return
         */
        node_t* RotateRight(node_t* node) {
            node_t* save = node -> left_;

            add_left(node, node -> left_ -> right_);
            add_right(save, node);

            node -> CalcHeight();
            calculate_lsubnum(node);
            save -> CalcHeight();
            calculate_lsubnum(save);

            return save;
        }

        /*
         * IN FIRST CASE
         * q.height - A.height = 2
         *          node
         *         /   \
         *        A     q
         *            /   \
         *           s     D
         *         /   \
         *        B     C
         *
         *  if s.height <= D.height then making simple left rotation with node as center
         *  and easy to find out that tree will become balanced
         *           q
         *         /   \
         *      node    D
         *      /   \
         *    A      s
         *         /   \
         *        B     C
         *  else making BIG left rotation [BIG left rotation = right rotation about q
         *                                                 then left rotation about node]
         *  result:
         *           s
         *         /   \
         *      node     q
         *     /   \   /   \
         *    A     B C     D
         * IN OTHER CASE SAME LOGIC
         */
        node_t* Balance(node_t* node) {
            node -> CalcHeight();
            calculate_lsubnum(node);

            if(node -> BalanceFactor() == 2) {
                if(node -> right_ -> BalanceFactor() < 0)
                    add_right(node, RotateRight(node -> right_));
                return RotateLeft(node);
            }
            if(node -> BalanceFactor() == -2) {
                if(node -> left_ -> BalanceFactor() > 0)
                    add_left(node, RotateLeft(node -> left_));
                return RotateRight(node);
            }
            return node;
        }

        void calculate_lsubnum(node_t* node) {
            std::stack<node_t*> s;
            int &lsubnum = node -> lsubnum_;
            lsubnum = 1;

            node = node -> left_;

            while (node || !s.empty()) {
                while (node) {
                    s.push(node);
                    node = node -> left_;
                }

                node = s.top();
                s.pop();
                lsubnum++;
                node = node -> right_;
            }
        }

        node_t* k_min_intern(int k, node_t* node) const noexcept {
            if((k <= 0) || (k > size_))
                return nullptr;

            int lsub = node -> lsubnum_;

            if(k == lsub)
                return node;
            if(k > lsub)
                return k_min_intern(k - lsub, node -> right_);
            if(k < lsub)
                return k_min_intern(k, node -> left_);
        }

        int less_than_intern(const Key& elem, node_t* node, int cur_less) const noexcept {
            if(!node)
                return cur_less;

            if(comparator_(node -> key_, elem)) {
                cur_less += node -> lsubnum_;
                return less_than_intern(elem, node -> right_, cur_less);
            } else {
                if(node -> key_ == elem)
                    return (cur_less + (node -> lsubnum_ - 1));
                else
                    return less_than_intern(elem, node -> left_, cur_less);
            }
        }

        /**
         * insert key in tree
         * @param node tree root
         * @param key
         * @return new tree root, after inserting tree is rebalanced
         */
        node_t* insert_intern(node_t* node, const Key &key) {
            if(!node) {
                size_++;
                return new node_t(key);
            }
            if(key == node -> key_)
                return node;  // already exists
            else {
                if(comparator_(key, node -> key_))
                    add_left(node, insert_intern(node -> left_, key));
                else
                    add_right(node, insert_intern(node -> right_, key));
            }
            return Balance(node); // rebalancing tree in end of recursion
        }

        // find nemo
        node_t* find_intern(node_t* node, const Key &nemo) const noexcept {
            if(!node)
                return nullptr;

            if(comparator_(nemo, node -> key_))
                return find_intern(node -> left_, nemo);
            else {
                if(nemo == node -> key_)
                    return node; //< we found nemo!
                else return find_intern(node -> right_, nemo);
            }
        }

        // finding a max ket node
        node_t* findmax_intern(node_t* node) const noexcept {
            if(!node) return nullptr;
            return node -> right_ ? findmax_intern(node -> right_) : node;
        }

        // finding a minimal key node
        node_t* findmin_intern(node_t* node) const noexcept {
            if(!node) return nullptr;
            return node -> left_ ? findmin_intern(node -> left_) : node;
        }

        // unlinking(not deleting) minimal node
        node_t* unlinkmin(node_t* node) {
            if(!node -> left_)
                return node -> right_;
            node -> left_ = unlinkmin(node -> left_);
            return Balance(node);
        }

        /**
         * removing node with key
         * @param node root pointer
         * @param key
         * @return new root pointer or nullptr if there is no key node
         */
        node_t* remove_intern(node_t* node, const Key &key) {
            if(!node)
                return nullptr;

            if(key == node -> key_) {
                node_t* left_subtree = node -> left_;
                node_t* right_subtree = node -> right_;

                delete node;
                size_--;

                if(!right_subtree)
                    return left_subtree;

                node_t* min = findmin_intern(right_subtree);
                add_right(min, unlinkmin(right_subtree));
                add_left(min, left_subtree);

                return Balance(min); // rebalancing tree in end of recursion
            } else {
                if(comparator_(key, node -> key_))
                    add_left(node, remove_intern(node -> left_, key));
                else
                    add_right(node, remove_intern(node -> right_, key));
            }

            return Balance(node); // rebalancing tree in end of recursion
        }
    };

}