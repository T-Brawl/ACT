#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


struct case_position {
    unsigned int check;
    int val;
};

typedef struct case_position * case_p;

static case_p ****res_d;

int position_naive(unsigned int m, unsigned int n, unsigned int i, unsigned int j){
    int tmp,res;
    unsigned int cpt,flag;
    res = 0;
    /*
    * The integer flag is meant to guide the automata.
    * The flag is 0 as long as the recursive calls of position return stricly positive values.
    * When one recursive call return a 0 or a negative value, flag is set to 1,
    * res is reset to 0 and will be affected only by recursive calls negative values.
    *
    */
    flag = 0;
    if(m == 1 && n == 1 && i == 0 && j ==0) return 0;

    for(cpt=1; cpt<m;cpt++){
        if(cpt<=i){
            tmp = position_naive(m-cpt, n, i-cpt,j);
        }else{
            tmp = position_naive(cpt, n,i,j);
        }
        if(tmp <= 0) {res = 0; flag = 1;}
        if(flag) {
            if(tmp <= 0) res = res?max(tmp,res):tmp;
        } else {
            res=res?max(tmp,res):tmp;
        }
    }

    for(cpt=1; cpt<n;cpt++){
        if(cpt<=j){
            tmp = position_naive(m, n-cpt, i,j-cpt);
        }else{
            tmp = position_naive(m, cpt,i,j);
        }
        if(tmp <= 0) {res = 0; flag = 1;}
        if(flag) {
            if(tmp <= 0) res = res?max(tmp,res):tmp;
        } else {
            res=res?max(tmp,res):tmp;
        }
    }
    if(flag) res = 1-res; else res = -1-res;
    return res;
}

void add_cell(int d0,int d1,int d2,int d3, int val){
  struct case_position *cell = malloc(sizeof(struct case_position));
  cell->check = 1;
  cell->val = val;
  res_d[d0][d1][d2][d3] = cell;
}

int dyna_rec(unsigned int m, unsigned int n, unsigned int i, unsigned int j){
  if (res_d[m][n][i][j]==NULL){
    return rec_for_dyna(m, n,i,j);
  }else{
    return res_d[m][n][i][j]->val;
  }
}

int rec_for_dyna(unsigned int m, unsigned int n, unsigned int i, unsigned int j){
  int tmp,res;
    unsigned int cpt,flag;
    res = 0;
    /*
    * The integer flag is meant to guide the automata.
    * The flag is 0 as long as the recursive calls of position return stricly positive values.
    * When one recursive call return a 0 or a negative value, flag is set to 1,
    * res is reset to 0 and will be affected only by recursive calls negative values.
    *
    */
    flag = 0;
    if(m == 1 && n == 1) return 0;

    for(cpt=1; cpt<m;cpt++){
        if(cpt<i){
            tmp = dyna_rec(m-cpt, n, i-cpt,j);
        }else{
            tmp = dyna_rec(cpt, n,i,j);
        }
        if(tmp <= 0) {res = 0; flag = 1;}
        if(flag) {
            if(tmp <= 0) res = res?max(tmp,res):tmp;
        } else {
            res=res?max(tmp,res):tmp;
        }
    }

    for(cpt=1; cpt<n;cpt++){
        if(cpt<j){
            tmp = dyna_rec(m, n-cpt, i,j-cpt);
        }else{
            tmp = dyna_rec(m, cpt,i,j);
        }
        if(tmp <= 0) {res = 0; flag = 1;}
        if(flag) {
            if(tmp <= 0) res = res?max(tmp,res):tmp;
        } else {
            res=res?max(tmp,res):tmp;
        }
    }
    if(flag) res = 1-res; else res = -1-res;
    return res;
}

int position_dynamique(unsigned int m, unsigned int n, unsigned int i, unsigned int j){
  int k,l,o;
  res_d = (case_p****)malloc(sizeof(case_p***)*m);
  for(k=0; k<m; k++)
    {
      res_d[k] = (case_p***)malloc(sizeof(case_p**)*n);
      for(l=0; l<n; l++)
	{
	  res_d[k][l] = (case_p**)malloc(sizeof(case_p*)*i);
	  for( o=0; o<i;o++)
	    {
	      res_d[k][l][o] = (case_p*)malloc(sizeof(case_p)*j);
	    }
	}
    }
  
  add_cell(0,0,0,0,0);

  dyna_rec(m-1,n-1,i-1,j-1);
  //free nothing, it's program's end  :D
  return 0;
}

void print_chocolate(unsigned int m, unsigned int n, unsigned int i, unsigned int j) {
    int row=0,column=0;
    printf("  ");
    for(row;row<m;row++) printf("%d ",row);
    printf("\n");
    for(column;column<n;column++) {
            printf("%d ",column);
            for(row=0;row<m;row++) {
                if(i == row && j == column) printf("X "); else printf(". ");
            }
            printf("\n");
    }
    printf("\n");
}


int main (int argc, char *argv[]){

    int res;

    res = position_naive(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    //res = position_naive(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    //res = position_naive(100,100,50,50);
    printf("Résultat = %d\n",res);

    return 0;
}
