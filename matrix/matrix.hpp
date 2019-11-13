#pragma once

#include <iostream>
#include <errno.h>
#include <cmath>

namespace cxx_containers {
    /**
     *
     * @tparam T should be able to float point arithmetic
     */

    const float TOLERANCE = 5e-3;
    static bool nearly_equal(float a, float b){
        return fabs(a - b) <= TOLERANCE;
    }

    template<typename T>
    class Matrix final {
        T** elems_ = nullptr;
        int rows_ = 0, cols_ = 0;

    public:
        Matrix() = default;

        Matrix(int rows, int cols)
            :
                rows_(rows),
                cols_(cols)
        {
            if((rows_ == 0) || (cols_ == 0)) {
                rows_ = cols_ = 0;
                elems_ = nullptr;
                return;
            }

            elems_ = new T* [rows_];
            for(int i = 0; i < rows_; i++)
                elems_[i] = new T [cols_]{};
        }

        ~Matrix() {
            if(!elems_)
                return;
            for(int i = 0; i < rows_; i++)
                delete [] elems_[i];
            delete [] elems_;
        }

        Matrix(const Matrix& other)
            :
                Matrix(other.rows_, other.cols_)
        {
            if(!elems_)
                return;

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    elems_[i][j] = other.elems_[i][j];
        }

        Matrix& operator= (const Matrix& other) {
            if(this == &other)
                return *this;

            resize(other.rows_, other.cols_);

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < rows_; j++)
                    elems_[i][j] = other.elems_[i][j];
                
            return *this;
        }

        // cache friendly multiplication
        Matrix& operator*= (const Matrix& other) {
            if(other.rows_ != cols_) {
                std::cerr << "size doesn't match" << std::endl;
                return *this;
            }

            Matrix tmp(*this);

            resize(rows_, other.cols_);

            if(!elems_)
                return *this;

            for(int i = 0; i < rows_; i++) {
                T* result_row = elems_[i];
                T* lhs_row    = tmp.elems_[i];

                for(int j = 0; j < cols_; j++)
                    result_row[j] = 0;

                for(int k = 0; k < other.rows_; k++) {
                    T* rhs_row = other.elems_[k];
                    for(int j = 0; j < cols_; j++) {
                        result_row[j] += lhs_row[k] * rhs_row[j];
                    }
                }
            }

            return *this;
        }

        Matrix& operator-= (const Matrix& other) {
            if((rows_ != other.rows_) || (cols_ != other.cols_)) {
                std::cerr << "size doesn't match" << std::endl;
                return *this;
            }

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    elems_[i][j] -= other.elems_[i][j];

            return *this;
        }

        Matrix& operator+= (const Matrix& other) {
            if((rows_ != other.rows_) || (cols_ != other.cols_)) {
                std::cerr << "size doesn't match" << std::endl;
                return *this;
            }

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    elems_[i][j] += other.elems_[i][j];

            return *this;
        }

        bool equal(const Matrix& other) const {
            if((rows_ != other.rows_) || (cols_ != other.cols_))
                return false;

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++) {
                    if(!nearly_equal(elems_[i][j],  other.elems_[i][j]))
                        return false;
                }

            return true;
        }

        void set(const T& elem, int m, int n) {
            if((m >= rows_) || (n >= cols_))
                return;

            elems_[m][n] = elem;
        }

        void set_zero() {
            if(!elems_)
                return;

            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < cols_; j++)
                    elems_[i][j] = 0;
        }

        T get(const T& elem, int m, int n) {
            if ((m >= rows_) || (n >= cols_))
                return {};
            return elems_[m][n];
        }

        const T& get(const T& elem, int m, int n) const {
            if ((m >= rows_) || (n >= cols_))
                return {};
            return elems_[m][n];
        }

        void switch_rows(int row1, int row2) {
            if((row1 < 0) || (row2 < 0) || (row1 >= rows_) || (row2 >= rows_))
                return;

            T* tmp = elems_[row1];
            elems_[row1] = elems_[row2];
            elems_[row2] = tmp;
        }

        // if our matrix is NxN there is a matrix pair
        // *this = L*U, L - lower triangle matrix, U - upper triangle matrix
        // if *this matrix determinant equals zero then L and U are both NxN zero matrix
        // if all main minors aren't invertable : return L = 0 and U = 0
        std::pair<Matrix<float>, Matrix<float>> LU_decomposition() const {
            if(rows_ != cols_) 
                return {};

            Matrix<float> L(rows_, rows_);
            Matrix<float> U(rows_, rows_);

            int i = 0, j = 0, k = 0;
            for (i = 0; i < rows_; i++) {
                for (j = 0; j < rows_; j++) {
                    if (j < i)
                        L.elems_[j][i] = 0;
                    else {
                        L.elems_[j][i] = elems_[j][i];
                        for (k = 0; k < i; k++) {
                            L.elems_[j][i] = L.elems_[j][i] - L.elems_[j][k] * U.elems_[k][i];
                        }
                    }
                }
                for (j = 0; j < rows_; j++) {
                    if (j < i)
                        U.elems_[i][j] = 0;
                    else if (j == i)
                        U.elems_[i][j] = 1;
                    else {
                        if(nearly_equal(L.elems_[i][i], 0)) {
                            L.set_zero();
                            U.set_zero();
                            return {L, U};
                        }

                        U.elems_[i][j] = elems_[i][j] / L.elems_[i][i];
                        for (k = 0; k < i; k++) {
                            U.elems_[i][j] = U.elems_[i][j]
                                    - ((L.elems_[i][k] * U.elems_[k][j]) / L.elems_[i][i]);
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
                if(nearly_equal(elems_[i][i], 0)) {
                    for(int j = i + 1; j < rows_; j++)
                        if(!nearly_equal(elems_[j][i], 0)) {
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
                    multiplier = elems_[j][i] / elems_ [i][i];
                    for(int k = i; k < rows_; k++)
                        elems_[j][k] -= multiplier * elems_[i][k];
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
                return elems_[0][0];

            if(rows_ == 2)
                return elems_[0][0] * elems_[1][1] - elems_[1][0] * elems_[0][1];

            Matrix tmp(*this);
            int sign = tmp.gaussian_elimination();
            float determinant = 1;

            for(int i = 0; i < rows_; i++)
                determinant *= tmp.elems_[i][i];

            return sign * determinant;
        }

        std::ostream& dump(std::ostream& os) const {
            for(int i = 0; i < rows_; i++) {
                for(int j = 0; j < cols_; j++)
                    os << elems_[i][j] << " ";
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
                    is >> elems_[i][j];
            }
            return is;
        }

    private:
        void resize(int rows, int cols) {
            if((rows < 0) || (cols < 0))
                return;

            if((rows == 0) && (cols == 0)) {
                for(int i = 0; i < rows_; i++)
                    delete [] elems_[i];
                delete [] elems_;
                elems_ = nullptr;
                rows_ = cols_ = 0;
                return;
            }

            if((rows == 0) || (cols == 0))
                return;

            if((rows_ != rows) || (cols_ != cols)) {
                if(rows_ == rows) {
                    for(int i = 0; i < rows_; i++) {
                        delete [] elems_[i];
                        elems_[i] = new T [cols]{};
                    }

                    cols_ = cols;
                } else if(cols_ == cols) {
                    T** new_buf = new T* [rows];

                    int range = (rows_ >= rows) ? rows : rows_;

                    for(int i = 0; i < range; i++)
                        new_buf[i] = elems_[i];

                    for(int j = range; j < rows; j++)
                        new_buf[j] = new T [cols]{};

                    delete [] elems_;

                    elems_ = new_buf;
                    rows_ = rows;
                } else {
                    for(int i = 0; i < rows_; i++)
                        delete [] elems_[i];

                    delete [] elems_;

                    rows_ = rows;
                    cols_ = cols;

                    elems_ = new T* [rows_];
                    for(int i = 0; i < rows_; i++)
                        elems_[i] = new T[cols_]{};
                }
            }
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