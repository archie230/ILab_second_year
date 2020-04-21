#include <iostream>
#include <fstream>
#include "Circuit.hpp"

using Circuit::Calculator;
using Circuit::Parser;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file name>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Can't open " << argv[1] << std::endl;
        std::cerr << "Usage: " << argv[0] << " <input file name>" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        Calculator calculator{&input};
        calculator.solve_circuit();
    }

    catch (std::exception& exc) {
        std::cerr << "Check input correctness //" << "what: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    catch (...) {
        std::cerr << "Check input correctness" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}