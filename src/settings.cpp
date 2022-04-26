#ifndef _SETTINGS_CPP_
#define _SETTINGS_CPP_

#include <iostream>

using namespace std;

enum class COLOR{
    BLACK,
    RED,
    BLUE
};

struct Settings{
    Settings() {}

    void setSettings(int x1, int y1, int x2, int y2) {
        x1_ = x1; y1_ = y1; x2_ = x2; y2_ = y2;
    }

    int x1_, y1_, x2_, y2_;
};

Settings settings;

#endif