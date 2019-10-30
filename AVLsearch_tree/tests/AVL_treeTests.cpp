#include <gtest/gtest.h>
#include "../AVL_tree.hpp"
#include <iostream>
#include <cmath>

using namespace cxx_containers;
using AVL_TREE = AVL_tree<int, std::less<>>;
using AVL_node_t = typename AVL_TREE::node_t;

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

std::ostream& operator<<(std::ostream& os, const AVL_TREE& tree) {
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

TEST(AVL_tree, insert) {
    AVL_TREE tree;
    srand(time(nullptr));

    for(int i = 0; i < 100; i++) {
        tree.root_ = tree.insert(tree.root_, rand());
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }
}

TEST(AVL_tree, remove) {
    AVL_TREE tree;
    std::vector<int> test_vec(100);
    std::set<int> used_numders;

    srand(time(nullptr));

    for(int i = 0; i < 100; i++) {
        test_vec[i] = rand();
        tree.root_ = tree.insert(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    std::cout << tree;

    for(int i = 0; i < 100; i++) {
        int rand_index = rand() % 100;

        while(used_numders.find(rand_index) != used_numders.end())
            rand_index = rand() % 100;

        used_numders.insert(rand_index);

        tree.root_ = tree.remove(tree.root_, test_vec[rand_index]);
        //std::cout << tree;
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }
    std::cout << tree;
}

TEST(AVL_tree, copy_ctor) {
    AVL_TREE tree;
    std::vector<int> test_vec(100);

    srand(time(nullptr));

    for(int i = 0; i < 100; i++) {
        test_vec[i] = rand();
        tree.root_ = tree.insert(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    AVL_TREE copy_tree(tree);

    for(int i = 0; i < 100; i++) {
        ASSERT_NE(copy_tree.find(copy_tree.root_, test_vec[i]), nullptr);
    }
}

TEST(AVL_tree, assignment_oper) {
    AVL_TREE tree;
    std::vector<int> test_vec(100);

    srand(time(nullptr));

    for(int i = 0; i < 100; i++) {
        test_vec[i] = rand();
        tree.root_ = tree.insert(tree.root_,test_vec[i]);
        ASSERT_TRUE(Is_Balanced(tree.root_));
    }

    AVL_TREE other_tree = tree;

    for(int i = 0; i < 100; i++) {
        ASSERT_NE(other_tree.find(other_tree.root_, test_vec[i]), nullptr);
    }

    other_tree = tree;
    for(int i = 0; i < 100; i++) {
        ASSERT_NE(other_tree.find(other_tree.root_, test_vec[i]), nullptr);
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}