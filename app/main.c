#include <stdlib.h>
#include <stdio.h>

#include <regression/matrix.h>
#include <regression/quadratic.h>

static void test_matrix(void)
{
    double matrix[3][3] = 
    {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 2, 9 }
    };
    double inverse[3][3] = {{ 0 }};

    double determinant = matrix_determinant_3x3(matrix);
    printf("Determinant: %f\n", determinant);

    matrix_inverse_3x3(matrix, inverse);
    matrix_print(3, 3, inverse);
}

static void test_quadratic(void)
{
    static const size_t NUM_POINTS = 2;

    QuadraticCurve reference = { .a = 5, .b = 10, .c = 15 };
    QuadraticCurve estimated = {0};

    double x[NUM_POINTS] = {0};
    double y[NUM_POINTS] = {0};

    for (size_t i = 0; i < NUM_POINTS; ++i)
    {
        x[i] = i * 50;
    }

    quadratic_y(&reference, x, NUM_POINTS, y);
    quadratic_lsm(&estimated, x, y, NUM_POINTS);

    printf("A: %f\n", estimated.a);
    printf("B: %f\n", estimated.b);
    printf("C: %f\n", estimated.c);
}

int main()
{
    test_matrix();
    test_quadratic();
}