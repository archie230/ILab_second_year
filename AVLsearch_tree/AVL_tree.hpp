#pragma once 

#include <queue>
#include <errno.h>

namespace cxx_containers {
    template <typename Key, typename Compare>
    /**
    * @tparam Key
    * @tparam Compare is a functor, for which is true:
    *                      if lhs < rhs then Compare(lhs, rhs)=true
    */
    struct AVL_tree {

        using comp_t = Compare;
        using node_t = struct AVLTreeNode {
            Key key_;
            int height_ = 0;

            AVLTreeNode *parent_ = nullptr;
            AVLTreeNode *left_   = nullptr;
            AVLTreeNode *right_  = nullptr;

            AVLTreeNode() = default;

            explicit AVLTreeNode(const Key& key, int height = 0, AVLTreeNode *parent = nullptr,
                                    AVLTreeNode *left = nullptr, AVLTreeNode *right = nullptr)
                    :
                    key_(key),
                    height_(height),
                    parent_(parent),
                    left_(left),
                    right_(right) {}

            int BalanceFactor() const{
                    return (right_ ? right_->height_:0) - (left_ ? left_->height_:0);
            }

            void CalcHeight() {
                int lh = left_ ? left_->height_ : 0;
                int rh = right_ ? right_->height_ : 0;
                height_ = (lh > rh ? lh : rh) + 1;
            }
        };

        comp_t  comparator_;
        node_t  *root_ = nullptr;
        int     size_  = 0;

        AVL_tree() = default;

        explicit AVL_tree(const comp_t& cmp)
                :
                comparator_(cmp),
                root_(nullptr)
        {}

        //deep copy tree with other root to our tree
        void Copy(node_t* other) {
            std::queue<node_t*> remaining;
            node_t* node = nullptr;

            remaining.push(other);

            while(!remaining.empty()) {
                node = remaining.front();
                remaining.pop();

                root_ = insert(root_, node->key_);

                if(node->left_ != nullptr)
                    remaining.push(node->left_);
                if(node->right_ != nullptr)
                    remaining.push(node->right_);
            }
        }

        AVL_tree(const AVL_tree& other)
                :
                comparator_(other.comparator_),
                root_(nullptr)
        {
            Copy(other.root_);
        }

        AVL_tree& operator=(const AVL_tree& other) {
            if(this == &other)
                return *this;

            Clear();
            Copy(other.root_);

            return *this;
        }

        //clearing tree
        void Clear() {
            std::queue<node_t*> remaining;
            node_t* node = nullptr;

            if(!root_)
                return;

            remaining.push(root_);

            while(!remaining.empty()) {
                node = remaining.front();
                remaining.pop();

                if(node->left_ != nullptr)
                    remaining.push(node->left_);
                if(node->right_ != nullptr)
                    remaining.push(node->right_);

                delete node;
            }

            root_ = nullptr;
        }

        ~AVL_tree() {
            Clear();
        }

        static void add_left(node_t* parent, node_t* left_child) {
            if(!parent || parent->left_ == left_child)
                return;

            parent->left_ = left_child;

            if(left_child)
                left_child->parent_ = parent;
        }

        static void add_right(node_t* parent, node_t* right_child) {
            if(!parent || parent->right_ == right_child)
                return;

            parent->right_ = right_child;

            if(right_child)
                right_child->parent_ = parent;
        }

        /**
         * simple left rotation about node as root
         * @param node
         * @return
         */
        node_t* RotateLeft(node_t* node) {
            node_t* save = node->right_;

            add_right(node, node->right_->left_);
            add_left(save, node);

            node->CalcHeight();
            save->CalcHeight();

            return save;
        }
        /**
         * simple right rotation about node as root
         * @param node
         * @return
         */
        node_t* RotateRight(node_t* node) {
            node_t* save = node->left_;

            add_left(node, node->left_->right_);
            add_right(save, node);

            node->CalcHeight();
            save->CalcHeight();

            return save;
        }

        node_t* Balance(node_t* node) {
            node->CalcHeight();
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
            if(node->BalanceFactor() == 2) {
                if(node->right_->BalanceFactor() < 0)
                    add_right(node, RotateRight(node->right_));
                return RotateLeft(node);
            }
            if(node->BalanceFactor() == -2) {
                if(node->left_->BalanceFactor() > 0)
                    add_left(node, RotateLeft(node->left_));
                return RotateRight(node);
            }
            return node;
        }
        /**
         * insert key in tree
         * @param node tree root
         * @param key
         * @return new tree root, after inserting tree is rebalanced
         */
        node_t* insert(node_t* node, const Key& key) {
            if(!node) {
                size_++;
                return new node_t(key);
            }
            if(key == node->key_)
                return node;  // already exists
            else {
                if(comparator_(key, node->key_))
                    add_left(node, insert(node->left_, key));
                else
                    add_right(node, insert(node->right_, key));
            }
            return Balance(node); // rebalancing tree in end of recursion
        }

        //find nemo
        node_t* find(node_t* node, const Key& nemo) const{
            if(!node)
                return nullptr;

            if(comparator_(nemo, node->key_))
                return find(node->left_, nemo);
            else {
                if(nemo == node->key_)
                    return node; //< we found nemo!
                else return find(node->right_, nemo);
            } 
        }

        //finding a max ket node
        node_t* findmax(node_t* node) const{
            return node->right_ ? findmax(node->right_) : node;
        }

        //finding a minimal key node
        node_t* findmin(node_t* node) const{
            return node->left_ ? findmin(node->left_) : node;
        }

        //unlinking(not deleting) minimal node
        node_t* unlinkmin(node_t* node) {
            if(!node->left_)
                return node->right_;
            node->left_ = unlinkmin(node->left_);
            return Balance(node);
        }

        /**
         * removing node with key
         * @param node root pointer
         * @param key
         * @return new root pointer or nullptr if there is no key node
         */
        node_t* remove(node_t* node, const Key& key) {
            if(!node)
                return nullptr;

            if(key == node->key_) {
                node_t* left_subtree  = node->left_;
                node_t* right_subtree = node->right_;

                delete node;
                size_--;

                if(!right_subtree)
                    return left_subtree;

                node_t* min = findmin(right_subtree);
                add_right(min, unlinkmin(right_subtree));
                add_left(min, left_subtree);

                return Balance(min); // rebalancing tree in end of recursion
            } else {
                if(comparator_(key, node->key_))
                    add_left(node, remove(node->left_, key));
                else
                    add_right(node, remove(node->right_, key));
            }

            return Balance(node); // rebalancing tree in end of recursion
        }
    };
}