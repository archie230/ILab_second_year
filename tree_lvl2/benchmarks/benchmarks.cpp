#include "../super_search.hpp"
#include <iostream>
#include <cassert>
#include <set>
#include <cstdlib>
#include <vector>
#include <set>
#include <chrono>

using namespace cxx_containers;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

long get_number(const char* str) {
    char* str_end;
    long number = strtol(str, &str_end, 10);

    if ((str_end == str) || (errno != 0 && number == 0))
        return -1;

    return number;
}

void fill_unique_data(std::vector<int>& vec) {
    srand(time(nullptr));
    std::set<int> used;
    int rand_num = 0;

    for(int& elem : vec) {
        for(;;) {
            rand_num = rand();
            if(used.find(rand_num) != used.end()) continue;
            break;
        }
        elem = rand_num;
        used.insert(rand_num);
    }
}

int less_than(int elem, std::set<int>& stl_search) {
    int k = 0;
    std::less<int> comp;
    for(int x : stl_search) {
        if (!comp(x, elem)) break;
        k++;
    }
    return k;
}

int k_min(int k, std::set<int>& stl_search) {
    int i = 1;
    for(int x : stl_search) {
        if(i == k)
            return x;
        i++;
    }
    abort();
}

void benchmark(int insert_iteratinos) {
    std::set<int, std::less<int>>       stl_search;
    SuperSearch<int, std::less<int>>    super_search;

    std::vector<int> data(insert_iteratinos);
    data.resize(insert_iteratinos);
    fill_unique_data(data);

    for(int elem : data) {
        stl_search.insert(elem);
        super_search.push(elem);
    }

    std::sort(data.begin(), data.end());
    /* less_than benchmark */
    // super_search
    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < insert_iteratinos; i++)
            assert(super_search.less_than(data[i]) == i);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "super search less_than | " <<
                insert_iteratinos << " elements time[us]: " << duration.count() << std::endl;
    }
    //

    // stl_search
    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < insert_iteratinos; i++)
            assert(less_than(data[i], stl_search) == i);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "stl search less_than | " <<
                  insert_iteratinos << " elements time[us]: " << duration.count() << std::endl;
    }
    //
    /**/
    
    /* k min benchmark */
    // super_search
    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < insert_iteratinos; i++)
            assert(super_search.k_min(i+1) == data[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "super search k_min | " <<
                  insert_iteratinos << " elements time[us]: " << duration.count() << std::endl;
    }
    //

    // stl_search
    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < insert_iteratinos; i++)
            assert(k_min(i+1, stl_search) == data[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "stl search k_min | " <<
                  insert_iteratinos << " elements time[us]: " << duration.count() << std::endl;
    }
    //
    /**/
}


int main(int argc, char* argv[]) {
    assert(argc == 2);
    long insert_iterations = get_number(argv[1]);
    assert(insert_iterations >= 0);

    benchmark(insert_iterations);
}