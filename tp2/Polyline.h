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
}

class PolylineIterator{
 private:
  Polyline *target;

 public:
  Iterator(Polyline p);
  void atBegin();
  void atEnd();
}
