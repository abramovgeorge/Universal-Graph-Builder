#ifndef _MAINWIDGET_CPP_
#define _MAINWIDGET_CPP_

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <cmath>
#include "plane.cpp"

const int WIDTH = 800;
const int HEIGHT = 700;

class mainWidget : public QWidget {
public:
    mainWidget(double (*f1)(double), double (*f2)(double)) {
        func_ = f1; dfunc_ = f2;
        QPushButton *updButton = new QPushButton("Next step", this);
        QLineEdit *readA = new QLineEdit(this);
        QLineEdit *readB = new QLineEdit(this);
        QLineEdit *readX0 = new QLineEdit(this);
        QLineEdit *readEps1 = new QLineEdit(this);
        QLineEdit *readEps2 = new QLineEdit(this);
        QCheckBox *checkBox = new QCheckBox("grid", this);
        QComboBox *comboBox = new QComboBox(this);
        QPushButton *drawButton = new QPushButton("Draw graph", this);
        QLabel *picture = new QLabel(this);
        QLabel *root = new QLabel(this);
        QLabel *valueInRoot = new QLabel(this);
        picture->setGeometry(0, 0, WIDTH, HEIGHT);

        readA->setPlaceholderText("input a:");
        readB->setPlaceholderText("input b:");
        readX0->setPlaceholderText("input x0:");
        readEps1->setPlaceholderText("input eps1:");
        readEps2->setPlaceholderText("input eps2:");

        comboBox->addItem("Black");
        comboBox->addItem("Red");
        comboBox->addItem("Blue");

        updButton->setGeometry(WIDTH + 50, 0, 100, 50);
        readA->setGeometry(WIDTH + 50, 60, 100, 50);
        readB->setGeometry(WIDTH + 50, 120, 100, 50);
        readX0->setGeometry(WIDTH + 50, 180, 100, 50);
        readEps1->setGeometry(WIDTH + 50, 240, 100, 50);
        readEps2->setGeometry(WIDTH + 50, 300, 100, 50);
        checkBox->setGeometry(WIDTH + 50, 360, 100, 20);
        comboBox->setGeometry(WIDTH + 50, 390, 100, 20);
        drawButton->setGeometry(WIDTH + 50, 420, 100, 50);
        root->setGeometry(WIDTH + 50, 480, 100, 20);
        valueInRoot->setGeometry(WIDTH + 50, 510, 100, 20);

        connect(updButton, &QPushButton::clicked, this, [this, picture, readA, readB, readX0,
                readEps1, readEps2, root, valueInRoot, checkBox, comboBox](){
            newStep(picture, readA, readB, readX0, readEps1, readEps2, root, valueInRoot, checkBox, comboBox);
        });
        connect(drawButton, &QPushButton::clicked, this, [this, picture, readA, readB, readX0,
                readEps1, readEps2, root, valueInRoot, checkBox, comboBox](){
            start(picture, readA, readB, readX0, readEps1, readEps2, root, valueInRoot, checkBox, comboBox);
        });
    }

private slots:
    void start(QLabel *picture, QLineEdit *readA, QLineEdit *readB, QLineEdit *readX0, QLineEdit *readEps1,
               QLineEdit *readEps2, QLabel *root, QLabel *valueInRoot, QCheckBox *checkBox, QComboBox *comboBox) {
        curLines = 0;
        drawCurrent(picture, readA, readB, readX0, readEps1, readEps2, root, valueInRoot, checkBox, comboBox);
    }

    void newStep(QLabel *picture, QLineEdit *readA, QLineEdit *readB, QLineEdit *readX0, QLineEdit *readEps1,
                 QLineEdit *readEps2, QLabel *root, QLabel *valueInRoot, QCheckBox *checkBox, QComboBox *comboBox) {
        curLines += 2;
        drawCurrent(picture, readA, readB, readX0, readEps1, readEps2, root, valueInRoot, checkBox, comboBox);
    }

private:
    Plane *plane_;
    double (*func_)(double), (*dfunc_)(double);
    int curLines = 0;

    void drawCurrent(QLabel *picture, QLineEdit *readA, QLineEdit *readB, QLineEdit *readX0, QLineEdit *readEps1,
                     QLineEdit *readEps2, QLabel *root, QLabel *valueInRoot, QCheckBox *checkBox, QComboBox *comboBox) {
        settings.setSettings(0, 0, WIDTH, HEIGHT, checkBox->isChecked(), readEps1->text().toDouble(),
                             readEps2->text().toDouble());
        Function func = Function(func_, dfunc_);
        Graph graph = Graph(&func, readA->text().toDouble(), readB->text().toDouble());
        Plane plane = Plane(&graph, COLOR(comboBox->currentIndex()));
        auto out = plane.solve(readX0->text().toDouble());
        root->setText(QString::fromStdString("x = ") + QString::number(out.first));
        valueInRoot->setText(QString::fromStdString("f(x) = ") + QString::number(out.second));
        plane_ = &plane;
        picture->setPicture(plane_->getPicture(curLines));
    }
};

#endif