#ifndef _FUNCTION_CPP_
#define _FUNCTION_CPP_

#include <iostream>
#include <cmath>
#include "settings.cpp"

namespace myFunctions {
    double integral(double a, double b, double(*f)(double)) { //trapezoid method
        double eps = settings.eps_;
        double newI = 0.0, prevI = 2.0 * eps;
        int n = 4;
        while (abs(prevI - newI) > eps) {
            prevI = newI;
            double h = (b - a) / n;
            newI = prevI / 2.0;
            for (int i = 0; i < n; i++) {
                double x_1 = a + i * h;
                double x_2 = a + (i + 1) * h;
                double x_new = (f(x_1) + f(x_2)) / 2.0;
                newI += x_new * h / 2.0;
            }
            n *= 2;
        }
        return newI;
    }
}

class Function {
public:
    Function(double (*f)(double)) {
        func_ = f;
    }
    double calculate(double x) {
        return func_(x);
    }

private:
    double (*func_)(double);
};

#endif