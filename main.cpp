#include <iostream>
#include <QApplication>
#include <cmath>
#include "src/function.cpp"
#include "src/graph.cpp"
#include "src/plane.cpp"

double test_f(double x) {
    return x * sin(x);
}

namespace in {
    double function(double x) {
        return myFunctions::integral(0.0, x, test_f);
    }
    const int color = 1;
    const bool grid = true;
    const double a = -10;
    const double b = 10;
    const int x1 = 0;
    const int y1 = 0;
    const int x2 = 700;
    const int y2 = 700;
    const double eps = 1e-2;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    settings.setSettings(in::x1, in::y1, in::x2, in::y2, in::grid, in::eps);
    Function func = Function(in::function);
    Graph graph = Graph(&func, in::a, in::b);
    Plane plane = Plane(&graph, COLOR(in::color));
    QLabel l;
    l.setPicture(plane.getPicture());
    l.setWindowTitle("Universal Graph Builder");
    l.show();
    return QApplication::exec();
}