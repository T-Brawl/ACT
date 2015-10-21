#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


struct solu_s{
    int flag;
    int val;
};

typedef struct solu_s solution;

static solution ****tab;

int position(unsigned int m, unsigned int n, unsigned int i, unsigned int j){
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
    assert(i<=m);
    assert(j<=n);
    if(m == 1 && n == 1) return 0;

    for(cpt=1; cpt<m;cpt++){

        if(cpt<=i){
            tmp = position(m-cpt, n, i-cpt,j);
        }else{
            tmp = position(cpt, n,i,j);
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
            tmp = position(m, n-cpt, i,j-cpt);
        }else{
            tmp = position(m, cpt,i,j);
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

void init_tab(int m, int n){
  int res, k,l,o,p;
  tab = (solution ****)malloc(sizeof(solution ***)*(m+1));
  for(k=0; k<=m; k++)
    {
      tab[k] = (solution ***)malloc(sizeof(solution **)*(n +1));
      for(l=0; l<=n; l++)
	{
	  tab[k][l] = (solution**)malloc(sizeof(solution *)*(m + 1));
	  for( o=0; o<=k;o++)
	    {
	      tab[k][l][o] = (solution*)malloc(sizeof(solution)*(n + 1));
	      for(p=0;p<=l;p++){
             		tab[k][l][o][p].flag=0;
		tab[k][l][o][p].val=-69; //( ͡° ͜ʖ ͡°)
	      }
	    }
	}
    }
}

void free_tab(int m, int n){
  int a,b,c;

  for(a=0; a<=m; a++){
      for(b=0; b<=n; b++)
	{
	  for( c=0; c<a;c++)
	    {
	      free(tab[a][b][c]);
	    }
	  free(tab[a][b]);
	}
      free(tab[a]);
    }
  free(tab);
}

int position_dynamique(unsigned int m, unsigned int n, unsigned int i, unsigned int j){
    int tmp,res;
    unsigned int cpt,lol;
    res = 0;
    lol = 0;
//if(m <= 1 || n <= 1 || i <= 1 || j <= 1) printf("%d %d %d %d\n",m,n,i,j);


    if(tab[m][n][i][j].flag) {
        return tab[m][n][i][j].val;
    }

    if(m == 1 && n == 1 && i == 0 && j == 0) {
        tab[1][1][0][0].val = 0;
        tab[1][1][0][0].flag = 1;
        return tab[1][1][0][0].val;
    }

    for(cpt=1; cpt<m;cpt++){

        if(cpt<=i){
            tmp = position_dynamique(m-cpt, n, i-cpt,j);
        }else{
            tmp = position_dynamique(cpt, n,i,j);
        }

        if(tmp <= 0) {res = 0; lol= 1;}
        if(lol) {
            if(tmp <= 0) res = res?max(tmp,res):tmp;
        } else {
            res=res?max(tmp,res):tmp;
        }

    }

    for(cpt=1; cpt<n;cpt++){

        if(cpt<=j){
            tmp = position_dynamique(m, n-cpt, i,j-cpt);
        }else{
            tmp = position_dynamique(m, cpt,i,j);
        }

        if(tmp <= 0) {res = 0; lol = 1;}
        if(lol) {
            if(tmp <= 0) res = res?max(tmp,res):tmp;
        } else {
            res=res?max(tmp,res):tmp;
        }
    }
    if(lol) res = 1-res; else res = -1-res;
    tab[m][n][i][j].flag = 1;
    tab[m][n][i][j].val = res;
    return res;
}

int main (int argc, char *argv[]){

    int res,xd,kappa,keepo;
    double temps;
    clock_t t1, t2;

    //res = position(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    res = position(3,2,2,0);
    printf("Résultat = %d\n",res);
    //t1 = clock();
    init_tab(127,127);

/*
    t2 = clock();
        temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps init_tab= %f\n", temps);
      t1 = clock();
    xd = position_dynamique(100,100,50,50); printf("Résultat = %d\n",xd);
        t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps position_dynamique 100 100 50 50 = %f\n", temps);
           t1 = clock();
    xd = position_dynamique(100,100,48,52); printf("Résultat = %d\n",xd);
        t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps position_dynamique 100 100 48 52 = %f\n", temps);
    free_tab(100,100);
    //position_dynamique(100,100,50,50);*/

    for(kappa=126;kappa>=0;kappa--) {

        for(keepo=126;keepo>=0;keepo--) {
            if(position_dynamique(127,127,kappa,keepo) == 127) printf("%d = (%d,%d)\n",kappa*keepo,kappa,keepo);
        }

    }
    return 0;
}
