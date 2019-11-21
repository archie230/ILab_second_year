#pragma once

#include <iostream>
#include <cerrno>
#include <cmath>
#include <cassert>

namespace cxx_containers {
    /**
     *
     * @tparam T should be able to float point arithmetic
     */

    const float TOLERANCE = 5e-3;

    template<typename T>
    static bool nearly_equal(const T& a, const T& b){
        return fabs(a - b) <= TOLERANCE;
    }

    template<typename T>
    class Matrix final {
        T*  buf_        = nullptr;    // ptr to buf
        T** row_ptrs_   = nullptr;    // row pointers
        int rows_       = 0;
        int cols_       = 0;

    public:
        Matrix() = default;

        Matrix(int rows, int cols)
            :
                rows_       (rows),
                cols_       (cols),
                buf_        (nullptr),
                row_ptrs_   (nullptr)
        {
            if((rows_ == 0) || (cols_ == 0) || (rows_ < 0) || (cols_ < 0)) {
                rows_ = cols_ = 0;
                return;
            }

            buf_        = new T [rows_ * cols_]{};
            row_ptrs_   = new T* [rows_];

            assert(buf_ && row_ptrs_);

            for(int i = 0; i < rows; i++)
                row_ptrs_[i] = buf_ + i * cols_;
        }

        Matrix(const T* buf, int rows, int cols)
            :
                Matrix(rows, cols)
        {
            if(!buf)
                return;
            for(int i = 0; i < rows_*cols_; i++)
                buf_[i] = buf[i];
        }

        Matrix(const Matrix& other)
            :
                Matrix(other.rows_, other.cols_)
        {
            if(!buf_)
                return;

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    row_ptrs_[i][j] = other.row_ptrs_[i][j];
        }

        Matrix(Matrix&& other) noexcept
            :
                buf_(other.buf_),
                row_ptrs_(other.row_ptrs_),
                rows_(other.rows_),
                cols_(other.cols_)
        {
            other.buf_ = nullptr, other.row_ptrs_ = nullptr;
            other.rows_ = other.cols_ = 0;
        }

        ~Matrix() {
            delete [] buf_;
            delete [] row_ptrs_;
        }

        Matrix& operator= (const Matrix& other) {
            if(this == &other)
                return *this;

            resize(other.rows_, other.cols_);

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    row_ptrs_[i][j] = other.row_ptrs_[i][j];
                
            return *this;
        }

        Matrix& operator= (Matrix&& other) noexcept {
            if(this == &other)
                return *this;

            delete [] buf_;
            delete [] row_ptrs_;

            buf_        = other.buf_;
            row_ptrs_   = other.row_ptrs_;
            rows_       = other.rows_;
            cols_       = other.cols_;

            other.buf_ = nullptr, other.row_ptrs_ = nullptr;
            other.rows_ = other.cols_ = 0;

            return *this;
        }

        Matrix& operator*= (const Matrix& other) {
            if(other.rows_ != cols_) {
                std::cerr << "size doesn't match" << std::endl;
                errno = EINVAL;
                return *this;
            }

            Matrix tmp(*this);

            resize(rows_, other.cols_);

            if(!row_ptrs_)
                return *this;

            transpose_multiplication(tmp.buf_, other.buf_, buf_, rows_, tmp.cols_, cols_);

            return *this;
        }

        Matrix& operator-= (const Matrix& other) {
            if((rows_ != other.rows_) || (cols_ != other.cols_)) {
                errno = EINVAL;
                std::cerr << "size doesn't match" << std::endl;
                return *this;
            }

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    row_ptrs_[i][j] -= other.row_ptrs_[i][j];

            return *this;
        }

        Matrix& operator+= (const Matrix& other) {
            if((rows_ != other.rows_) || (cols_ != other.cols_)) {
                errno = EINVAL;
                std::cerr << "size doesn't match" << std::endl;
                return *this;
            }

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    row_ptrs_[i][j] += other.row_ptrs_[i][j];

            return *this;
        }

        bool equal(const Matrix& other) const {
            if((rows_ != other.rows_) || (cols_ != other.cols_))
                return false;

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++) {
                    if(!nearly_equal<T>(row_ptrs_[i][j],  other.row_ptrs_[i][j]))
                        return false;
                }

            return true;
        }

        const T* operator[] (int i) const {
            return row_ptrs_[i];
        };

        void set_zero() {
            if(!row_ptrs_)
                return;

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    row_ptrs_[i][j] = 0;
        }

        void set(const T& elem, int m, int n) {
            if ((m >= rows_) || (n >= cols_) || (m < 0) || (n < 0))
                return;
            row_ptrs_[m][n] = elem;
        }

        void switch_rows(int row1, int row2) {
            if((row1 < 0) || (row2 < 0) || (row1 >= rows_) || (row2 >= rows_))
                return;

            T* tmp = row_ptrs_[row1];
            row_ptrs_[row1] = row_ptrs_[row2];
            row_ptrs_[row2] = tmp;
        }

        // if our matrix is NxN there is a matrix pair
        // *this = L*U, L - lower triangle matrix, U - upper triangle matrix
        // if *this matrix determinant equals zero then L and U are both NxN zero matrix
        // if all main minors aren't invertable : return L = 0 and U = 0
        std::pair<Matrix<float>, Matrix<float>> LU_decomposition() const {
            if(rows_ != cols_) {
                errno = EINVAL;
                return {};
            }

            Matrix<float> L(rows_, rows_);
            Matrix<float> U(rows_, rows_);

            int i = 0, j = 0, k = 0;
            for (i = 0; i < rows_; i++) {
                for (j = 0; j < rows_; j++) {
                    if (j < i)
                        L.row_ptrs_[j][i] = 0;
                    else {
                        L.row_ptrs_[j][i] = row_ptrs_[j][i];
                        for (k = 0; k < i; k++) {
                            L.row_ptrs_[j][i] = L.row_ptrs_[j][i] - L.row_ptrs_[j][k] * U.row_ptrs_[k][i];
                        }
                    }
                }
                for (j = 0; j < rows_; j++) {
                    if (j < i)
                        U.row_ptrs_[i][j] = 0;
                    else if (j == i)
                        U.row_ptrs_[i][j] = 1;
                    else {
                        if(nearly_equal<T>(L.row_ptrs_[i][i], 0)) {
                            L.set_zero();
                            U.set_zero();
                            return {L, U};
                        }

                        U.row_ptrs_[i][j] = row_ptrs_[i][j] / L.row_ptrs_[i][i];
                        for (k = 0; k < i; k++) {
                            U.row_ptrs_[i][j] = U.row_ptrs_[i][j]
                                    - ((L.row_ptrs_[i][k] * U.row_ptrs_[k][j]) / L.row_ptrs_[i][i]);
                        }
                    }
                }
            }
            return {L, U};
        }

        /**
         * normally makes gaussian elimination on matrix
         * @return sign of new determinant or -2 in case of err
         */
        int gaussian_elimination() {
            if(cols_ != rows_)
                return -2;
            if((rows_ == 0) || (rows_ == 1))
                return 1;

            int sign = 1, switch_row = -1;
            float multiplier = 1;

            for(int i = 0; i < rows_; i++) {
                if(nearly_equal<T>(row_ptrs_[i][i], 0)) {
                    for(int j = i + 1; j < rows_; j++)
                        if(!nearly_equal<T>(row_ptrs_[j][i], 0)) {
                            switch_row = j;
                            break;
                        }

                    if(switch_row != -1) {
                        switch_rows(i, switch_row);
                        sign *= -1;
                        switch_row = -1;
                    }
                    else
                        continue;
                }
                for(int j = i + 1; j < rows_; j++) {
                    multiplier = row_ptrs_[j][i] / row_ptrs_ [i][i];
                    for(int k = i; k < rows_; k++)
                        row_ptrs_[j][k] -= multiplier * row_ptrs_[i][k];
                }
            }
            return sign;
        }

        float determinant() const {
            if(cols_ != rows_) {
                errno = EPERM;
                return -1;
            }

            if(cols_ == 0)
                return 0;

            if(cols_ == 1)
                return row_ptrs_[0][0];

            if(rows_ == 2)
                return row_ptrs_[0][0] * row_ptrs_[1][1] - row_ptrs_[1][0] * row_ptrs_[0][1];

            Matrix tmp(*this);
            int sign = tmp.gaussian_elimination();
            float determinant = 1;

            for(int i = 0; i < rows_; i++)
                determinant *= tmp.row_ptrs_[i][i];

            return sign * determinant;
        }

        std::ostream& dump(std::ostream& os) const {
            for(int i = 0; i < rows_; i++) {
                for(int j = 0; j < cols_; j++)
                    os << row_ptrs_[i][j] << " ";
                os << std::endl;
            }
            return os;
        }

        std::istream& scan(std::istream& is) {
            int rows = 0, cols = 0;
            is >> rows >> cols;
            if( (rows < 0) || (cols < 0) || ((rows == 0) && (cols != 0))
                                || ((rows != 0) && (cols == 0)) ) {
                std::cerr << "bad matrix parameters!" << std::endl;
                return is;
            }

            resize(rows, cols);

            for(int i = 0; i < rows_; i++) {
                for(int j = 0; j < cols_; j++)
                    is >> row_ptrs_[i][j];
            }
            return is;
        }

        std::pair<int, int> size() const {
            return {rows_, cols_};
        }

    private:
        void resize(int rows, int cols) {
            if ((rows < 0) || (cols < 0))
                return;

            if ((rows == 0) && (cols == 0)) {
                delete[] buf_;
                delete[] row_ptrs_;
                row_ptrs_ = nullptr;
                buf_ = nullptr;
                rows_ = cols_ = 0;
                return;
            }

            if ((rows == 0) || (cols == 0))
                return;

            if ((rows * cols) != (rows_ * cols_)) {
                delete[] buf_;
                delete[] row_ptrs_;

                buf_ = new T[rows * cols]{};
                row_ptrs_ = new T *[rows];

                assert(buf_ && row_ptrs_);

                for (int i = 0; i < rows; i++)
                    row_ptrs_[i] = buf_ + i * cols;
                rows_ = rows;
                cols_ = cols;
            } else {
                if (rows == rows_)
                    return;
                else {
                    delete[] row_ptrs_;
                    for (int i = 0; i < rows; i++)
                        row_ptrs_[i] = buf_ + i * cols;
                    rows_ = rows;
                    cols_ = cols;
                }
            }
        }

        // cache friendly multiplication
        void transpose_multiplication(const T* A, const T* B, T* C, int AX, int AY, int BY) {
            if(!(A && B && C) || AX < 0 || AY < 0 || BY < 0)
                return;

            T* tmp = new T [AY * BY];
            assert(tmp);

            for(int i = 0; i < AY; i++)
                for(int j = 0; j < BY; j++)
                    tmp[j * AY + i]  = B[i * BY + j];

            for(int i = 0; i < AX; i++)
                for(int j = 0; j < BY; j++) {
                    C[i * BY + j] = 0;
                    for(int k = 0; k < AY; k++)
                        C[i * BY + j] += A[i * AY + k] * tmp[j * AY + k];
                }

            delete [] tmp;
        }
    };

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const Matrix<T>& matrix) {
        return matrix.dump(os);
    }

    template <typename T>
    std::istream& operator>> (std::istream& is, Matrix<T>& matrix) {
        return matrix.scan(is);
    }

    template <typename T>
    Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs) {
        Matrix<T> tmp(lhs);
        return tmp *= rhs;
    }

    template <typename T>
    Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs) {
        Matrix<T> tmp(lhs);
        return tmp += rhs;
    }

    template <typename T>
    Matrix<T> operator- (const Matrix<T>& lhs, const Matrix<T>& rhs) {
        Matrix<T> tmp(lhs);
        return tmp -= rhs;
    }

    template <typename T>
    bool operator== (const Matrix<T>& lhs, const Matrix<T>& rhs) {
        return lhs.equal(rhs);
    }
}