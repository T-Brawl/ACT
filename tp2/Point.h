#include <string>

class Point{
 private:
  int x;
  int y;

 public:
  Point();
  Point(int ord, int abs);
  int getX();
  int getY();
  std::string toString();
};
