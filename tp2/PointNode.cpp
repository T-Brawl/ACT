#include "PointNode.h"

PointNode::PointNode(Point *p):point(p), next(0), previous(0){
};

PointNode::PointNode(Point *p, PointNode *prev, PointNode *nex):point(p), previous(prev), next(nex){
};

PointNode* PointNode::getNext(){
  return next;
};

PointNode* PointNode::getPrevious(){
  return previous;
};

Point *getPoint(){
  return point;
}

void PointNode::setNext(PointNode *nex){
  next=nex;
}

void PointNode::setPrevious(PointNode *prev){
  previous=prev;
}
