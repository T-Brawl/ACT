#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

double temps;
clock_t t1, t2;

int symmetry = 1;

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
    if(m == 1 && n == 1) return 0;

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
		tab[k][l][o][p].val=0;
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

int position_dynamic(unsigned int m, unsigned int n, unsigned int i, unsigned int j){
    int tmp,res;
    unsigned int cpt,reset;
    res = 0;
    reset = 0;

	/*
	* Same principle as position_naive but smarter since it saves intermediate
	* values in a 4 dimensional array. The function checked if the result
	* for m,n,i and j have been already computed. 
	*
	* It also uses the symmetric properties if the integer symmetry is not zero.
	*/

    if(tab[m][n][i][j].flag) {
        return tab[m][n][i][j].val;
    }

    if(m == 1 && n == 1 && i == 0 && j == 0) {
        tab[1][1][0][0].val = 0;
        tab[1][1][0][0].flag = 1;
        return tab[1][1][0][0].val;
    }

    if( symmetry && ((i>(m/2)) ||  (j>(n/2))) ) {

        int a,b;
        a = (i>(m/2))?m-1-i:i;
        b = (j>(n/2))?n-1-j:j;

        return position_dynamic(m,n,a,b);
    }


    for(cpt=1; cpt<m;cpt++){

        if(cpt<=i){
            tmp = position_dynamic(m-cpt, n, i-cpt,j);
        }else{
            tmp = position_dynamic(cpt, n,i,j);
        }

        if(tmp <= 0) {res = 0; reset = 1;}
        if(reset) {
            if(tmp <= 0) res = res?max(tmp,res):tmp;
        } else {
            res=res?max(tmp,res):tmp;
        }

    }

    for(cpt=1; cpt<n;cpt++){

        if(cpt<=j){
            tmp = position_dynamic(m, n-cpt, i,j-cpt);
        }else{
            tmp = position_dynamic(m, cpt,i,j);
        }

        if(tmp <= 0) {res = 0; reset = 1;}
        if(reset) {
            if(tmp <= 0) res = res?max(tmp,res):tmp;
        } else {
            res=res?max(tmp,res):tmp;
        }
    }
    if(reset) res = 1-res; else res = -1-res;
    tab[m][n][i][j].flag = 1;
    tab[m][n][i][j].val = res;
    return res;
}

void test(){

int res,i,j;

    t1 = clock();
    init_tab(100,100);
    t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("Initialization of a 4 dimensions array for a 100 * 100 chocolate bar.\nThis array contains all the values of position_dynamic(m,n,i,j) such that\n1 <= m <= 100, 1 <= n <= 100, 0 <= i< m and 0 <= j < n\nInitialization time = %f second(s)\n\nNotice : by default, the function position_dynamic uses symmetric properties of the chocolate bar.\n\n",temps);

    printf("position_dynamic(100,100,50,50) = ");
	fflush(stdout);
    t1 = clock();
    res = position_dynamic(100,100,50,50);
    t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("%d\nDuration = %f second(s)\n\n",res,temps);


    free_tab(100,100);
    init_tab(100,100);
    printf("We destroy the array then we create a fresh new one.\n\n");

    printf("position_dynamic(100,100,48,52) = ");
	fflush(stdout);
    t1 = clock();
    res = position_dynamic(100,100,48,52);
    t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("%d\nDuration = %f second(s)\n\n",res,temps);


    free_tab(100,100);
    init_tab(127,127);
    printf("We destroy again the array but we make one bigger: an array for a 127 * 127 bar this time...\n");

    printf("Search the array for (i,j) pairs such that\nposition_dynamic(127,127,i,j) = 127\nExpected result = 4 pairs within the next 3-5 minutes\n\n");
    time_t debut,fin;
    double diff;
    time(&debut);
    for(i=0;i<=126;i++) {
        for(j=0;j<=126;j++) {
            if(position_dynamic(127,127,i,j) == 127) {
                    time(&fin);
                    diff = difftime(fin,debut);
                    printf("Pair (%d,%d) found\t\t%.0f minutes and %.0f seconds\n",i,j,floor(diff/60),fmod(diff,60));
            }
        }
    }
    time(&fin);
    diff = difftime(fin,debut);
    printf("Array search time = %.0f minutes and %.0f seconds\n\n",floor(diff/60),fmod(diff,60));

    free_tab(127,127);
    printf("Destruction of the array.\nJob's done.\n");

}

int main (int argc, char *argv[]){

    if(argc==5){

        t1 = clock();
        int res = position_dynamic(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
        t2 = clock();
        temps = (double)(t2-t1)/CLOCKS_PER_SEC;
        printf("position_dynamic using symmetry (%d,%d,%d,%d) = %d\nTime = %f seconds",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),res,temps);

    } else if (argc==6) {

        if(argv[5][0] == 'n') {
            t1 = clock();
            int res = position_naive(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
            t2 = clock();
            temps = (double)(t2-t1)/CLOCKS_PER_SEC;
            printf("position_naive(%d,%d,%d,%d) = %d\nTime = %f seconds",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),res,temps);
        }

        if(argv[5][0] == 'd') {
            t1 = clock();
            symmetry = 0;
            int res = position_dynamic(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
            t2 = clock();
            temps = (double)(t2-t1)/CLOCKS_PER_SEC;
            printf("position_dynamic without symmetry (%d,%d,%d,%d) = %d\nTime = %f seconds",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),res,temps);
        }

        if(argv[5][0] == 'f') {
            t1 = clock();
            int res = position_dynamic(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
            t2 = clock();
            temps = (double)(t2-t1)/CLOCKS_PER_SEC;
            printf("position_dynamic using symmetry (%d,%d,%d,%d) = %d\nTime = %f seconds",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),res,temps);
        }

    } else test();

    return 0;
}
