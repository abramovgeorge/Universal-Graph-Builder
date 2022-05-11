#ifndef _FUNCTION_CPP_
#define _FUNCTION_CPP_

#include <iostream>
#include <cmath>

namespace myFunctions {
    double integral(double a, double b, double(*f)(double)) {
        //TODO: implement integral
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