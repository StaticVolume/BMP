#include "display.h"
#include "point.h"


Display::Display(bool in_curs_check , char in_exit ): curs_check{in_curs_check}, exit{in_exit}{
     initscr();
     start_color();

     init_pair(Color::WHITE, COLOR_WHITE, COLOR_BLACK);
     init_pair(Color::Black, COLOR_BLACK,  COLOR_BLACK);
     init_pair(Color::BLUE, COLOR_BLUE, COLOR_BLACK);
     init_pair(Color::GREEN, COLOR_GREEN, COLOR_BLACK);
     init_pair(Color::RED, COLOR_RED, COLOR_BLACK);


     noecho();
     curs_set(curs_check);
     getmaxyx(stdscr, heigth, width);
}

 unsigned int Display::GetDisplayWidth()const{
    return width;
}

 unsigned int Display::GetDisplayHeigth()const{
    return heigth;
}

void Display::Stop(char in_ch){
    switch (in_ch) {
        case 'p':{
            refresh();
            endwin();
        }   break;
        default:
        break;
    }
}

void Display::DrawPoint(const Point& in_point) const{
    move(in_point.GetPointY(), in_point.GetPointX());
    attron(COLOR_PAIR(in_point.GetPointColor()));
    addch(in_point.GetPointStyle());
    attroff(COLOR_PAIR(in_point.GetPointColor()));
    refresh();
}


Display::~Display(){}
