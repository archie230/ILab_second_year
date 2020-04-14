#pragma once

#include <cassert>
#include <iostream>
#include <cmath>

namespace cxx_containers {
    /**
     * C++17 required
     * @tparam T should be able to float point arithmetic
     */

	template <typename T, typename ... Ts> 
	void construct (T *p, Ts&& ... values) {
		new (p) T (std::forward<Ts>(values)...);
	}

	template <class T> 
	void destroy(T* p) {
		p->~T();
	}

	template <typename FwdIter> 
	void destroy (FwdIter first, FwdIter last) {
		while (first++ != last)
	 		destroy (&*first);
	}

    template <typename FwdIt>
    using value_type = typename std::iterator_traits<FwdIt>::value_type ;

    template <typename T>
    class MatrixBuf final {
    public:
        using size_type = size_t;
        using elem_type = T;
    private:
        T* buf_;
        size_type size_;
    public:
        explicit MatrixBuf(size_type size)
                :
                buf_((size == 0) ?
                     nullptr : static_cast<T*>(::operator new (sizeof(T)*size))),
                size_(size)
        {
            for (size_type i = 0; i < size_; ++i) {
                try {
                    construct(buf_ + i);
                } catch (...) {
                    destroy(buf_, buf_+i);
                    ::operator delete(buf_);
                    buf_ = nullptr;
                    size_ = 0;
                    throw;
                }
            }
        }

        MatrixBuf(size_type size, const T& arg)
            :
                buf_((size == 0) ?
                    nullptr : static_cast<T*>(::operator new (sizeof(T)*size))),
                size_(size)
        {
        	for (size_type i = 0; i < size_; ++i) {
        		try {
        			construct(buf_ + i, arg);
    			} catch (...) {
                    destroy(buf_, buf_+i);
                    ::operator delete(buf_);
                    buf_ = nullptr;
                    size_ = 0;
                    throw;
                }
        	}
        }

        template <typename FwdIt,
                typename = std::_RequireInputIter<FwdIt>>
        MatrixBuf(FwdIt first, FwdIt last)
            :
                buf_((std::distance(first, last) == 0) ?
                    nullptr : static_cast<T*>(::operator new (sizeof(T)*std::distance(first, last)))),
                size_(std::distance(first, last))
        {
            for (size_type i = 0; i < size_; ++i) {
                try {
                    construct(buf_ + i, *(first++));
                } catch (...) {
                    destroy(buf_, buf_+i);
                    ::operator delete(buf_);
                    buf_ = nullptr;
                    size_ = 0;
                    throw;
                }
            }
        }

        ~MatrixBuf() noexcept {
            destroy(buf_, buf_ + size_);
            ::operator delete(buf_);
        }

        MatrixBuf(const MatrixBuf& other)
            :
                buf_((other.size_ == 0) ?
                    nullptr : static_cast<T*>(::operator new (sizeof(T)*other.size_))),
                size_(other.size_)
        {
            for (size_type i  = 0; i < size_; ++i) {
                try {
                    construct(buf_+i, other.buf_[i]);
                } catch (...) {
                    destroy(buf_, buf_+i);
                    ::operator delete(buf_);
                    buf_ = nullptr;
                    size_ = 0;
                    throw;
                }
            }
        }

        MatrixBuf& operator= (const MatrixBuf& other) {
            MatrixBuf tmp(other);
            std::swap(buf_, tmp.buf_);
            std::swap(size_, tmp.size_);

            return *this;
        }

        MatrixBuf(MatrixBuf&& other) noexcept
            :
                buf_(other.buf_),
                size_(other.size_)
        {
            other.buf_ = nullptr;
            other.size_ = 0;
        }

        MatrixBuf& operator= (MatrixBuf&& other) noexcept {
            if (this != &other) {
                destroy(buf_, buf_ + size_);
                ::operator delete(buf_);
                buf_ = nullptr;
                size_ = 0;

                std::swap(buf_, other.buf_);
                std::swap(size_, other.size_);
            }

            return *this;
        }

        void resize(size_type size) {
            if (size == size_)
                return;

            MatrixBuf tmp(size);

            std::swap(size_, tmp.size_);
            std::swap(buf_, tmp.buf_);
        }

        size_type size() const noexcept {
            return size_;
        }

        T& operator [] (int id) noexcept {
            return buf_[id];
        }

        const T& operator [] (int id) const noexcept {
            return buf_[id];
        }
    };

    template <typename FwdIt,
            typename = std::_RequireInputIter<FwdIt>>
	MatrixBuf(FwdIt, FwdIt) -> MatrixBuf<value_type<FwdIt>>;


    template <typename T>
    struct SimpleTraits {
        static bool eq(const T& lhs, const T& rhs) {
            return abs(lhs - rhs) <= 5e-3;
        }
    };

    template <typename T,
            typename arithmetic_traits = SimpleTraits<T>>
    class Matrix final {
    public:
        using size_type = typename MatrixBuf<T>::size_type;
    private:
        size_type rows_, cols_;
        MatrixBuf<T> buf_;

    public:
        Matrix()
            :
                rows_(0),
                cols_(0),
                MatrixBuf<T>(0)
        {}

        /**
         *
         * @param size  size.first - rows number
         *              size.second - columns number
         */
        explicit Matrix(const std::pair<size_type, size_type>& size)
                :
                rows_(0),
                cols_(0),
                buf_(size.first * size.second)
        {
            auto rows = size.first, cols = size.second;
            if (!((rows!=0 && cols!=0) || (rows==0 && cols==0))) {
                throw std::runtime_error
                ("bad matrix parameters: it isn't possible to create [rows, 0] or [0, cols] matrix");
            }
            rows_ = rows;
            cols_ = cols;
        }

        Matrix(const std::pair<size_type, size_type>& size, const T& arg)
            :
                rows_(0),
                cols_(0),
                buf_(size.first * size.second, arg)
        {
            auto rows = size.first, cols = size.second;
            if (!((rows!=0 && cols!=0) || (rows==0 && cols==0))) {
                throw std::runtime_error
                ("bad matrix parameters: it isn't possible to create [rows, 0] or [0, cols] matrix");
            }
            rows_ = rows;
            cols_ = cols;
        }

        template <typename FwdIt, typename = std::_RequireInputIter<FwdIt>>
        Matrix(FwdIt first, FwdIt last, const std::pair<size_type, size_type>& size)
            :
                rows_(0),
                cols_(0),
                buf_(first, last)
        {
            auto rows = size.first, cols = size.second;
            if (buf_.size() != rows*cols) {
                resize(0, 0);
                throw std::runtime_error("distance doesn't match with matrix parameters");
            }

            rows_ = rows;
            cols_ = cols;
        }

        void resize(size_type rows, size_type cols) {
            if (!((rows!=0 && cols!=0) || (rows==0 && cols==0)))
                throw std::runtime_error
                ("bad matrix parameters: it isn't possible to resize matrix to [rows, 0] or [0, cols]");

            buf_.resize(rows*cols);

            rows_ = rows;
            cols_ = cols;
        }

        Matrix& operator*= (const Matrix& other) {
            if (other.rows_ != cols_)
                throw std::runtime_error("in matrix operator *= size doesn't match");

            auto rhs_tmp = other.transpose();
            auto AX = rows_, AY = cols_, BY = other.cols_;
            Matrix tmp({AX, BY});

            // cache friendly loop

            for (size_type i = 0; i < AX; i++)
                for (size_type j = 0; j < BY; j++) {
                    tmp[i][j] = 0;
                    for (size_type k = 0; k < AY; k++) {
                        tmp[i][j] +=
                                (*this)[i][k] * rhs_tmp[j][k];

                    }
                }

            std::swap(tmp, *this);

            return *this;
        }

        Matrix transpose() const {
            Matrix transp({cols_, rows_});
            for (size_type i = 0; i < transp.rows_; ++i)
                for (size_type j = 0; j < transp.cols_; ++j)
                    transp[i][j] = (*this)[j][i];
            return transp;
        }

        Matrix& operator-= (const Matrix& other) {
            if ((rows_ != other.rows_) || (cols_ != other.cols_))
                throw std::runtime_error("in matrix operator -= size doesn't match");

            Matrix tmp(*this);

            for (size_type i = 0; i < tmp.buf_.size(); i++)
                tmp.buf_[i] -= other.buf_[i];

        	std::swap(tmp, *this);

            return *this;
        }

        Matrix& operator+= (const Matrix& other) {
            if ((rows_ != other.rows_) || (cols_ != other.cols_))
                throw std::runtime_error("in matrix operator += size doesn't match");

        	Matrix tmp(*this);

            for (size_type i = 0; i < buf_.size(); i++)
                tmp.buf_[i] += other.buf_[i];

            std::swap(tmp, *this);

            return *this;
        }

        bool equal(const Matrix& other) const noexcept {
            if ((rows_ != other.rows_) || (cols_ != other.cols_))
                return false;

            for (size_type i = 0; i < buf_.size(); i++)
                if (!arithmetic_traits::eq(buf_[i],  other.buf_[i]))
                    return false;

            return true;
        }

        const T* operator[] (int i) const noexcept {
            return &buf_[i*cols_];
        };

        T* operator[] (int i) noexcept {
            return &buf_[i*cols_];
        };

        void switch_rows(size_t first_row, size_t second_row) {
            if ( (first_row >= rows_) || (second_row >= rows_) )
                throw std::out_of_range("bad rows");

            for (size_type i = 0; i < cols_; ++i)
                std::swap((*this)[first_row][i], (*this)[second_row][i]);
        }

        /**
         * normally makes gaussian elimination on matrix
         * @return sign of new determinant or -2 in case of err
         */
        int gaussian_elimination() {
            if (cols_ != rows_)
                throw std::runtime_error("can't eliminate non square matrix");

            if ( (rows_ == 0) || (rows_ == 1) )
                return 1;

            int sign = 1, switch_row = -1;
            double multiplier = 1;

            for (size_type i = 0; i < rows_; i++) {
                if (arithmetic_traits::eq((*this)[i][i], 0)) {

                    for (size_type j = i + 1; j < rows_; j++)
                        if (!arithmetic_traits::eq((*this)[j][i], 0)) {
                            switch_row = j;
                            break;
                        }

                    if (switch_row != -1) {
                        switch_rows(i, switch_row);
                        sign *= -1;
                        switch_row = -1;
                    } else
                        continue;

                }
                for (size_type j = i + 1; j < rows_; j++) {
                    multiplier = (*this)[j][i] / (*this)[i][i];
                    for (size_type k = i; k < rows_; k++)
                        (*this)[j][k] -= multiplier * (*this)[i][k];
                }
            }
            return sign;
        }

        double determinant() const {
            if (cols_ != rows_)
                throw std::runtime_error("can't find determinant of non square matrix");

            if (cols_ == 0)
                return 0;

            if (cols_ == 1)
                return buf_[0];

            if (cols_ == 2)
                return buf_[0] * buf_[3] - buf_[1] * buf_[2];

            Matrix tmp(*this);

            auto sign = tmp.gaussian_elimination();
            double determinant = 1;

            for (size_type i = 0; i < tmp.cols_; ++i)
                determinant *= tmp[i][i];

            return sign * determinant;
        }

        std::ostream& dump(std::ostream& os) const {
            for (size_type i = 0; i < rows_; i++) {
                for (size_type j = 0; j < cols_; j++)
                    os << (*this)[i][j] << " ";
                os << std::endl;
            }
            return os;
        }

        std::istream& scan(std::istream& is) {
            size_type rows = 0, cols = 0;
            is >> rows >> cols;

            if (!is.good())
                throw std::runtime_error("bad input!");

            resize(rows, cols);

            for (size_type i = 0; i < rows_; i++) {
                for (size_type j = 0; j < cols_; j++)
                    is >> (*this)[i][j];
            }
            return is;
        }

        std::pair<size_type, size_type> size() const noexcept {
            return {rows_, cols_};
        }
    };

    template <typename FwdIt,
            typename = std::_RequireInputIter<FwdIt>>
    Matrix(FwdIt first, FwdIt last, typename Matrix<value_type<FwdIt>>::size_type cols,
            typename Matrix<value_type<FwdIt>>::size_type rows) -> Matrix<value_type<FwdIt>>;

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