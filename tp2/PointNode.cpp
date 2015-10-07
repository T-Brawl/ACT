#include "PointNode.h"
#include <iostream> 
#include <fstream>

using namespace std;

PointNode::PointNode(Point *p):point(p), next(NULL), previous(NULL){
}

PointNode::PointNode(Point *p, PointNode *prev, PointNode *nex){
  point=p;
  cerr << "fail avec "<< nex << endl;
  previous=prev;
  next=nex;
}

PointNode* PointNode::getNext(){
  return next;
}

PointNode* PointNode::getPrevious(){
  return previous;
}

Point *PointNode::getPoint(){
  return point;
}

void PointNode::setNext(PointNode *nex){
  next=nex;
}

void PointNode::setPrevious(PointNode *prev){
  previous=prev;
}
