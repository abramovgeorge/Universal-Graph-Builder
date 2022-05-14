#ifndef _SETTINGS_CPP_
#define _SETTINGS_CPP_

#include <iostream>

enum class COLOR{
    BLACK,
    RED,
    BLUE
};

struct Settings{
    Settings() {}

    void setSettings(int x1, int y1, int x2, int y2, bool isGrid, double eps) {
        x1_ = x1; y1_ = y1; x2_ = x2; y2_ = y2; isGrid_ = isGrid; eps_ = eps;
    }

    int x1_, y1_, x2_, y2_, isGrid_;
    double eps_;
};

Settings settings;

#endif