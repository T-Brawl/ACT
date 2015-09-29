
class Svg{
  private:
  Polyline points;
  int html;

  public:
  Svg(Point(*) p);
  /*0 for false*/
  void setHtml();
  std::string getDocument();
}; 

Svg::Svg(Polyline p){
  points = p->resolve();
};

std::string Svg::getDocument(){
  std::string res="";
  res+="<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"300\" height=\"300\" viewBox=\"-10 -150 200 150\"><polyline points=\"";
  res+=points->toString();
  res+="\" stroke=\"green\" stroke-width=\"1\" fill=\"none\" transform=\" scale(5,-5) \" /></svg>";
}

int main(int, char*[]){

}
