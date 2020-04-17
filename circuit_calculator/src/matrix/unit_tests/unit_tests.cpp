#include "../matrix.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <unistd.h>
#include <vector>

using namespace cxx_containers;

const char* inv_square_matrix           = "../unit_tests/test_data/invertable_square_matrix";
const char* square_matrix               = "../unit_tests/test_data/square_matrix";
const char* square_matrixs_determinants = "../unit_tests/test_data/square_matrixs_determinants";
const char* eliminated                  = "../unit_tests/test_data/eliminated";


using size_type = MatrixBuf<int>::size_type ;

TEST(matrixBuf, ctors) {
    MatrixBuf<int> buf(21, 1);
    for (size_type i = 0; i < buf.size(); ++i)
        ASSERT_EQ(buf[i], 1);

    auto other = buf;
    for (size_type i = 0; i < buf.size(); ++i)
        ASSERT_EQ(buf[i], other[i]);

    buf.resize(2);

    other = std::move(buf);
    ASSERT_EQ(buf.size(), 0);
    ASSERT_EQ(other.size(), 2);
}

TEST(matrix, memory_managment) {
    Matrix<int> m1({3, 7}, 1);
    for (size_type i = 0; i < m1.size().first; ++i)
        for (size_type j = 0; j < m1.size().second; ++j)
            ASSERT_EQ(m1[i][j], 1);

    auto m2 = m1;
    ASSERT_EQ(m2, m1);
    std::swap(m2, m1);
    ASSERT_EQ(m2, m1);
}

TEST(matrix, range_ctor) {
    std::vector<int> v = {1, 2, 3 ,4};
    Matrix<int> mx1({2, 2});

    mx1[0][0] = 1;
    mx1[0][1] = 2;
    mx1[1][0] = 3;
    mx1[1][1] = 4;

    Matrix<int> mx2(v.begin(), v.end(), {2, 2});
    ASSERT_EQ(mx1, mx2);
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

    Matrix<float> matrix({4, 4});

    int matrix_num = 0;
    double answ = 0;
    fstr_input >> matrix_num;

    for(int i = 0; i < matrix_num; i++) {
        fstr_input >> matrix;
        fstr_determinants >> answ;
        auto determinant = matrix.determinant();
        ASSERT_TRUE(SimpleTraits<double>::eq(determinant, answ));
    }

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

    Matrix<float> matrix({4, 4});
    Matrix<float> matrix_eliminated({4, 4});

    int matrix_num = 0;
    fstr_input >> matrix_num;

    for(int i = 0; i < matrix_num; i++) {
        fstr_input >> matrix;
        fstr_eliminated >> matrix_eliminated;
        matrix.gaussian_elimination();
        ASSERT_EQ(matrix, matrix_eliminated);
    }

}

TEST(matrix, LU_decomposition) {
    std::srand(time(nullptr));
    std::array<double, 64> arr;
    std::generate(arr.begin(), arr.end(), [] () {return std::rand() % 10000;});

    Matrix<double> m(arr.begin(), arr.end(), {8, 8});

    auto [L,U] = m.LU_decomposition();

    ASSERT_EQ(L*U, m);
}

TEST(matrix, SolveSystem) {
    {
        std::array<double, 9> a = {1,2,0,3,4,4,5,6,3};
        Matrix A(a.begin(), a.end(), {3, 3});
        Matrix<double> b({3, 1});
        b[0][0] = 3;
        b[1][0] = 7;
        b[2][0] = 8;

        Matrix<double> expect({3, 1});
        expect[0][0] = -1.4;
        expect[1][0] = 2.2;
        expect[2][0] = 0.6;

        auto answ = cxx_containers::SolveSystem(A, b);
        ASSERT_EQ(answ, expect);
    }

    {
        std::array<double, 9> a = {2.0+4.0+22.0, -22.0, 4.0, -22.0, 22.0+60.0+5.0, 60.0, 4.0, 60.0, 4.0+60.0+10.0};
        std::array<double, 3> b = {12, 0, 0};
        std::array<double , 3> ans = {1.07446,0.707219,-0.631499};
        Matrix A(a.begin(), a.end(), {3, 3});
        Matrix B(b.begin(), b.end(), {3, 1});
        Matrix answ(ans.begin(), ans.end(), {3, 1});

        ASSERT_EQ(cxx_containers::SolveSystem(A,B), answ);
    }


}

TEST (matrix, multiplication) {
    std::array<int, 6> a = {1, 2, 3, 4, 5, 6};
    std::array<int, 2> b = {1, 2};
    std::array<int, 3> answ = {5, 11, 17};

    Matrix<int> ma(a.begin(), a.end(), {3, 2});
    Matrix<int> mb(b.begin(), b.end(), {2, 1});
    Matrix<int> mansw(answ.begin(), answ.end(), {answ.size(), 1});

    ASSERT_EQ(ma * mb, mansw);


    std::array<int, 4> a1 = {3, 2, 0, -1};
    std::array<int, 4> b1 = {-1, 1, 0, 2};
    std::array<int, 16> answ1 = {-3,3,0,6,-2,2,0,4,0,0,0,0,1,-1,0,-2};
    Matrix<int> ma1(a1.begin(), a1.end(), {a1.size(), 1});
    Matrix<int> mb1(b1.begin(), b1.end(), {1, b1.size()});
    Matrix<int> mansw1(answ1.begin(), answ1.end(), {4, 4});

    ASSERT_EQ(ma1*mb1, mansw1);
}

TEST(matrix, transp) {
    std::array<int, 6> a = {1, 2, 3, 4, 5, 6};
    Matrix<int> ma(a.begin(), a.end(), {3, 2});
    auto transposed = ma.transpose();

    for (size_type i = 0; i < ma.size().first; ++i)
        for (size_type j = 0; j < ma.size().second; ++j)
                ASSERT_EQ(transposed[j][i], ma[i][j]);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}