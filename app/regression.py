# %%

from dataclasses import dataclass
from random import random
from typing import List, Tuple, Union

import numpy as np


@dataclass
class QuadraticCurve:
    """A curve that is represented using a 2nd-order polynomial.
    
    A quadratic curve is represented with the equation:
    
        y = Ax^2 + Bx + C
    
    Individual instances of quadratic curves are distinguished by their values
    for the coefficients A, B, and C.
    """
    a: float
    b: float
    c: float

    @staticmethod
    def lsm(x: List[float], y: List[float]) -> 'QuadraticCurve':
        """Fit a quadratic curve to a set of points using the Least Squares 
        Method.

        Args:
            x: X-coordinates for the points to fit the curve to.
            y: Y-coordinates for the points to fit the curve to.

        Returns:
            The best fitting curve.
        """
        matrix = np.array([[np.sum(x**4), np.sum(x**3), np.sum(x**2)],
                           [np.sum(x**3), np.sum(x**2), np.sum(x**1)],
                           [np.sum(x**2), np.sum(x**1),       len(x)]])
        
        vector = np.array([np.sum((x**2)*y), np.sum(x*y), np.sum(y)])

        a, b, c = np.matmul(np.linalg.inv(matrix), vector)
        return QuadraticCurve(a, b, c)

    @staticmethod
    def random(scale: Union[float, Tuple[float, float, float]] = 100) -> 'QuadraticCurve':
        """Generate a random quadratic curve.

        Args:
            scale: The scale factor of the coefficients for the curve. This can
                either be a single value all coefficients, or a list of values 
                for each coefficient.

        Returns:
            The generated curve.
        """
        if type(scale) is int:
            scale = [scale] * 3
        
        a, b, c = tuple((random() - 0.5) * scale[i] for i in range(3))
        return QuadraticCurve(a, b, c)
    
    def y(self, x: List[float]) -> List[float]:
        """Calculate Y-coordinates from some X-coordinates.

        Args:
            x: A list of X-coordinate values.

        Returns:
            A list of Y-coordinate values corresponding to the X-coordinate
            values.
        """
        x = np.array(x)
        return (self.a * (x**2)) + (self.b * x) + self.c
    
    def r2(self, x: List[float], y: List[float]) -> float:
        """Calculate the relative predictive power of the quadratic curve.

        Args:
            x: X-coordinates for the actual data points.
            y: Y-coordinates for the actual data points.

        Returns:
            The calculated relative predictive power.
        """
        sse = np.sum((y - self.y(x)) ** 2)
        sst = np.sum((y - np.average(y)) ** 2)
        return 1 - (sse / sst)


if __name__ == '__main__':
    a = np.array([[1, 2, 3],
                  [4, 5, 6],
                  [7, 2, 9]])
    import matplotlib.pyplot as plt
    curve = QuadraticCurve.random([1, 50, 200])
    x = np.linspace(-100, 100, num=3)
    y = curve.y(x)

    fit_curve = QuadraticCurve.lsm(x, y)
    fit_x = np.linspace(-100, 100, num=500)
    fit_y = fit_curve.y(fit_x)

    print(curve)
    print(fit_curve)
    print('R2: ', fit_curve.r2(x, y))
    plt.plot(x, y, 'r')
    plt.plot(fit_x, fit_y, 'b')
    plt.show()
# %%
