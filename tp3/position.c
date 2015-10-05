#include <stdio.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

int ctoi(char c){
  printf("%d--", c);
  printf("%d\n", c-48);
  return (int)c-48;
}

int position(int m,int n, int i, int j) {
  int cpt,tmpPos, tmpNeg;
  tmpPos=0;
  tmpNeg=-1;
  if(m==1 && n==1){
    return 0;
  }
  for(cpt=1; cpt<m-1;cpt++){
    int tmp;
    if(cpt<=i){
      tmp = position(m-cpt, n, i-cpt,j);
    }else{
      tmp = position(cpt, n,i,j);
    }
    if(tmp>0){
      tmpPos=max(tmpPos,(tmp+1));
    }else{
      if(tmpNeg>0){
	tmpNeg=min(tmpNeg, -(tmp-1));
      }else{
	tmpNeg= -(tmp-1);
      }
    }
  }
  for(cpt=1; cpt<n-1;cpt++){
    int tmp;
    if(cpt<=j){
      tmp = position(m, n-cpt, i,j-cpt);
    }else{
      tmp = position(m, cpt,i,j);
    }
    if(tmp>0){
      tmpPos=max(tmpPos,(tmp+1));
    }else{
      if(tmpNeg>0){
	tmpNeg=min(tmpNeg, -(tmp-1));
      }else{
	tmpNeg= -(tmp-1);
      }
    }
  }
  if(tmpNeg!=-1){
    return tmpNeg;
  }
  return tmpPos;
}




int main(int argc,char **args) {
  int res = position(ctoi(args[1][0]),
		     ctoi(args[2][0]),
		     ctoi(args[3][0]),
		     ctoi(args[4][0]));

  printf("%d",res);

  return 0;
}
