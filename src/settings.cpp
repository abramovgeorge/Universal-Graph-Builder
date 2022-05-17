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

    void setSettings(int x1, int y1, int x2, int y2, bool isGrid, double eps1, double eps2) {
        x1_ = x1; y1_ = y1; x2_ = x2; y2_ = y2; isGrid_ = isGrid; eps1_ = eps1; eps2_ = eps2;
    }

    int x1_, y1_, x2_, y2_, isGrid_;
    double eps1_, eps2_;
};

Settings settings;

#endif