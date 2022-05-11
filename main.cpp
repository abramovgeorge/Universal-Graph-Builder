#include <iostream>
#include <QApplication>
#include <fstream>
#include <cmath>
#include "src/function.cpp"
#include "src/graph.cpp"
#include "src/plane.cpp"

using namespace std;

double in_func(double x) {
    return (pow((x + 3), sin(x + 3))-3)/100;
}

const int in_color = 1;
const bool in_grid = true;
const double in_a = -2;
const double in_b = 10;
const int in_x1 = 0;
const int in_y1 = 0;
const int in_x2 = 700;
const int in_y2 = 700;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    settings.setSettings(in_x1, in_y1, in_x2, in_y2, in_grid);
    Function func = Function(in_func);
    Graph graph = Graph(&func, in_a, in_b);
    Plane plane = Plane(&graph, COLOR(in_color));
    QLabel l;
    l.setPicture(plane.getPicture());
    l.setWindowTitle("Universal Graph Builder");
    l.show();
    return QApplication::exec();
}