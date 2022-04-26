#ifndef _GRAPH_CPP_
#define _GRAPH_CPP_

#include <iostream>
#include <QWidget>
#include "settings.cpp"
#include "function.cpp"

using namespace std;

class Graph {
public:
    Graph(Function *func, double a, double b) {
        func_ = func;
        a_ = a; b_ = b;
        x1_ = settings.x1_; y1_ = settings.y1_; x2_ = settings.x2_; y2_ = settings.y2_;
        this->setXStep(computeXStep());
        this->computeValues();
    }

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

    vector<double> *getValues() {
        return &values_;
    }

private:
    Function *func_;
    double a_, b_, xstep_, ystep_, f_max_, f_min_;
    int x1_, y1_, x2_, y2_;
    vector<double> values_;
};

#endif