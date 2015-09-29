#include "Point.h"
#include "PointNode.h"
#include <string>

class Polyline{
 private:
  PointNode *begin;
  PointNode *end;
  int leng;

 public:
  Polyline(PointNode *p);
  Polyline(PointNode *start, PointNode *stop, int length);
  PointNode *atBegin();
  PointNode *atEnd();
  void addBefore(PointNode *pn, Point *p);
  void addAfter(PointNode *pn, Point *p);
  int length();
  Polyline(*) split(int nb_part);
  Polyline resolve();
  std::string toString();
};
