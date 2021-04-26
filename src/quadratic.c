#include <math.h>
#include <stddef.h>

#include <regression/matrix.h>
#include <regression/quadratic.h>

// Get the number of elements in a statically allocated array
#define ARRAY_LENGTH(array)   (sizeof(array) / sizeof(array[0]))

void quadratic_lsm(QuadraticCurve * curve,
                   double x[],
                   double y[],
                   size_t n) 
{
    double sum_x[5] = {0};   // sum_x[i]  = Summation of: x^i
    double sum_yx[5] = {0};  // sum_yx[i] = Summation of: x^i * y

    for (size_t point = 0; point < n; ++point)
    {
        for (size_t power = 0; power < ARRAY_LENGTH(sum_x); ++power)
        {
            double x_power = pow(x[point], power);
            sum_x[power]  += x_power;
            sum_yx[power] += x_power * y[point];
        }
    }

    double matrix[3][3] =
    {
        { sum_x[4], sum_x[3], sum_x[2] },
        { sum_x[3], sum_x[2], sum_x[1] },
        { sum_x[2], sum_x[1],        n }
    };

    double vector[3] = 
    { 
        sum_yx[2], sum_yx[1], sum_yx[0] 
    };

    matrix_inverse_3x3(matrix, matrix);

    // Matrix multiply 
    double coefficients[3] = {0};
    for (size_t m = 0; m < ARRAY_LENGTH(vector); ++m)
    {
        for (size_t n = 0; n < ARRAY_LENGTH(matrix[0]); ++n)
        {
            coefficients[m] += matrix[m][n] * vector[n];
        }
    }

    curve->a = coefficients[0];
    curve->b = coefficients[1];
    curve->c = coefficients[2];
}

void quadratic_y(const QuadraticCurve * curve,
                 const double x[], 
                 size_t n, 
                 double y[]) 
{
    for (size_t i = 0; i < n; ++i)
    {
        y[i] = (curve->a * x[i] * x[i]) + (curve->b * x[i]) + curve->c;
    }
}
