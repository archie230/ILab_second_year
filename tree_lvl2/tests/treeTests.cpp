#include <gtest/gtest.h>
#define OPEN_SRC_FOR_UNIT_TST_
#include "../super_tree.hpp"
#include <iostream>
#include <cmath>

using namespace cxx_containers;
using Super_tree = super_tree<int, std::less<int>>;
using AVL_node_t = typename Super_tree::node_t;

std::ostream& operator<<(std::ostream& os, const AVL_node_t& node) {
    os << "{[k: " << node.key_ << "] [h:" << node.height_  << std::hex
       << "] [this: " << &node << "] [p: " << node.parent_
       << "] [l: " << node.left_ << "] [r: " << node.right_ << "]}" << std::endl << std::dec;
    return os;
}

void tree_dump(AVL_node_t* cur, int depth, int state, std::ostream& os) {
    if (!cur) {
        os << "{[nil]}" << std::endl;
        return;
    }

    if (cur->left_)
        tree_dump(cur->left_, depth + 1, 1, os);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1)       // left
        printf("┌───");
    else if (state == 2)  // right
        printf("└───");

    os << *cur;

    if (cur->right_)
        tree_dump(cur->right_, depth + 1, 2, os);
}

std::ostream& operator<<(std::ostream& os, const Super_tree& tree) {
    os << "###TREE###\n";
    tree_dump(tree.root_, 0, 0, os);
    return os;
}

bool Is_Balanced(AVL_node_t * node) {
    bool left_balanced = true, right_balanced = true;

    if(!node)
        return true;

    if(node->left_)
        left_balanced = Is_Balanced(node->left_);
    if(node->right_)
        right_balanced = Is_Balanced(node->right_);

    bool node_balanced = abs(node->BalanceFactor()) < 2;

    return node_balanced && left_balanced && right_balanced;
}

TEST(Super_tree, insert) {
    Super_tree tree;
    srand(time(nullptr));

    for(int i = 0; i < 100; i++) {
        tree.root_ = tree.insert_intern(tree.root_, rand());
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }
}

TEST(Super_tree, remove) {
    Super_tree tree;
    int test_iterations = 100;
    std::vector<int> test_vec(test_iterations);
    std::set<int> used_numders;
    int rand_num = 0;
    bool find = false;

    srand(time(nullptr));

    for(int i = 0; i < test_iterations; i++) {    Super_tree tree;
        std::vector<int> test_vec(test_iterations);
        std::set<int> used_numders;
        int rand_num = 0;
        bool find = false;

        srand(time(nullptr));

        for(int i = 0; i < test_iterations; i++) {
            test_vec[i] = rand();
            tree.root_ = tree.insert_intern(tree.root_,test_vec[i]);
            ASSERT_TRUE(Is_Balanced(tree.root_));
        }
        test_vec[i] = rand();
        tree.root_ = tree.insert_intern(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    std::cout << tree;

    for(int i = 0; i < test_iterations; i++) {
        int rand_index = rand() % test_iterations;

        while(used_numders.find(rand_index) != used_numders.end())
            rand_index = rand() % test_iterations;

        used_numders.insert(rand_index);

        tree.root_ = tree.remove_intern(tree.root_, test_vec[rand_index]);
        //std::cout << tree;
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }
    std::cout << tree;
}

TEST(Super_tree, copy_ctor) {
    Super_tree tree;
    int test_iterations = 100;
    std::vector<int> test_vec(test_iterations);

    srand(time(nullptr));

    for(int i = 0; i < test_iterations; i++) {
        test_vec[i] = rand();
        tree.root_ = tree.insert_intern(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    Super_tree copy_tree(tree);

    for(int i = 0; i < test_iterations; i++) {
        ASSERT_NE(copy_tree.find_intern(copy_tree.root_, test_vec[i]), nullptr);
    }
}

TEST(Super_tree, assignment_oper) {
    Super_tree tree;
    int test_iterations = 100;
    std::vector<int> test_vec(test_iterations);

    srand(time(nullptr));

    for(int i = 0; i < test_iterations; i++) {
        test_vec[i] = rand();
        tree.root_ = tree.insert_intern(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    Super_tree other_tree = tree;

    for(int i = 0; i < test_iterations; i++) {
        ASSERT_NE(other_tree.find_intern(other_tree.root_, test_vec[i]), nullptr);
    }

    other_tree = tree;
    for(int i = 0; i < test_iterations; i++) {
        ASSERT_NE(other_tree.find_intern(other_tree.root_, test_vec[i]), nullptr);
    }
}

TEST(Super_tree, calc_lsub) {
    Super_tree tree;
    int test_iterations = 100;
    std::vector<int> test_vec(test_iterations);

    srand(time(nullptr));

    for(int i = 0; i < test_iterations; i++) {
        test_vec[i] = rand();
        tree.root_ = tree.insert_intern(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    std::cout << tree.root_ -> left_ -> lsubnum_;
    std::cout << tree;

    tree.insert_intern(tree.root_, 1011);
    std::cout << tree.root_ -> left_ -> lsubnum_;
    std::cout << tree;

    tree.insert_intern(tree.root_, 1);
    std::cout << tree.root_ -> left_ -> lsubnum_;
    std::cout << tree;
}

TEST(Super_tree, k_min) {
    Super_tree tree;
    int test_iterations = 100;
    std::vector<int> test_vec(test_iterations);

    srand(time(nullptr));

    for(int i = 0; i < test_iterations; i++) {
        test_vec[i] = rand();
        tree.root_ = tree.insert_intern(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    std::sort(test_vec.begin(), test_vec.end());

    for(int elemm : test_vec)
        std::cout << elemm << " ";
    std::cout << std::endl;

    for(int i = 0; i < test_iterations; i++) {
        AVL_node_t* k_min = tree.k_min_intern(i+1, tree.root_);
        ASSERT_TRUE(errno != EINVAL);
        ASSERT_EQ(k_min->key_, test_vec[i]);
    }
}

TEST(Super_tree, less_than) {
    Super_tree tree;
    int test_iterations = 100;
    std::vector<int> test_vec(test_iterations);

    srand(time(nullptr));

    for(int i = 0; i < test_iterations; i++) {
        test_vec[i] = rand() % 1000000;
        tree.root_ = tree.insert_intern(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    std::sort(test_vec.begin(), test_vec.end());

    for(int elemm : test_vec)
        std::cout << elemm << " ";
    std::cout << std::endl;

    std::cout << tree << std::endl;

    for(int i = 0; i < test_iterations; i++) {
        int minN = tree.less_than_intern(test_vec[i], tree.root_, 0);
        ASSERT_TRUE(errno != EINVAL);
        ASSERT_EQ(minN, i);
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}