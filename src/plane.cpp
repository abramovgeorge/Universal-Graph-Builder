#ifndef _PLANE_CPP_
#define _PLANE_CPP_

#include <iostream>
#include <algorithm>
#include <cmath>
#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include <QPicture>
#include "settings.cpp"
#include "graph.cpp"

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

void delZeros(std::string &s) {
    while (s[s.size() - 1] == '0') {
        s.pop_back();
    }
    if (s[s.size() - 1] == '.') {
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

    QPicture getPicture(int curLines) {
        graphPaint(curLines);
        return p_;
    }

    std::pair<double, double> solve(double x0) {
        double eps = settings.eps2_;
        auto xStep = graph_->getXStep(), yStep = graph_->getYStep();
        double prev = x0, next = prev - graph_->getFunc()->calculate(prev) / graph_->getFunc()->calculateD(prev);
        std::vector<std::pair<double, double>> points;
        auto zero_y = graph_->getYZero();
        points.emplace_back((prev - graph_->getA()) / xStep, y2_ - zero_y);
        points.emplace_back((prev - graph_->getA()) / xStep,
                y2_ - (graph_->getFunc()->calculate(prev) - graph_->getFMin()) * yStep);
        while (abs(next - prev) > eps) {
            prev = next;
            next = prev - graph_->getFunc()->calculate(prev) / graph_->getFunc()->calculateD(prev);
            points.emplace_back((prev - graph_->getA()) / xStep, y2_ - zero_y);
            points.emplace_back((prev - graph_->getA()) / xStep,
                                y2_ - (graph_->getFunc()->calculate(prev) - graph_->getFMin()) * yStep);
        }
        solvePoints_ = points;
        return std::make_pair(next, graph_->getFunc()->calculate(next));
    }

    std::vector<std::pair<double, double>> getPoints() {
        return solvePoints_;
    }

private:
    int x1_, y1_, x2_, y2_;
    Graph *graph_;
    COLOR color_;
    QPicture p_;
    std::vector<std::pair<double, double>> solvePoints_;
    bool isXAxis_ = false, isYAxis_ = false;

    void graphPaint(int curLines) {
        std::vector<double> points = *graph_->getValues();
        paintLines(points, curLines);
    }

    void paintLines(std::vector<double> &points, int curLines) {
        QPainter qp(&p_);
        qp.setRenderHint(QPainter::Antialiasing);
        qp.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
        paintAxes(&qp);
        paintNotches(&qp);
        if (settings.isGrid_) {
            paintGrid(&qp);
        }
        qp.setPen(QPen(getQtColor(color_), 2, Qt::SolidLine, Qt::RoundCap));
        for (int i = 0; i < points.size() - 1; i++) {
            qp.drawLine(x1_ + i, y2_ - (int)points[i], x1_ + i + 1, y2_ - (int)points[i + 1]);
        }
        qp.setPen(QPen(Qt::black, 2, Qt::DashDotLine, Qt::RoundCap));
        for (int i = 0; i < std::min(curLines, (int)solvePoints_.size() - 1); i++) {
            qp.drawLine(solvePoints_[i].first, solvePoints_[i].second,
                        solvePoints_[i + 1].first, solvePoints_[i + 1].second);
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
        int count;
        if (isXAxis_) {
            auto zero_y = graph_->getYZero();
            auto len_x = graph_->getXOneLength();
            int x_starting_pos = getXStartingPos();
            double x_starting_val = graph_->getA();
            if (isYAxis_) x_starting_val = 0.0;
            count = 0;
            for (int line_x = x_starting_pos; line_x <= x2_; line_x += len_x) {
                qp->drawLine(line_x, y2_ - zero_y + 5, line_x, y2_ - zero_y - 5);
                std::string x_s = std::to_string(x_starting_val + count * pow(10, graph_->getXOneLength(true)));
                delZeros(x_s);
                qp->drawText(line_x - 20, y2_ - zero_y - 10, QString::fromStdString(x_s));
                count++;
            }
            count = -1;
            for (int line_x = x_starting_pos - len_x; line_x >= x1_; line_x -= len_x) {
                qp->drawLine(line_x, y2_ - zero_y + 5, line_x, y2_ - zero_y - 5);
                std::string x_s = std::to_string(x_starting_val + count * pow(10, graph_->getXOneLength(true)));
                delZeros(x_s);
                qp->drawText(line_x - 20, y2_ - zero_y - 10, QString::fromStdString(x_s));
                count--;
            }
        }
        if (isYAxis_) {
            auto zero_x = graph_->getXZero();
            auto len_y = graph_->getYOneLength();
            int y_starting_pos = getYStartingPos();
            auto a = (graph_->getFMin() *
                           pow(10, graph_->getYOneLength(true)));
            double y_starting_val = floor(graph_->getFMin() *
                    pow(10, -graph_->getYOneLength(true))) / pow(10, -graph_->getYOneLength(true));
            if (isXAxis_) y_starting_val = 0.0;
            count = 0;
            for (int line_y = y_starting_pos; line_y <= y2_; line_y += len_y) {
                qp->drawLine(x1_ + zero_x - 5, line_y, x1_ + zero_x + 5, line_y);
                if (!(isXAxis_ && isYAxis_ && line_y == y_starting_pos)) {
                    std::string y_s = std::to_string(y_starting_val + count * pow(10, graph_->getYOneLength(true)));
                    delZeros(y_s);
                    qp->drawText(x1_ + zero_x - 30, line_y - 5, QString::fromStdString(y_s));
                }
                count--;
            }
            count = 1;
            for (int line_y = y_starting_pos - len_y; line_y >= y1_; line_y -= len_y) {
                qp->drawLine(x1_ + zero_x - 5, line_y, x1_ + zero_x + 5, line_y);
                std::string y_s = std::to_string(y_starting_val + count * pow(10, graph_->getYOneLength(true)));
                delZeros(y_s);
                qp->drawText(x1_ + zero_x - 30, line_y - 5, QString::fromStdString(y_s));
                count++;
            }
        }
    }

    void paintGrid(QPainter *qp) {
        auto prevPen = qp->pen();
        qp->setPen(QPen(Qt::black, 0.5, Qt::SolidLine, Qt::RoundCap));
        auto x_starting_pos = getXStartingPos();
        auto len_x = graph_->getXOneLength();
        for (int line_x = x_starting_pos; line_x <= x2_; line_x += len_x) {
            qp->drawLine(line_x, y1_, line_x, y2_);
        }
        for (int line_x = x_starting_pos - len_x; line_x >= x1_; line_x -= len_x) {
            qp->drawLine(line_x, y1_, line_x, y2_);
        }
        auto y_starting_pos = getYStartingPos();
        auto len_y = graph_->getYOneLength();
        for (int line_y = y_starting_pos; line_y <= y2_; line_y += len_y) {
            qp->drawLine(x1_, line_y, x2_, line_y);
        }
        for (int line_y = y_starting_pos - len_y; line_y >= y1_; line_y -= len_y) {
            qp->drawLine(x1_, line_y, x2_, line_y);
        }
        qp->setPen(prevPen);
    }

    int getXStartingPos() {
        int x_starting_pos;
        if (isYAxis_) {
            x_starting_pos = x1_ + graph_->getXZero();
        }
        else {
            x_starting_pos = x1_;
        }
        return x_starting_pos;
    }

    int getYStartingPos() {
        int y_starting_pos;
        if (isXAxis_) {
            y_starting_pos = y2_ - graph_->getYZero();
        }
        else {
            y_starting_pos = y2_;
        }
        return y_starting_pos;
    }
};

#endif