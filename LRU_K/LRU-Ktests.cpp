#define _DEBUG
#include "LRU-K.hpp"
#undef _DEBUG
#include <gtest/gtest.h>

//-------------Functions for debugging------------
#define CREATE_TIME_Q(...) ({std::queue<uint32_t> time_q;\
                            set_time_queue(time_q, __VA_ARGS__);\
                            time_q;})

//recursion bottom
void set_time_queue(std::queue<uint32_t> time_q) {}

template <typename ...Types>
void set_time_queue(std::queue<uint32_t>& time_q ,uint32_t arg1, Types... args) {
    time_q.push(arg1);
    set_time_queue(time_q, args...);
}

bool operator==(const typename LRUK_cache<int>::cache_node_t& left,
                const typename LRUK_cache<int>::cache_node_t& right) {
    return (left.data_ == right.data_) && (left.time_queue_ == right.time_queue_);
}
//-------------------------------------------------

//checking that LRU-K algorithm works just right
TEST(cache_test, step_by_step) {
#define EXPECT_CACHE_LIST(...) ({LRUK_cache<int>::cachelist_t expect = {__VA_ARGS__};\
                                expect;})
    LRUK_cache<int> cache(3, 2);
    std::vector<int> requests = {3,4,1,4,4,4,3,2,7,6,7,7,2,2,13,8};
    uint32_t time = 1;

    cache.lookup(requests[time-1], time); ++time;
    cache.lookup(requests[time-1], time); ++time;
    cache.lookup(requests[time-1], time); ++time;

    //expecting cache: 1 4 3
    //coming: 4,4,4,3,2,7,6,7,7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({1, CREATE_TIME_Q(3)},
            {4, CREATE_TIME_Q(2)}, {3, CREATE_TIME_Q(1)}));


    cache.lookup(requests[time-1], time); ++time;
    //expecting cache: 1 4 3
    //coming: 4,4,3,2,7,6,7,7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({1, CREATE_TIME_Q(3)},
            {4, CREATE_TIME_Q(2, 4)}, {3, CREATE_TIME_Q(1)}));


    cache.lookup(requests[time-1], time); ++time;
    //expecting cache: 4 1 3
    //coming: 4,3,2,7,6,7,7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({4, CREATE_TIME_Q(4, 5)},
            {1, CREATE_TIME_Q(3)}, {3, CREATE_TIME_Q(1)}));

    cache.lookup(requests[time-1], time); ++time;
    //expecting cache: 4 1 3
    //coming: 3,2,7,6,7,7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({4, CREATE_TIME_Q(5, 6)},
            {1, CREATE_TIME_Q(3)}, {3, CREATE_TIME_Q(1)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 4 1 3
    //coming: 2,7,6,7,7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({4, CREATE_TIME_Q(5, 6)},
            {1, CREATE_TIME_Q(3)}, {3, CREATE_TIME_Q(1, 7)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 2 4 1
    //coming: 7,6,7,7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({2, CREATE_TIME_Q(8)},
            {4, CREATE_TIME_Q(5, 6)}, {1, CREATE_TIME_Q(3)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 7 2 4
    //coming: 6,7,7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({7, CREATE_TIME_Q(9)},
            {2, CREATE_TIME_Q(8)}, {4, CREATE_TIME_Q(5, 6)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 6 7 2
    //coming: 7,7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({6, CREATE_TIME_Q(10)},
            {7, CREATE_TIME_Q(9)}, {2, CREATE_TIME_Q(8)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 6 7 2
    //coming: 7,2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({6, CREATE_TIME_Q(10)},
            {7, CREATE_TIME_Q(9, 11)}, {2, CREATE_TIME_Q(8)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 7 6 2
    //coming: 2,2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({7, CREATE_TIME_Q(11, 12)},
            {6, CREATE_TIME_Q(10)}, {2, CREATE_TIME_Q(8)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 7 6 2
    //coming: 2,13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({7, CREATE_TIME_Q(11, 12)},
            {6, CREATE_TIME_Q(10)}, {2, CREATE_TIME_Q(8, 13)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 2 7 6
    //coming: 13,8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({2, CREATE_TIME_Q(13, 14)},
            {7, CREATE_TIME_Q(11, 12)}, {6, CREATE_TIME_Q(10)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 13 2 7
    //coming: 8
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({13, CREATE_TIME_Q(15)},
            {2, CREATE_TIME_Q(13, 14)}, {7, CREATE_TIME_Q(11, 12)}));

    cache.lookup(requests[time - 1], time); ++time;
    //expecting cache: 8 13 2
    //coming:
    ASSERT_EQ(cache.cachelist_, EXPECT_CACHE_LIST({8, CREATE_TIME_Q(16)},
            {13, CREATE_TIME_Q(15)}, {2, CREATE_TIME_Q(13, 14)}));

#undef EXPECT_CACHE_LIST
}

TEST(cache_test, cache_node_greater_operatr) {
    LRUK_cache<int>::cache_node_t node1, node2;
    node1.time_queue_.push(10);
    node2.time_queue_.push(3);
    ASSERT_TRUE(node1 > node2);
}

TEST(cache_test, insert_by_time) {
    LRUK_cache<int> cache(3, 2);

    cache.cachelist_ = {{6, CREATE_TIME_Q(7, 3)}, {4, CREATE_TIME_Q(2)},
                        {31, CREATE_TIME_Q(1)}, {88, CREATE_TIME_Q(6)}};

    LRUK_cache<int>::cachelist_t exp_list =
            {{6, CREATE_TIME_Q(7, 3)}, {88, CREATE_TIME_Q(6)},
             {4, CREATE_TIME_Q(2)}, {31, CREATE_TIME_Q(1)}};

    cache.insert_by_time_in_cache(--cache.cachelist_.end());
    ASSERT_EQ(cache.cachelist_, exp_list);
}

TEST(cache_test, cache_3_lru_2_test) {
    LRUK_cache<int> cache(3, 2);
    std::vector<int> requests_vector = {1,2,3,3,2,1,5};
    EXPECT_EQ(cache.cache_hit_num(requests_vector), 3);
}

TEST(cache_test, cache_6_lru_3_test) {
    LRUK_cache<int> cache(6, 3);
    std::vector<int> requests_vector = {1,2,3,4,5,8,6,5,5,5,193,6,1,3,4,5,2};
    EXPECT_EQ(cache.cache_hit_num(requests_vector), requests_vector.size() - 12);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#undef CREATE_TIME_Q