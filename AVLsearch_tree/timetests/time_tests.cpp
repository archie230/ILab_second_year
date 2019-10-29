#include <chrono>
#include <set>
#include <iostream>
#include <climits>
#include "../search_tree.hpp"
#include <vector>
#include <cassert>

using cxx_containers::SearchTree;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

long int get_number(char* str) {
    char* str_end;
    long int number = strtol(str, &str_end, 10);

    if (errno == ERANGE && (number == LONG_MAX || number == LONG_MIN)) {
        return -1;
    }

    if ((str_end == str) || (errno != 0 && number == 0)) {
        return -1;
    }

    return number;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        errno = EINVAL;
        perror("");
        exit(EXIT_FAILURE);
    }
    
    std::set<int> set;
    SearchTree<int> bst;

    long int elem_number = get_number(argv[1]);
    assert(elem_number >= 0);
    
    std::vector<int> test_vec(elem_number);
    std::vector<int> pop_vec(elem_number);

    srand(time(nullptr));

    // setting insert data
    for(int i = 0; i < elem_number; i++)
        test_vec[i] = rand();

    // setting pop data order
    for(int i = 0; i < elem_number; i++) {
        std::set<int> used_numbers;
        int rand_index = rand() % elem_number;

        while (used_numbers.find(rand_index) != used_numbers.end())
            rand_index = rand() % elem_number;

        used_numbers.insert(rand_index);

        pop_vec[i] = test_vec[rand_index];
    }

    //inserting elements
    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < elem_number; i++)
            bst.push(test_vec[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "my tree inserting " << elem_number << " elements time: " << duration.count() << std::endl;
    }

    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < elem_number; i++)
            set.insert(test_vec[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "set inserting " << elem_number << " elements time: " << duration.count() << std::endl;
    }

    // find elem
    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < elem_number; i++)
            bst.exists(pop_vec[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "my tree find " << elem_number << " elements time: " << duration.count() << std::endl;
    }

    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < elem_number; i++)
            set.find(pop_vec[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "set find " << elem_number << " elements time: " << duration.count() << std::endl;
    }


    //deleting elements
    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < elem_number; i++)
            bst.remove(pop_vec[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "my tree delete " << elem_number << " elements time: " << duration.count() << std::endl;
    }

    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < elem_number; i++)
            set.erase(pop_vec[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "set delete " << elem_number << " elements time: " << duration.count() << std::endl;
    }

    return 0;
}