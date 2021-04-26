#include <stdio.h>

#include <regression/matrix.h>

double matrix_determinant_2x2(const double matrix[2][2])
{
    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[1][0];
    double d = matrix[1][1];

    return (a * d) - (b * c);
}

double matrix_determinant_3x3(const double matrix[3][3])
{
    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[0][2];

    double submatrix_a[2][2] =
    {
        { matrix[1][1], matrix[1][2] },
        { matrix[2][1], matrix[2][2] }
    };
    double submatrix_b[2][2] =
    {
        { matrix[1][0], matrix[1][2] },
        { matrix[2][0], matrix[2][2] }
    };
    double submatrix_c[2][2] =
    {
        { matrix[1][0], matrix[1][1] },
        { matrix[2][0], matrix[2][1] }
    };

    return (a * matrix_determinant_2x2(submatrix_a))
         - (b * matrix_determinant_2x2(submatrix_b))
         + (c * matrix_determinant_2x2(submatrix_c));
}

void matrix_inverse_3x3(const double matrix[3][3], double inverse[3][3])
{
    double submatrix[3][3][2][2] = 
    {
        {
            {
                { matrix[1][1], matrix[1][2] },
                { matrix[2][1], matrix[2][2] }
            },
            {
                { matrix[0][2], matrix[0][1] },
                { matrix[2][2], matrix[2][1] }
            },
            {
                { matrix[0][1], matrix[0][2] },
                { matrix[1][1], matrix[1][2] }
            }
        },
        {
            {
                { matrix[1][2], matrix[1][0] },
                { matrix[2][2], matrix[2][0] }
            },
            {
                { matrix[0][0], matrix[0][2] },
                { matrix[2][0], matrix[2][2] }
            },
            {
                { matrix[0][2], matrix[0][0] },
                { matrix[1][2], matrix[1][0] }
            }
        },
        {
            {
                { matrix[1][0], matrix[1][1] },
                { matrix[2][0], matrix[2][1] }
            },
            {
                { matrix[0][1], matrix[0][0] },
                { matrix[2][1], matrix[2][0] }
            },
            {
                { matrix[0][0], matrix[0][1] },
                { matrix[1][0], matrix[1][1] }
            }
        }
    };

    double determinant = matrix_determinant_3x3(matrix);
    for (int m = 0; m < 3; ++m)
    {
        for (int n = 0; n < 3; ++n)
        {
            inverse[m][n] = matrix_determinant_2x2(submatrix[m][n]) / determinant;
        }
    }
}

void matrix_print(size_t m, size_t n, const double matrix[m][n])
{
    for (int row = 0; row < m; ++row)
    {
        printf("[");
        for (int column = 0; column < n; ++column)
        {
            if (column != 0)
            {
                printf(",");
            }
            printf(" %8.3f", matrix[row][column]);
        }
        printf(" ]\n");
    }
}