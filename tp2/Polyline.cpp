#include "Polyline.h"
#include <string>
#include <iostream>  
#include <fstream>

using namespace std;

Polyline::Polyline():begin(0), end(0), leng(0){
};

Polyline::Polyline(PointNode *p):begin(p), end(p), leng(1){
};


Polyline::Polyline(PointNode *p, PointNode *end, int length):begin(p), end(end), leng(length){
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
  if (leng ==0){
    leng=1;
    begin=pn;
    end=pn;
    pn->setNext(pn);
    pn->setPrevious(pn);
  }else{
    if(pn->getPrevious()==0){
      begin= newNode;
    }else {
      newNode->setPrevious(pn->getPrevious());
      newNode->getPrevious()->setNext(newNode);
    }
    newNode->setNext(pn);
    pn->setPrevious(newNode);
    leng+=1;
  }
}

void Polyline::addAfter(PointNode *pn, Point *p){
  PointNode *newNode;
  newNode = new PointNode(p);
  if (leng ==0){
    leng=1;
    begin=pn;
    end=pn;
    pn->setNext(NULL);
    pn->setPrevious(NULL);
  }else{
    if(pn->getNext()==NULL){
      end= newNode;
      newNode->setNext(0);
    }else {
      newNode->setNext(pn->getNext());
      newNode->getNext()->setPrevious(newNode);
    }
    newNode->setPrevious(pn);
    pn->setNext(newNode);
    leng+=1;
  }
}

void Polyline::split(Polyline *arr[]){
  int lg= leng/2;
  PointNode *current=this->atBegin();
  for(int i=0; i<lg;i++){
      current= current->getNext();
  }
  arr[0]= Polyline(this->atBegin(), current, lg).resolve();
  arr[1]= Polyline(current->getNext(), this->atEnd(), leng-lg).resolve();
}

Polyline *Polyline::resolve(){
  if(leng<2){
    return this;
  }
  Polyline *tmp[2];
  this->split(tmp);
  Polyline *pointer=tmp[1];
  return tmp[0]->fusion(pointer);
}

/*complexity : we parse the two polyline and see all points(n points) only time
we have one add ( O(1)) and between one to three comparaisons
The fusion is in O(n)*/
Polyline *Polyline::fusion(Polyline *p){
  Polyline *result= new Polyline();
  PointNode *it1=this->atBegin();
  PointNode *it2=p->atBegin();

  Point *last1= it1->getPoint();
  Point *last2=it2->getPoint();
  while(it1!=0){
    if(it2 ==0){
      result->addAfter(this->atEnd(),it1->getPoint());
      it1 = it1->getNext();
    }else{
      if (it1->getPoint()->getX() > it2->getPoint()->getX()){
	this->insertFusion(it1,it2,last1, last2, result);
      }else{
	this->insertFusion(it2,it1,last2, last1, result);
      }
    }
  }
  while(it2!=0){
    result->addAfter(this->atEnd(),it2->getPoint());
  }
  return result;
};

void Polyline::insertFusion(PointNode *it1,PointNode *it2,Point *last1,Point *last2,Polyline *result){
  if(result->atEnd()->getPoint()->getY()<= it2->getPoint()->getY()){
    if (it1->getPoint()->getY() <= it2->getPoint()->getY()){
      last2=it2->getPoint();
    }else{
      last2=new Point(it2->getPoint()->getX(), last1->getY());
    }
    result->addAfter(this->atEnd(),last2);
  }else{
    last2=it2->getPoint();
  }
  it2 = it2->getNext();
}

std::string Polyline::toString(){
  std::string res="";
  PointNode *current=this->atBegin();
  while(current!=0){
    res+=current->getPoint()->toString();
    res+=" ";
    current= current->getNext();
  }
  return res;
}
