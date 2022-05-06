#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <fstream>
#include "include/json.hpp"
#include "src/function.cpp"
#include "src/graph.cpp"
#include "src/plane.cpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    fstream in("../config.json");
    json config;
    in >> config;
    settings.setSettings(config["x1"], config["y1"], config["x2"], config["y2"], config["grid"]);
    Function func = Function(config["function"]);
    Graph graph = Graph(&func, config["a"], config["b"]);
    Plane plane = Plane(&graph, COLOR(config["color"]));
    QLabel l;
    l.setPicture(plane.getPicture());
    l.setWindowTitle("Universal Graph Builder");
    l.show();
    return QApplication::exec();
}