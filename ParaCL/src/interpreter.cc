#include "PCL_Driver.hpp"
#include <fstream>

int main(int argc, const char* argv[]) {

    try {
        if (argc != 2) {
            std::cerr << "usage: ./" << argv[0] << " <filename>" << std::endl;
        } else {
            std::ifstream input(argv[1]);
            if (!input) {
                std::cerr << "can't open " << argv[1] << std::endl;
                return 0;
            }
            yy::PCL_Driver driver(&input);
            driver.parse();

#ifdef DEBUG
            std::cout << "root:" << std::hex << driver.root_ << std::dec << std::endl;
            if(driver.root_)
                driver.root_ -> print();
            driver.symtbl_.print();
#endif

            driver.interpretate(driver.root_);
        }

        return 0;
    }

    catch(const std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }

    catch(...) { return 1; }
}