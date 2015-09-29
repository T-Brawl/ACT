#include "Polyline.h"
#include <std::string>

Polyline::Polyline(PointNode *p):begin(p), end(p), leng(1){
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
  if(pn->getPrevious()==0){
      begin= newNode;
  }else {
      newNode->setPrevious(pn->getPrevious);
      NewNode->getPrevious()->setNext(NewNode);
  }
  NewNode->setNext(pn);
  pn->setPrevious(newNode);
  leng+=1;
}

void Polyline::addAfter(PointNode *pn, Point *p){
  PointNode *newNode;
  newNode = new PointNode(p);
  if(pn->getPrevious()==0){
      end= newNode;
  }else {
      newNode->setNext(pn->getNext);
      NewNode->getNext()->setPrevious(NewNode);
  }
  NewNode->setPrevious(pn);
  pn->setNext(newNode);
  leng+=1;
}

Polyline(*) Polyline::split(int nb_part){
  int lg= leng/2;
  PointNode *current=this->atBegin();
  Polyline res[2];
  for(int i=0; i<lg;i++){
      current= current->getNext();
  }
  res[0]= new polyline(this->atBegin(), current, lg);
  res[1]=new polyline(current->getNext(), this->atEnd(), leng-lg);
  return res;
}

Polyline Polyline::resolve(){
  if(leng<2){
    return this;
  }
  polyline tmp[2];
  tmp =this->split();
  return tmp[2].fusion(tmp[1]);
}

/*complexity : we parse the two polyline and see all points(n points) only time
we have one add ( O(1)) and between one to three comparaisons
The fusion is in O(n)*/
Polyline Polyline::fusion(Polyline p){
  PointNode *current=this->atBegin();
  PointNode *iter=pn->atBegin();
  while(current!=0){
    /*if the point of the second polyline have a point before the first polyline,
      we add the point at the first polyline*/
    if(current->getPoint()->getX() > pn->getPoint()->getX()){
      this->addBefore(current,pn->getPoint());
      pn=pn->getNext();
    } else if (current->getPoint()->getX() == pn->getPoint()->getX()){
      /*we save the heighter point if the two point have the same ordonne*/
      if(current->getPoint()->getX()< pn->getPoint()->getX()){
	current->setPoint(pn->getPoint());
      }
      pn= pn->getNext();
      current=current->getNext();
    } else{
      /*if the point of the first polyline is in place. we only past at the next point*/
      current=current->getNext();
    }
  }
  while(pn!=0){
    this->addAfter(this->atEnd(),pn->getPoint());
  }
};

string Polyline::toString(){
  string res= new string();
  PointNode *current=this->atBegin();
  while(current!=0){
    res+=current->getPoint()->toString();
    res=+=" ";
    current= current->next();
  }
  return res;
}

PolylineIterator::PolylineIterator(Polyline *p):target(p),current(p->atBegin()){
};

void PolylineIterator::atBegin(){
    current=target->atBegin();
};

void PolylineIterator::atEnd(){
    current=target->atEnd();
};

PointNode PolylineIterator::next(){
    current=current->getNext();
    return current;
};
