#include <iostream>
#include <QApplication>
#include <cmath>
#include "src/function.cpp"
#include "src/graph.cpp"
#include "src/plane.cpp"
#include "src/mainWidget.cpp"

namespace in {
    double func(double x) {
        return x * sin(x);
    }

    double function(double x) {
        return x + integral(0, x, func);
    }
    double dfunction(double x) {
        return x * sin(x);
    }
    const int color = 1;
    const bool grid = true;
    const double a = -5;
    const double b = 15;
    const double x0 = 9;
    const int x1 = 0;
    const int y1 = 0;
    const int x2 = 700;
    const int y2 = 700;
    const double eps1 = 1e-2;
    const double eps2 = 1e-2;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    settings.setSettings(in::x1, in::y1, in::x2, in::y2, in::grid, in::eps1, in::eps2);
    Function func = Function(in::function, in::dfunction);
    Graph graph = Graph(&func, in::a, in::b);
    Plane plane = Plane(&graph, COLOR(in::color));
    QLabel l;
    auto root = plane.solve(in::x0);
    std::cout << root.first << ' ' << root.second;
    mainWidget w = mainWidget(&plane);
    w.show();
    return QApplication::exec();
}