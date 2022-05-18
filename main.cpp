#include <iostream>
#include <QApplication>
#include <cmath>
#include "src/mainWidget.cpp"

namespace in {
    double h(double x) {
        return x * sin(x);
    }
    double function(double x) {
        return x + integral(0, x, h);
    }
    double dfunction(double x) {
        return 1 + x * sin(x);
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainWidget w = mainWidget(in::function, in::dfunction);
    w.show();
    return QApplication::exec();
}