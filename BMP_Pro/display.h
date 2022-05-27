#pragma once
#include<ncurses.h>
#include "point.h"
#include "color.h"

class Display {

private:
    Color color;
    unsigned int width, heigth;
    char exit;
    bool curs_check;

public:

    Display(bool curs_check = false, char in_exit = 'p');
    unsigned int GetDisplayWidth() const;
    unsigned int GetDisplayHeigth() const;
    void Stop(const char in_ch);
    void DrawPoint(const Point& in_point ) const;



     ~Display();
};


