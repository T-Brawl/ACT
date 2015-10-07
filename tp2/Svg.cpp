#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Polyline.h"

using namespace std;

//this function has been copied from the web
vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}



class Svg{
  private:
  Polyline *points;
  int html;

  public:
  Svg(Polyline *p);
  /*0 for false*/
  void setHtml();
  string getDocument();
}; 

Svg::Svg(Polyline *p){
  points = p->resolve();
};

string Svg::getDocument(){
  string res="";
  res+="<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"300\" height=\"300\" viewBox=\"-10 -150 200 150\"><polyline points=\"";
  res+=points->toString();
  res+="\" stroke=\"green\" stroke-width=\"1\" fill=\"none\" transform=\" scale(5,-5) \" /></svg>";
  return res;
}			   

int main(int argc, char** argv){
  string outFile,inFile;
  Polyline *p= new Polyline();
  if(argc!=2){
    if (argc==3){
      outFile =string(argv[2]);
    }else{
      cerr << "Veuillez renseigner un seul fichier" << endl;
      return 1;
    }
  }else {
    outFile = string(argv[1]);
    outFile+=".svg";
  }

  inFile = string(argv[1]);
  ifstream ifile(inFile.c_str());  

  if(ifile){
    int int1, int2 ,int3;
    string buff;
    getline(ifile, buff);
    //int cpt = stoi(buff);
    while(getline(ifile,buff)){
      vector<string> sep;
      sep= split(buff, '\t');
      if (sep.size()==1){
	sep= split(buff, ' ');
	if (sep.size()==1){
	  sep= split(buff, ',');
	  if (sep.size()==1){
	    cerr << "Delimiteur incorrecte utiliser ' ' '\t' ou ','" << endl;
	    exit(10);
	  }
	}
      }
      int1 = stoi(sep[0]);
      int2 = stoi(sep[1]);
      int3 = stoi(sep[2]);
      p->addAfter(p->atEnd(), new Point(int1, int2));
      p->addAfter(p->atEnd(), new Point(int3, 0));
    }
    ifile.close(); 
  }else{ 
    cerr << "Impossible d'ouvrir le fichier !" << endl;
    return 2;
  }

  Svg *res= new Svg(p);

  ofstream ofile(outFile, ios::out | ios::trunc);
  if(ofile){
    ofile << res->getDocument();
    ofile.close(); 
  }else{ 
    cerr << "Impossible d'ouvrir le fichier !" << endl;
    return 2;
  }
  
  return 0;
}
