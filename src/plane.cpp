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

void delZeros(string &s) {
    while (s[s.size() - 1] == '0' or s[s.size() - 1] == '.') {
        s.pop_back();
    }
}

class Plane {
public:
    Plane(Graph *graph, COLOR color) {
        x1_ = settings.x1_; y1_ = settings.y1_; x2_ = settings.x2_; y2_ = settings.y2_;
        graph_ = graph;
        color_ = color;
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
    bool isXAxis_ = false, isYAxis_ = false;

    void paintLines(vector<double> &points) {
        QPainter qp(&p_);
        qp.setRenderHint(QPainter::Antialiasing);
        qp.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
        paintAxes(&qp);
        paintNotches(&qp);
        qp.setPen(QPen(getQtColor(color_), 2, Qt::SolidLine, Qt::RoundCap));
        for (int i = 0; i < points.size() - 1; i++) {
            qp.drawLine(x1_ + i, y2_ - (int)points[i], x1_ + i + 1, y2_ - (int)points[i + 1]);
        }
        qp.end();
    }

    void paintAxes(QPainter *qp) {
        if (graph_->getA() < 0.0 && graph_->getB() > 0.0) {
            isYAxis_ = true;
            auto zero_x = graph_->getXZero();
            qp->drawLine(x1_ + zero_x, y1_, x1_ + zero_x, y2_);
        }
        auto zero_y = graph_->getYZero();
        if (zero_y != -1) {
            isXAxis_ = true;
            qp->drawLine(x1_, y2_ - zero_y, x2_, y2_ - zero_y);
        }
    }

    void paintNotches(QPainter *qp) {
        if (isXAxis_) {
            auto zero_y = graph_->getYZero();
            auto len_x = graph_->getXOneLength();
            int x_starting_pos;
            if (isYAxis_) {
                x_starting_pos = x1_ + graph_->getXZero();
            }
            else {
                x_starting_pos = (x2_ - x1_) / 2;
            }
            for (int line_x = x_starting_pos; line_x <= x2_; line_x += len_x) {
                qp->drawLine(line_x, y2_ - zero_y + 5, line_x, y2_ - zero_y - 5);
            }
            for (int line_x = x_starting_pos - len_x; line_x >= x1_; line_x -= len_x) {
                qp->drawLine(line_x, y2_ - zero_y + 5, line_x, y2_ - zero_y - 5);
            }
            string x_s = to_string(pow(10, graph_->getXOneLength(true)));
            delZeros(x_s);
            qp->drawText(x_starting_pos + len_x - 3, y2_ - zero_y - 10, QString::fromStdString(x_s));
        }
        if (isYAxis_) {
            auto zero_x = graph_->getXZero();
            auto len_y = graph_->getYOneLength();
            int y_starting_pos;
            if (isXAxis_) {
                y_starting_pos = y2_ - graph_->getYZero();
            }
            else {
                y_starting_pos = (y2_ - y1_) / 2;
            }
            for (int line_y = y_starting_pos; line_y <= y2_; line_y += len_y) {
                qp->drawLine(x1_ + zero_x - 5, line_y, x1_ + zero_x + 5, line_y);
            }
            for (int line_y = y_starting_pos - len_y; line_y >= y1_; line_y -= len_y) {
                qp->drawLine(x1_ + zero_x - 5, line_y, x1_ + zero_x + 5, line_y);
            }
            string y_s = to_string(pow(10, graph_->getYOneLength(true)));
            delZeros(y_s);
            qp->drawText(x1_ + zero_x - 30, y_starting_pos - len_y + 5, QString::fromStdString(y_s));
        }
    }

    void graphPaint() {
        vector<double> points = *graph_->getValues();
        paintLines(points);
    }
};

#endif