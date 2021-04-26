#ifndef REGRESSION_MATRIX_H
#define REGRESSION_MATRIX_H

#include <stddef.h>

/**
 * Calculate the determinent of a 2-by-2 matrix.
 * 
 * @param[in] matrix
 *     The matrix to calculate the determinent of.
 * 
 * @return
 *     The calculated determinant. 
 */
double matrix_determinant_2x2(const double matrix[2][2]);

/**
 * Calculate the determinent of a 3-by-3 matrix.
 * 
 * @param[in] matrix
 *     The matrix to calculate the determinent of.
 * 
 * @return
 *     The calculated determinant. 
 */
double matrix_determinant_3x3(const double matrix[3][3]);

/**
 * Calculate the inverse of a 3-by-3 matrix.
 * 
 * @param[in] matrix
 *     The matrix to calculate the inverse of.
 * @param[in] m
 *     The number of rows in the matrix.
 * @param[in] n
 *     The number of columns in the matrix.
 * @param[out] inverse
 *     A buffer to store the calculated inverse of the matrix.
 * 
 * @c inverse is expected to be an @c n by @c m matrix.
 */
void matrix_inverse_3x3(const double matrix[3][3], double inverse[3][3]);

/**
 * Print a matrix to stdout.
 * 
 * @param[in] m 
 *     The number of rows in the matrix.
 * @param[in] n 
 *     The number of columns in the matrix.
 * @param[in] matrix
 *     The matrix to print.
 */
void matrix_print(size_t m, size_t n, const double matrix[m][n]);

#endif // REGRESSION_MATRIX_H