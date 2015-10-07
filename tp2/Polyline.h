#include "PointNode.h"
#include <string>

class Polyline{
 private:
  PointNode *begin;
  PointNode *end;
  int leng;
  PointNode * insertFusion(PointNode *it1,PointNode *it2,Point *last1,Point *last2,Polyline *result);

 public:
  Polyline();
  Polyline(PointNode *p);
  Polyline(PointNode *p, PointNode *end, int length);
  PointNode *atBegin();
  PointNode *atEnd();
  void addBefore(PointNode *pn, Point *p);
  void addAfter(PointNode *pn, Point *p);
  int length();
  void split(Polyline *arr[]);
  Polyline *resolve();
  Polyline *fusion(Polyline *p);
  std::string toString();
};
