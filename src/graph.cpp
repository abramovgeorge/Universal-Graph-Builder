#ifndef _GRAPH_CPP_
#define _GRAPH_CPP_

#include <iostream>
#include <QWidget>
#include "settings.cpp"
#include "function.cpp"

const double eps = 1e-2;

class Graph {
public:
    Graph(Function *func, double a, double b) {
        func_ = func;
        a_ = a; b_ = b;
        x1_ = settings.x1_; y1_ = settings.y1_; x2_ = settings.x2_; y2_ = settings.y2_;
        this->setXStep(computeXStep());
        this->computeValues();
    }

    std::vector<double> *getValues() {
        return &values_;
    }

    double getA() {
        return a_;
    }

    double getB() {
        return b_;
    }

    int getXZero() {
        return (int)-(a_/xstep_);
    }

    int getYZero() {
        if (zero_ind_ == -1) {
            return -1;
        }
        return (int)values_[zero_ind_];
    }

    int getXOneLength(bool isExp = false) {
        double len = (b_ - a_) / 2.0;
        int exp = -6;
        while (pow(10, exp) < len) {
            exp++;
        }
        exp--;
        if (isExp) {
            return exp;
        }
        return (int)(pow(10, exp) / xstep_);
    }

    int getYOneLength(bool isExp = false) {
        double len = (f_max_ - f_min_) / 2.0;
        int exp = -6;
        while (pow(10, exp) < len) {
            exp++;
        }
        exp--;
        if (isExp) {
            return exp;
        }
        return (int)(pow(10, exp) * ystep_);
    }

    double getFMax() {
        return f_max_;
    }

    double getFMin() {
        return f_min_;
    }

private:
    Function *func_;
    double a_, b_, xstep_, ystep_, f_max_, f_min_;
    int x1_, y1_, x2_, y2_, zero_ind_ = -1;
    std::vector<double> values_;

    double computeXStep() {
        return (b_ - a_) / (x2_ - x1_);
    }

    double computeYStep() {
        return (y2_ - y1_) / (f_max_ - f_min_);
    }

    void computeValues() {
        values_.resize(x2_ - x1_);
        f_max_ = func_->calculate(a_);
        f_min_ = func_->calculate(a_);
        for (int i = 0; i < x2_ - x1_; i++) {
            values_[i] = func_->calculate(a_ + i * xstep_);
            if (values_[i] > f_max_) f_max_ = values_[i];
            if (values_[i] < f_min_) f_min_ = values_[i];
        }
        if (f_min_ < 0.0 && f_max_ > 0.0) {
            zero_ind_ = 0;
            for (int i =  1; i < x2_ - x1_; i++) {
                if (abs(values_[i]) < abs(values_[zero_ind_])) {
                    zero_ind_ = i;
                }
            }
        }
        else {
            zero_ind_ = -1;
        }
        this->setYStep(computeYStep());
        for (int i = 0; i < x2_ - x1_; i++) {
            values_[i] -= f_min_;
            values_[i] *= ystep_;
        }
    }

    void setXStep(double x) {
        xstep_ = x;
    }

    void setYStep(double x) {
        ystep_ = x;
    }
};

#endif