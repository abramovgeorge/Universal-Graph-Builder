#ifndef _MAINWIDGET_CPP_
#define _MAINWIDGET_CPP_

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <cmath>
#include "plane.cpp"

class mainWidget : public QWidget {
public:
    mainWidget(double (*f1)(double), double (*f2)(double)) {
        func_ = f1; dfunc_ = f2;
        QPushButton *updButton = new QPushButton("Next step", this);
        updButton->setGeometry(750, 0, 100, 50);
        QLineEdit *readA = new QLineEdit(this);
        QLineEdit *readB = new QLineEdit(this);
        QLineEdit *readX0 = new QLineEdit(this);
        QLineEdit *readEps1 = new QLineEdit(this);
        QLineEdit *readEps2 = new QLineEdit(this);
        readA->setPlaceholderText("input a:");
        readB->setPlaceholderText("input b:");
        readX0->setPlaceholderText("input x0:");
        readEps1->setPlaceholderText("input eps1:");
        readEps2->setPlaceholderText("input eps2:");
        readA->setGeometry(750, 60, 100, 50);
        readB->setGeometry(750, 120, 100, 50);
        readX0->setGeometry(750, 180, 100, 50);
        readEps1->setGeometry(750, 240, 100, 50);
        readEps2->setGeometry(750, 300, 100, 50);
        QPushButton *drawButton = new QPushButton("Draw graph", this);
        drawButton->setGeometry(750, 360, 100, 50);
        QLabel *picture = new QLabel(this);
        picture->setGeometry(0, 0, 700, 700);
        QLabel *root = new QLabel(this);
        root->setGeometry(750, 420, 100, 20);
        QLabel *valueInRoot = new QLabel(this);
        valueInRoot->setGeometry(750, 450, 100, 20);
        connect(updButton, &QPushButton::clicked, this, [this, picture, readA, readB, readX0,
                readEps1, readEps2, root, valueInRoot](){
            newStep(picture, readA, readB, readX0, readEps1, readEps2, root, valueInRoot);
        });
        connect(drawButton, &QPushButton::clicked, this, [this, picture, readA, readB, readX0,
                                                          readEps1, readEps2, root, valueInRoot](){
            start(picture, readA, readB, readX0, readEps1, readEps2, root, valueInRoot);
        });
    }

private slots:
    void start(QLabel *picture, QLineEdit *readA, QLineEdit *readB,
               QLineEdit *readX0, QLineEdit *readEps1, QLineEdit *readEps2, QLabel *root, QLabel *valueInRoot) {
        curLines = 0;
        drawCurrent(picture, readA, readB, readX0, readEps1, readEps2, root, valueInRoot);
    }

    void newStep(QLabel *picture, QLineEdit *readA, QLineEdit *readB,
              QLineEdit *readX0, QLineEdit *readEps1, QLineEdit *readEps2, QLabel *root, QLabel *valueInRoot) {
        curLines += 2;
        drawCurrent(picture, readA, readB, readX0, readEps1, readEps2, root, valueInRoot);
    }

private:
    Plane *plane_;
    double (*func_)(double), (*dfunc_)(double);
    int curLines = 0;

    void drawCurrent(QLabel *picture, QLineEdit *readA, QLineEdit *readB,
                     QLineEdit *readX0, QLineEdit *readEps1, QLineEdit *readEps2, QLabel *root, QLabel *valueInRoot) {
        settings.setSettings(0, 0, 700, 700, true, readEps1->text().toDouble(),
                             readEps2->text().toDouble());
        Function func = Function(func_, dfunc_);
        Graph graph = Graph(&func, readA->text().toDouble(), readB->text().toDouble());
        Plane plane = Plane(&graph, COLOR(1));
        auto out = plane.solve(readX0->text().toDouble());
        root->setText(QString::fromStdString("x = ") + QString::number(out.first));
        valueInRoot->setText(QString::fromStdString("f(x) = ") + QString::number(out.second));
        plane_ = &plane;
        picture->setPicture(plane_->getPicture(curLines));
    }
};

#endif