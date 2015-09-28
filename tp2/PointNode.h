#include "Point.h"

class PointNode{
  private:
  Point *point;
  PointNode *next;
  PointNode *previous;

  public:
  PointNode(Point *p);
  PointNode(Point *p, PointNode *prev, PointNode *nex);
  PointNode* getPrevious();
  PointNode* getNext();
  Point *getPoint();
  void setNext(PointNode *nex);
  void setPrevious(PointNode *prev);
};
