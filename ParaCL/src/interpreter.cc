#include "PCL_Driver.hpp"
#include <fstream>

int main(int argc, const char* argv[]) {
    if(argc != 2) {
        std::cerr << "usage: ./" << argv[0] << " <filename>" << std::endl;
    } else {
        std::ifstream input(argv[1]);
        if (!input) {
            std::cerr << "can't open " << argv[1] << std::endl;
            return 0;
        }
        yy::PCL_Driver driver(&input);
        driver.parse();

    #ifdef _DEBUG
        driver.root_ -> print();
        driver.symtbl_.print();
    #endif

        if(driver.err_counter_ == 0 && driver.root_)
            driver.interpretate(driver.root_);
    }

    return 0;
}