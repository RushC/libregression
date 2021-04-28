#include <stdlib.h>
#include <stdio.h>

#include <regression/bitset.h>
#include <regression/matrix.h>
#include <regression/quadratic.h>

static void test_bitset(void)
{
    static const size_t NUM_BITS = 20;

    bitset bits[BITSET_SIZE(NUM_BITS)] = {0};

    printf("Initial: ");
    bitset_print(bits, NUM_BITS);
    printf("\n");

    bitset_set(bits, 1);
    bitset_set(bits, 4);
    bitset_set(bits, 5);
    bitset_set(bits, 6);
    bitset_set(bits, 9);
    bitset_set(bits, 10);
    bitset_set(bits, 11);
    bitset_set(bits, 16);
    bitset_set(bits, 19);

    printf("Set:     ");
    bitset_print(bits, NUM_BITS);
    printf("\n");

    bitset_clear(bits, 4);
    bitset_clear(bits, 6);
    bitset_clear(bits, 19);

    printf("Clear:   ");
    bitset_print(bits, NUM_BITS);
    printf("\n");

    for (size_t i = 0; i < NUM_BITS; ++i)
    {
        bitset_write(bits, i, i % 2);
    }

    printf("Write:   ");
    bitset_print(bits, NUM_BITS);
    printf("\n");
}

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
    test_bitset();
    // test_matrix();
    // test_quadratic();
}