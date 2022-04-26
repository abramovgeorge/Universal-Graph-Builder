#ifndef _PLANE_CPP_
#define _PLANE_CPP_

#include <iostream>
#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include <QPicture>
#include "settings.cpp"
#include "graph.cpp"

using namespace std;

QBrush getQtColor(COLOR color) {
    switch (color) {
        case COLOR::BLACK:
            return Qt::black;
        case COLOR::RED:
            return Qt::red;
        case COLOR::BLUE:
            return Qt::blue;
    }
}

class Plane {
public:
    Plane(Graph *graph, COLOR color) {
        x1_ = settings.x1_; y1_ = settings.y1_; x2_ = settings.x2_; y2_ = settings.y2_;
        graph_ = graph;
        color_ = color;
        //p_.setGeometry(x1_, y1_, x2_ - x1_, y2_ - y1_); //plane size
    }

    void paintLines(vector<double> &points) {
        QPainter qp(&p_);
        qp.setRenderHint(QPainter::Antialiasing);
        qp.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        if (graph_->getA() < 0.0 && graph_->getB() > 0.0) {
            auto zero_x = graph_->getXZero();
            qp.drawLine(zero_x, y1_, zero_x, y2_);
        }
        auto zero_y = graph_->getYZero();
        if (zero_y != -1) {
            qp.drawLine(x1_, y2_ - zero_y, x2_, y2_ - zero_y);
        }
        qp.setPen(QPen(getQtColor(color_), 3, Qt::SolidLine, Qt::RoundCap));
        for (int i = 0; i < points.size() - 1; i++) {
            qp.drawLine(x1_ + i, y2_ - (int)points[i], x1_ + i + 1, y2_ - (int)points[i + 1]);
        }
        qp.end();
    }

    void graphPaint() {
        vector<double> points = *graph_->getValues();
        paintLines(points);
    }

    QPicture getPicture() {
        graphPaint();
        return p_;
    }

private:
    int x1_, y1_, x2_, y2_;
    Graph *graph_;
    COLOR color_;
    QPicture p_;
};

#endif