#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
 private:
    int rows_, cols_;
    double** p_;
    S21Matrix minor(int n, int m);
    void mem_alloc();
    void mem_free();
    void mem_copy(const S21Matrix& other);

 public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix& operator=(S21Matrix&& other);
    double& operator()(int row, int col);
    double operator()(int row, int col) const;
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*(const double num);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(const double num);
    bool operator==(const S21Matrix& other);
    bool operator!=(const S21Matrix& other);

    bool eq_matrix(const S21Matrix& other);
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();

    void setNum(double num, int i, int j);
    double getNum(int i, int j);
    void setRows(int rows);
    void setCols(int cols);
    int getRows();
    int getCols();
    void populateMatrix(const double nums[], int len);
    void print_matrix();
};

#endif  // SRC_S21_MATRIX_OOP_H_
