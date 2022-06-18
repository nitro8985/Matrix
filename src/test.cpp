#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.cpp"

TEST(S21Matrix___Test, eq) {
    S21Matrix mat1(3, 4);
    double nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    mat1.populateMatrix(nums, 12);
    S21Matrix mat2(mat1);
    ASSERT_TRUE(mat1.eq_matrix(mat2));
}

TEST(S21Matrix___Test, eq1) {
    S21Matrix mat(3, 4);
    S21Matrix mat1(3, 4);
    double nums[] = {1.111111111112, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double nums1[] = {1.111111111111, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    mat.populateMatrix(nums, 12);
    mat1.populateMatrix(nums1, 12);
    ASSERT_TRUE(mat.eq_matrix(mat1));
}

TEST(S21Matrix___Test, eq2) {
    S21Matrix mat1;
    double nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    mat1.populateMatrix(nums, 12);
    S21Matrix mat2(5, 7);
    mat2 = mat1;
    mat2.setNum(1.0000001, 0, 0);
    ASSERT_FALSE(mat1.eq_matrix(mat2));
}

TEST(S21Matrix___Test, eq3) {
    S21Matrix mat;
    S21Matrix mat1(3, 4);
    ASSERT_FALSE(mat == mat1);
}

TEST(S21Matrix___Test, sum) {
    S21Matrix mat1;
    double nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    mat1.populateMatrix(nums, 12);
    S21Matrix mat2(mat1);
    mat2 += mat1;
    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            ASSERT_EQ(mat1.getNum(i, j) * 2, (mat2.getNum(i, j)));
        }
    }
    mat1.print_matrix();
}

TEST(S21Matrix___Test, sub) {
    S21Matrix mat1;
    double nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    mat1.populateMatrix(nums, 12);
    S21Matrix mat2(mat1);
    mat2 -= mat1;
    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            ASSERT_EQ(0, (mat2.getNum(i, j)));
        }
    }
}

TEST(S21Matrix___Test, mulnum) {
    S21Matrix mat;
    double nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    mat.populateMatrix(nums, 12);
    S21Matrix mat1(std::move(mat));
    S21Matrix mat2;
    mat2 = mat1;
    // mat2 = std::move(mat2);
    mat2 *= 10;
    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            ASSERT_EQ(mat1.getNum(i, j) * 10, (mat2.getNum(i, j)));
        }
    }
}

TEST(S21Matrix___Test, self_assignment) {
    ASSERT_ANY_THROW(S21Matrix mat(mat));
    ASSERT_ANY_THROW(S21Matrix mat(std::move(mat)));
}

TEST(S21Matrix___Test, mulmat) {
    S21Matrix mat(3, 2);
    S21Matrix mat1(2, 3);
    S21Matrix res;
    double nums[] = {1, 4, 2, 5, 3, 6};
    mat.populateMatrix(nums, 6);
    double nums1[] = {1, -1, 1, 2, 3, 4};
    mat1.populateMatrix(nums1, 6);
    double numsres[] = {9, 11, 17, 12, 13, 22, 15, 15, 27};
    res.populateMatrix(numsres, 9);
    mat *= mat1;
    for (int i = 0; i < mat.getRows(); i++) {
        for (int j = 0; j < mat.getCols(); j++) {
            ASSERT_EQ(mat.getNum(i, j), res.getNum(i, j));
        }
    }
}

TEST(S21Matrix___Test, mulmat1) {
    S21Matrix mat(3, 2);
    S21Matrix mat1(2, 3);
    S21Matrix res;
    double nums[] = {1, 4, 2, 5, 3, 6};
    mat.populateMatrix(nums, 6);
    double nums1[] = {1, -1, 1, 2, 3, 4};
    mat1.populateMatrix(nums1, 6);
    double numsres[] = {9, 11, 17, 12, 13, 22, 15, 15, 27};
    res.populateMatrix(numsres, 9);
    mat = mat * mat1;
    for (int i = 0; i < mat.getRows(); i++) {
        for (int j = 0; j < mat.getCols(); j++) {
            ASSERT_EQ(mat.getNum(i, j), res.getNum(i, j));
        }
    }
}

TEST(S21Matrix___Test, transpose) {
    S21Matrix mat(3, 2);
    S21Matrix mat1(2, 3);
    double nums[] = {1, 4, 2, 5, 3, 6};
    double nums1[] = {1, 2, 3, 4, 5, 6};
    mat.populateMatrix(nums, 6);
    mat1.populateMatrix(nums1, 6);
    S21Matrix mat2(mat.transpose());
    ASSERT_TRUE(mat2 == mat1);
}

TEST(S21Matrix___Test, determinant) {
    S21Matrix mat;
    S21Matrix mat1(1, 1);
    double nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    mat.populateMatrix(nums, 9);
    ASSERT_EQ(0, mat.determinant());
    ASSERT_EQ(0, mat1.determinant());
}

TEST(S21Matrix___Test, calc_complements) {
    S21Matrix mat;
    S21Matrix mat1;
    S21Matrix res;
    double nums[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
    double nums1[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
    mat.populateMatrix(nums, 9);
    mat1.populateMatrix(nums1, 9);
    res = mat.calc_complements();
    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            ASSERT_EQ(mat1.getNum(i, j), res.getNum(i, j));
        }
    }
    ASSERT_FALSE(res != mat1);
}

TEST(S21Matrix___Test, inverse) {
    S21Matrix mat;
    S21Matrix mat1;
    S21Matrix res;
    double nums[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
    double nums1[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
    mat.populateMatrix(nums, 9);
    mat1.populateMatrix(nums1, 9);
    res = mat.inverse_matrix();
    ASSERT_TRUE(res == mat1);
}

TEST(S21Matrix___Test, operators) {
    S21Matrix mat;
    S21Matrix mat1;
    const S21Matrix mat2;
    double nums[] = {0, 1, 1, 1, 1, 1, 1, 1, 1};
    mat.populateMatrix(nums, 9);
    mat(0, 0) = 1;
    mat1 = mat * 2;
    mat = mat1 + mat;
    mat = mat - mat1;
    mat1 = mat1 * 0.5;
    mat1 = mat1;
    mat = std::move(mat);
    double n = mat2(1, 1);
    ASSERT_TRUE(mat == mat1);
    ASSERT_EQ(0, n);
}

TEST(S21Matrix___Test, setRows) {
    S21Matrix mat(1, 3);
    S21Matrix mat1(2, 3);
    double nums[] = {1, 2, 3, 4, 5, 6};
    mat.populateMatrix(nums, 3);
    mat1.populateMatrix(nums, 6);
    mat1.setRows(1);
    mat1.setRows(2);
    mat.setRows(2);
    ASSERT_TRUE(mat == mat1);
}

TEST(S21Matrix___Test, setCols) {
    S21Matrix mat;
    S21Matrix mat1(3, 2);
    double nums[] = {1, 2, 3};
    mat.populateMatrix(nums, 3);
    mat1.populateMatrix(nums, 2);
    mat.setCols(3);
    mat.setCols(2);
    ASSERT_TRUE(mat == mat1);
}

TEST(S21Matrix___Test, setCols_and_setRows) {
    S21Matrix mat;
    S21Matrix mat1;
    double nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    mat.populateMatrix(nums, 9);
    mat1.populateMatrix(nums, 2);
    mat1(1, 0) = 4;
    mat1(1, 1) = 5;
    mat.setRows(2);
    mat.setCols(2);
    mat.setRows(3);
    mat.setCols(3);
    ASSERT_TRUE(mat == mat1);
}

TEST(S21Matrix___Test, exceptions) {
    ASSERT_ANY_THROW(S21Matrix mat(-1, -3));
    S21Matrix mat;
    S21Matrix mat1(3, 4);
    const S21Matrix mat2;
    ASSERT_ANY_THROW(mat.sum_matrix(mat1));
    ASSERT_ANY_THROW(mat.sub_matrix(mat1));
    ASSERT_ANY_THROW(mat.mul_matrix(mat1));
    ASSERT_ANY_THROW(mat1.determinant());
    ASSERT_ANY_THROW(mat1.calc_complements());
    ASSERT_ANY_THROW(mat.inverse_matrix());
    ASSERT_ANY_THROW(double n = mat1(5, 55));
    ASSERT_ANY_THROW(double n = mat2(-1, -2));
    ASSERT_ANY_THROW(mat.setNum(3.14, -1, 4));
    ASSERT_ANY_THROW(mat.getNum(3, 3));
    ASSERT_ANY_THROW(mat.setRows(0));
    ASSERT_ANY_THROW(mat.setCols(-1));
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running main() from test.cpp\n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
