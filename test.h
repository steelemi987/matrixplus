#ifndef TEST_H
#define TEST_H

#include <gtest/gtest.h>

#include "./s21_matrix_oop.h"

bool is_mat_fill_numb(const S21Matrix& mat, double num);
void fill_mat_numb(S21Matrix& mat, double num);
bool equel_double(double a, double b);

#endif