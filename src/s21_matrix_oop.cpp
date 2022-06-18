#include "s21_matrix_oop.h"

void S21Matrix::mem_alloc() {
    p_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
        p_[i] = new double[cols_]();
    }
}

void S21Matrix::mem_free() {
    for (int i = 0; i < rows_; i++) {
        delete[] p_[i];
    }
    delete[] p_;
    p_ = nullptr;
}

void S21Matrix::mem_copy(const S21Matrix& other) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p_[i][j] = other.p_[i][j];
        }
    }
}

S21Matrix::S21Matrix() {
    rows_ = 3;
    cols_ = 3;
    mem_alloc();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Couldn't create a matrix of such size");
    }
    mem_alloc();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
    if (this == &other) {
        throw std::invalid_argument("No self assignment allowed");
    }
    mem_alloc();
    mem_copy(other);
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_) {
    if (this == &other) {
        throw std::invalid_argument("No self assignment allowed");
    }
    p_ = other.p_;
    other.p_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
    if (p_ != nullptr) {
        mem_free();
        rows_ = 0;
        cols_ = 0;
    }
}

bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool ret = true;
    if (rows_ == other.rows_ && cols_ == other.cols_) {
        double eps = 1e-7;
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                if (std::abs(p_[i][j] - other.p_[i][j]) > eps) {
                    ret = false;
                }
            }
        }
    } else {
        ret = false;
    }
    return ret;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument(
            "Incorrect input, matrices should have the same size");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p_[i][j] += other.p_[i][j];
        }
    }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument(
            "Incorrect input, matrices should have the same size");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p_[i][j] -= other.p_[i][j];
        }
    }
}

void S21Matrix::mul_number(const double num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            p_[i][j] *= num;
        }
    }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
    S21Matrix tmp(rows_, other.cols_);
    if (rows_ != other.cols_) {
        throw std::invalid_argument(
            "Couldn't multiply matrices if A rows != B columns");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                tmp.p_[i][j] += p_[i][k] * other.p_[k][j];
            }
        }
    }
    *this = tmp;
}

S21Matrix S21Matrix::transpose() {
    S21Matrix ret(cols_, rows_);
    for (int i = 0; i < cols_; i++) {
        for (int j = 0; j < rows_; j++) {
            ret.p_[i][j] = p_[j][i];
        }
    }
    return ret;
}

double S21Matrix::determinant() {
    double ret = 0;
    if (rows_ != cols_) {
        throw std::invalid_argument(
            "There's no determinant for non-square matrix");
    }
    if (rows_ == 1) {
        ret = p_[0][0];
    } else if (rows_ == 2) {
        ret = (p_[0][0] * p_[1][1]) - (p_[1][0] * p_[0][1]);
    } else {
        for (int n = 0; n < cols_; n++) {
            if (n % 2 == 0) {
                S21Matrix B = minor(0, n);
                ret += (p_[0][n] * B.determinant());
            } else {
                S21Matrix B = minor(0, n);
                ret -= (p_[0][n] * B.determinant());
            }
        }
    }
    return ret;
}

S21Matrix S21Matrix::calc_complements() {
    S21Matrix ret(rows_, cols_);
    if (rows_ != cols_) {
        throw std::invalid_argument(
            "There's no complements for non-square matrix");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            S21Matrix B = minor(i, j);
            if (B.determinant()) {
                ret.p_[i][j] = B.determinant() * pow(-1, i + j);
            }
        }
    }
    return ret;
}

S21Matrix S21Matrix::inverse_matrix() {
    S21Matrix ret(rows_, cols_);
    if (determinant() == 0) {
        throw std::invalid_argument(
            "There's no inverse matrix for matrix with zero(0) determinant");
    }
    S21Matrix B = calc_complements();
    S21Matrix C = B.transpose();
    for (int i = 0; i < C.rows_; i++) {
        for (int j = 0; j < C.cols_; j++) {
            ret.p_[i][j] = C.p_[i][j] / determinant();
        }
    }
    return ret;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix res(*this);
    res.sum_matrix(other);
    return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix res(*this);
    res.sub_matrix(other);
    return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix res(*this);
    res.mul_matrix(other);
    return res;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix res(*this);
    res.mul_number(num);
    return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this == &other) {
        return *this;
    }
    mem_free();
    rows_ = other.rows_;
    cols_ = other.cols_;
    mem_alloc();
    mem_copy(other);
    return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
    if (this == &other) {
        return *this;
    }
    mem_free();
    rows_ = other.rows_;
    cols_ = other.cols_;
    // mem_alloc();
    p_ = other.p_;
    other.p_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    sum_matrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    sub_matrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    mul_matrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
    mul_number(num);
    return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) { return eq_matrix(other); }

bool S21Matrix::operator!=(const S21Matrix& other) { return !eq_matrix(other); }

// index operator overload
double& S21Matrix::operator()(int row, int col) {
    if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return p_[row][col];
}

double S21Matrix::operator()(int row, int col) const {
    if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return p_[row][col];
}

void S21Matrix::setNum(double num, int i, int j) {
    if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    p_[i][j] = num;
}

double S21Matrix::getNum(int i, int j) {
    if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return p_[i][j];
}

void S21Matrix::setRows(int rows) {
    if (rows <= 0) {
        throw std::invalid_argument("Couldn't set such size");
    }
    if (rows_ != rows) {
        S21Matrix tmp(*this);
        mem_free();
        rows_ = rows;
        mem_alloc();
        for (int i = 0; i < tmp.rows_ && i < rows_; i++) {
            for (int j = 0; j < tmp.cols_ && j < cols_; j++) {
                p_[i][j] = tmp.p_[i][j];
            }
        }
    }
}

void S21Matrix::setCols(int cols) {
    if (cols <= 0) {
        throw std::invalid_argument("Couldn't set such size");
    }
    if (cols_ != cols) {
        S21Matrix tmp(*this);
        mem_free();
        cols_ = cols;
        mem_alloc();
        for (int i = 0; i < tmp.rows_ && i < rows_; i++) {
            for (int j = 0; j < tmp.cols_ && j < cols_; j++) {
                p_[i][j] = tmp.p_[i][j];
            }
        }
    }
}

int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

void S21Matrix::print_matrix() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << p_[i][j] << "    ";
        }
        std::cout << std::endl << std::endl;
    }
    std::cout << "============================" << std::endl;
}

void S21Matrix::populateMatrix(const double nums[], int len) {
    int k = 0;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (k < len) {
                p_[i][j] = nums[k];
                k++;
            } else {
                p_[i][j] = 0;
            }
        }
    }
}

S21Matrix S21Matrix::minor(int n, int m) {
    S21Matrix ret(rows_ - 1, cols_ - 1);
    for (int i = 0; i < ret.rows_; i++) {
        for (int j = 0; j < ret.cols_; j++) {
            if (i >= n && j >= m) {
                ret.p_[i][j] = p_[i + 1][j + 1];
            } else if (i >= n) {
                ret.p_[i][j] = p_[i + 1][j];
            } else if (j >= m) {
                ret.p_[i][j] = p_[i][j + 1];
            } else {
                ret.p_[i][j] = p_[i][j];
            }
        }
    }
    return ret;
}
