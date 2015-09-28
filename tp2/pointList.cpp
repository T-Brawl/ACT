#include "PointNode.h"

PointNode::PointNode(Point p):point(p), next(NULL), previous(NULL){
};

PointNode::PointNode(Point p, PointNode prev, PointNode nex):point(p), previous(prev), next(nex){
};

Point PointNode::getNext(){
  return next;
}

Point PointNode::getPrevious(){
  return previous;
}
