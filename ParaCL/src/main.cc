#include "PCL_Driver.hpp"
#include "Interpreter.hpp"
#include <fstream>

int main(int argc, const char* argv[]) {

    try {

        if (argc != 2)
            std::cerr << "usage: ./" << argv[0] << " <filename>" << std::endl;
        else {
            std::ifstream input(argv[1]);
            if (!input) {
                std::cerr << "can't open " << argv[1] << std::endl;
                return 1;
        }

            yy::PCL_Driver driver(&input);
            driver.parse();

#ifdef DEBUG
            std::cout << "root:" << std::hex << driver.root_ << std::dec << std::endl;
            if(driver.root_)
                driver.root_ -> print();
            driver.symtbl_.print();
#endif
            if (driver.err_counter_ == 0) {
                assert(driver.env_.size() == 1);
                yy::Interpreter interpreter(driver.root_, driver.symtbl_, driver.env_[0], 2500);
                interpreter.interpretate();
            }
        }

        return 0;
    }

    catch(const std::exception& exc) {
        std::cerr << "caught exception. exception what: ";
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    catch(...) {
        std::cerr << "caught exception" << std::endl;
        return 1;
    }

}