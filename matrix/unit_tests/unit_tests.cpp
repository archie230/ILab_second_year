#include "../matrix.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <unistd.h>

using namespace cxx_containers;

const char* inv_square_matrix           = "../unit_tests/test_data/invertable_square_matrix";
const char* square_matrix               = "../unit_tests/test_data/square_matrix";
const char* square_matrixs_determinants = "../unit_tests/test_data/square_matrixs_determinants";
const char* eliminated                  = "../unit_tests/test_data/eliminated";

TEST(matrix, LU_decomposition) {
    std::ifstream fstr_input(inv_square_matrix);
    if(!fstr_input) {
        std::cerr << "can't open " << inv_square_matrix << std::endl;
        return;
    }

    Matrix<float> matrix(3, 3);

    int matrix_num = 0;
    fstr_input >> matrix_num;

    for(int i = 0; i < matrix_num; i++) {
        fstr_input >> matrix;
        std::pair<Matrix<float>, Matrix<float>> LU = matrix.LU_decomposition();
        ASSERT_EQ(matrix, LU.first * LU.second);
    }

    fstr_input.close();
}

TEST(matrix, determinant) {
    std::ifstream fstr_input(square_matrix);
    std::ifstream fstr_determinants(square_matrixs_determinants);
    if(!fstr_input) {
        std::cerr << "can't open " << square_matrix << std::endl;
        return;
    }
    if(!fstr_determinants) {
        std::cerr << "can't open " << square_matrixs_determinants << std::endl;
        return;
    }

    Matrix<float> matrix(4, 4);

    int matrix_num = 0;
    float answ = 0;
    fstr_input >> matrix_num;

    for(int i = 0; i < matrix_num; i++) {
        fstr_input >> matrix;
        fstr_determinants >> answ;
        float determinant = matrix.determinant();
        ASSERT_EQ(determinant, answ);
    }

    fstr_input.close();
    fstr_determinants.close();
}

TEST(matrix, gaussian_elimination) {
    std::ifstream fstr_input(square_matrix);
    std::ifstream fstr_eliminated(eliminated);
    if(!fstr_eliminated) {
        std::cerr << "can't open " << eliminated << std::endl;
        return;
    }
    if(!fstr_input) {
        std::cerr << "can't open " << square_matrix << std::endl;
        return;
    }

    Matrix<float> matrix(4, 4);
    Matrix<float> matrix_eliminated(4, 4);

    int matrix_num = 0;
    fstr_input >> matrix_num;

    for(int i = 0; i < matrix_num; i++) {
        fstr_input >> matrix;
        fstr_eliminated >> matrix_eliminated;
        matrix.gaussian_elimination();
        ASSERT_EQ(matrix, matrix_eliminated);
    }

    fstr_input.close();
    fstr_eliminated.close();
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}