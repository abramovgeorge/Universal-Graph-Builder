#ifndef _FUNCTION_CPP_
#define _FUNCTION_CPP_

#include <iostream>
#include <cmath>

using namespace std;

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
    int i_ = 0;
};

#endif