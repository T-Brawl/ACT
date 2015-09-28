#include "Polyline.h"

Polyline::Polyline(PointNode *p):begin(p), end(p){
};

PointNode *Polyline::atBegin(){
  return begin;
}

PointNode *Polyline::atEnd(){
  return end;
}

void Polyline::addBefore(PointNode *pn, Point *p){
  PointNode *newNode;
  newNode = new PointNode(p);
  newNode->setPrevious(pn->getPrevious);
  NewNode->getPrevious()->setNext(NewNode);
  NewNode->setNext(pn);
  pn->setPrevious(newNode);
}

void Polyline::addAfter(PointNode *pn, Point *p){
  PointNode *newNode;
  newNode = new PointNode(p);
  newNode->setNext(pn->getNext);
  NewNode->getNext()->setPrevious(NewNode);
  NewNode->setPrevious(pn);
  pn->setNext(newNode);
}
