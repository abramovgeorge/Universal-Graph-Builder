#ifndef _FUNCTION_CPP_
#define _FUNCTION_CPP_

#include <iostream>
#include <cmath>

using namespace std;

class Function {
public:
    Function(string s) {
        func_ = s;
    }
    double calculate(double x) {
        i_ = 0;
        string pre_func = func_;
        func_ += '#';
        double res = add_(x);
        if (func_[i_] == '#' && i_ == func_.size() - 1) {
            func_ = pre_func;
            return res;
        }
        else {
            func_ = pre_func;
            return 0.0; //incorrect equation
        }
    }

private:
    string func_;
    int i_ = 0;

    double add_(double x) {
        double res = mult_(x);
        while (func_[i_] == '+') {
            i_++;
            res += mult_(x);
        }
        return res;
    }

    double mult_(double x) {
        double res = power_(x);
        while (func_[i_] == '*' or func_[i_] == '/') {
            if (func_[i_] == '*') {
                i_++;
                res *= power_(x);
            }
            else {
                i_++;
                res /= power_(x);
            }
        }
        return res;
    }

    double power_(double x) {
        double res = factor_(x);
        while (func_[i_] == '^') {
            i_++;
            res = pow(res, factor_(x));
        }
        return res;
    }

    double factor_(double x) {
        double res = 0.0;
        switch (func_[i_]) {
            case 'x':
                res = x;
                i_++;
                break;
            case '0'...'9':
                while (func_[i_] >= '0' && func_[i_] <= '9') {
                    res = res * 10 + func_[i_] - '0';
                    i_++;
                }
                break;
            case '-':
                i_++;
                res -= factor_(x);
                break;
            case 's':
                i_++;
                res = sin(factor_(x));
                break;
            case 'c':
                i_++;
                res = cos(factor_(x));
                break;
            case 't':
                i_++;
                res = tan(factor_(x));
                break;
            case 'l':
                i_++;
                res = log(factor_(x));
                break;
            case '(':
                i_++;
                res = add_(x);
                if (func_[i_] == ')') {
                    i_++;
                }
                break;
            case '|':
                i_++;
                res = abs(add_(x));
                if (func_[i_] == '|') {
                    i_++;
                }
                break;
            default:
                break;
        }
        return res;
    }
};

#endif