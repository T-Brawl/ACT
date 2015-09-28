#include "Point.h"
#include "PointNode.h"

class Polyline{
 private:
  PointNode *begin;
  PointNode *end;

 public:
  Polyline(PointNode *p);
  PointNode *atBegin();
  PointNode *atEnd();
  void addBefore(PointNode *pn, Point *p);
  void addAfter(PointNode *pn, Point *p);
};

class PolylineIterator{
 private:
  Polyline *target;
  PointNode *current;

 public:
  PolylineIterator(Polyline *p);
  void atBegin();
  void atEnd();
  PointNode next();

}
