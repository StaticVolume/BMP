#include "point.h"

Point::Point():x{0},y{0},style{'*'}{}

Point::Point(int in_x, int in_y, char in_style,  Color in_color): x{in_x},y{in_y}, style{in_style}, p_color{in_color} {}

bool Point::operator==(const Point& in_point) {

    return (  (x == in_point.x) && (y == in_point.y)   );
}

bool Point::operator!=(const Point& in_point) {

    return !(*this == in_point);
}

Point& Point::operator=(const Point& in_point) {

    if (*this != in_point) {
        x = in_point.GetPointX();
        y = in_point.GetPointY();
        style = in_point.GetPointStyle();
        p_color = in_point.GetPointColor();
    }
    return *this;
}

Point& Point::operator-(const Point& in_point) {

    this->SetPointX(this->GetPointX() - in_point.GetPointX());
    this->SetPointY(this->GetPointY() - in_point.GetPointY());

    return *this;
}

void Point::SetPointStyle(char in_style) {

    style = in_style;
}

void Point::SetPointX(int in_x){

    x = in_x;
}

void Point::SetPointY(int in_y){

    y = in_y;
}
void Point::SetPointColor(Color& in_color) {
    p_color = in_color;
}

void Point::Delete(){

    style  = ' ';
}

