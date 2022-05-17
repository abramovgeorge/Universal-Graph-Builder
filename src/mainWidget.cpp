#ifndef _MAINWIDGET_CPP_
#define _MAINWIDGET_CPP_

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <cmath>
#include "plane.cpp"

class mainWidget : public QWidget {
public:
    mainWidget(Plane *plane) {
        plane_ = plane;
        QHBoxLayout *hbox = new QHBoxLayout(this);
        hbox->setSpacing(5);
        QPushButton *updButton = new QPushButton("Next step", this);
        hbox->addWidget(updButton, 0, Qt::AlignLeft | Qt::AlignTop);
        QLabel *label = new QLabel(this);
        label->setPicture(plane_->getPicture());
        hbox->addWidget(label, 0, Qt::AlignLeft | Qt::AlignTop);
        connect(updButton, &QPushButton::clicked, this, [this, label](){
            draw(label);
        });
    }

private slots:
    void draw(QLabel *label) {
        plane_->update();
        label->setPicture(plane_->getPicture());
    }

private:
    Plane *plane_;
};

#endif