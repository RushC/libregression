#ifndef REGRESSION_QUADRATIC_H
#define REGRESSION_QUADRATIC_H

#include <stddef.h>

/**
 * A curve that is represented by a 2nd-order polynomial.
 * 
 * A quadratic curve is described with the equation:
 * 
 *     y = Ax^2 + Bx + C
 * 
 * Different instances of a quadratic curve are distinguished by the values for
 * the coefficients A, B, and C.
 */
typedef struct QuadraticCurve
{
    /// @{
    /// Coefficients for the 2nd-order polynomial describing the curve.
    double a;
    double b;
    double c;
    /// @}

} QuadraticCurve;

/**
 * Fit a quadratic curve to a set of points using the Least Squares Method.
 * 
 * @param[out] curve
 *     The best fitting curve for the points.
 * @param[in] x 
 *     The X-components for each of the points.
 * @param[in] y 
 *     The Y-components for each of the points.
 * @param[in] n 
 *     The number of points.
 */
void quadratic_lsm(QuadraticCurve * curve,
                   double x[],
                   double y[],
                   size_t n);

/**
 * Calculate points on a quadratic curve.
 * 
 * @param[in] curve
 *     The curve to calculate points for.
 * @param[in] x
 *     The X-components of the points.
 * @param[in] n
 *     The number of points.
 * @param[out] y 
 *     Buffer to hold the Y-components of the points.
 */
void quadratic_y(const QuadraticCurve * curve,
                 const double x[], 
                 size_t n, 
                 double y[]);

#endif // REGRESSION_QUADRATIC_H