#include "Point.h"

Point::Point():x(0),y(0){
};

Point::Point(int coord, int absc):x(coord),y(absc){
};

int Point::getX(){
  return x;
};

int Point::getY(){
  return y;
};
