#include "Polyline.h"
#include <std::string>

Polyline::Polyline():begin(0), end(0), leng(0){
};

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
  if (leng ==0){
    leng=1;
    begin=pn;
    end=pn;
  }else{
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
}

void Polyline::addAfter(PointNode *pn, Point *p){
  PointNode *newNode;
  newNode = new PointNode(p);
  if (leng ==0){
    leng=1;
    begin=pn;
    end=pn;
  }else{
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
  Polyline result= new Polyline();
  PointNode *it1=this->atBegin();
  PointNode *it2=pn->atBegin();

  Point *last1= it1->getPoint();
  Point *last2=it2->getPoint();
  while(it1!=0){
    if(t2 ==0){
      result->addAfter(this->atEnd(),it1->getPoint());
      it1 = it1->next;
    }else{
      if (it1->getPoint()->getX() > it2->getPoint()->getX()){
	this->insertFusion(it1,it2,last1, result);
      }else{
	this->insertFusion(it2,it1,last2, result);
      }
    }
  }
  while(it2!=0){
    this->addAfter(this->atEnd(),it2->getPoint());
  }
};

void Polyline::insertFusion(PointNode *it1,PointNode *it2,Point *last1,Polyline *result){
  if(last1->getY()<= it2->getPoint()->getY()){
    if (it1->getPoint()->getY() <= it2->getPoint()->getY()){
      dernier2=it2->getPoint();
    }else{
      dernier2=new Point(it2->getPoint()->getX(), last1->getY());
    }
    result->addAfter(this->atEnd(),dernier2);
  }
  it2 = it2->next;
}

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
