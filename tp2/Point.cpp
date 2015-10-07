#include "Point.h"
#include <string>
#include <iostream> 
#include <fstream>

Point::Point():x(0),y(0){
}

Point::Point(int coord, int absc):x(coord),y(absc){
}

int Point::getX(){
  return x;
}

int Point::getY(){
  return y;
}

std::string Point::toString(){
  std::cerr << std::to_string(x)+", "<< std::endl;
    std::cerr <<std::to_string(y) << std::endl;
  std::string res;
  res = std::to_string(x)+", "+std::to_string(y);
  std::cerr << res << std::endl;
  return res;
}
