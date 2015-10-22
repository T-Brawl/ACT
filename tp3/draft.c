#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
int symetrie = 1;

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
    assert(i<=m);
    assert(j<=n);
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

int position_dynamique(unsigned int m, unsigned int n, unsigned int i, unsigned int j){
    int tmp,res;
    unsigned int cpt,reset;
    res = 0;
    reset = 0;

    if(tab[m][n][i][j].flag) {
        return tab[m][n][i][j].val;
    }

    if(m == 1 && n == 1 && i == 0 && j == 0) {
        tab[1][1][0][0].val = 0;
        tab[1][1][0][0].flag = 1;
        return tab[1][1][0][0].val;
    }

    if( symetrie && ((i>(m/2)) ||  (j>(n/2))) ) {

        int a,b;
        a = (i>(m/2))?m-1-i:i;
        b = (j>(n/2))?n-1-j:j;

        return position_dynamique(m,n,a,b);
    }


    for(cpt=1; cpt<m;cpt++){

        if(cpt<=i){
            tmp = position_dynamique(m-cpt, n, i-cpt,j);
        }else{
            tmp = position_dynamique(cpt, n,i,j);
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
            tmp = position_dynamique(m, n-cpt, i,j-cpt);
        }else{
            tmp = position_dynamique(m, cpt,i,j);
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
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("Initialisation du tableau pour les calculs d'une tablette de 100 * 100.\nLe tableau va conetenir tous les position_dynamique(m,n,i,j) tel que\n1<=m<=127, 1<=n<=127, 0<=i<=126 et 0<=j<=126\nTemps de l'initialisation = %f seconde(s)\n\nRemarque : position_dynamique utilise par défaut la symétrie.\n\n",temps);

    printf("position_dynamique(100,100,50,50) = ");
    t1 = clock();
    res = position_dynamique(100,100,50,50);
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("%d\nTemps = %f seconde(s)\n\n",res,temps);


    free_tab(100,100);
    init_tab(100,100);
    printf("On supprime la tablette de chocolat 100 * 100 puis on en crée une autre même taille.\n\n");

    printf("position_dynamique(100,100,48,52) = ");
    t1 = clock();
    res = position_dynamique(100,100,48,52);
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("%d\nTemps = %f seconde(s)\n\n",res,temps);


    free_tab(100,100);
    init_tab(127,127);
    printf("On supprime la tablette de chocolat 100 * 100 puis on en crée un autre de 127 * 127...\n");

    printf("Recherche dans le tableau des couples (i,j) tel que\nposition_dynamique(127,127,i,j) = 127\nRésultat attendu = 4 couples en 3 minutes maximum\n\n");
    time_t debut,fin;
    double diff;
    time(&debut);
    for(i=0;i<=126;i++) {
        for(j=0;j<=126;j++) {
            if(position_dynamique(127,127,i,j) == 127) {
                    time(&fin);
                    diff = difftime(fin,debut);
                    printf("Couple (%d,%d) trouvé\t\t%.0f minutes et %.0f secondes\n",i,j,floor(diff/60),fmod(diff,60));
            }
        }
    }
    time(&fin);
    diff = difftime(fin,debut);
    printf("Temps de la recherche = %.0f minutes et %.0f secondes\n\n",floor(diff/60),fmod(diff,60));

    free_tab(127,127);
    printf("Destruction de la tablette 127 * 127.\nTravail terminé.\n");

}

int main (int argc, char *argv[]){

    if(argc==5){

        t1 = clock();
        int res = position_dynamique(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
        t2 = clock();
        temps = (float)(t2-t1)/CLOCKS_PER_SEC;
        printf("position_dynamique avec symétrie (%d,%d,%d,%d) = %d\nTemps = %f",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),temps);

    } else if (argc==6) {

        if(argv[5][0] == 'n') {
            t1 = clock();
            int res = position_naive(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
            t2 = clock();
            temps = (float)(t2-t1)/CLOCKS_PER_SEC;
            printf("position_naive(%d,%d,%d,%d) = %d\nTemps = %f",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),temps);
        }

        if(argv[5][0] == 'd') {
            t1 = clock();
            symetrie = 0;
            int res = position_dynamique(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
            t2 = clock();
            temps = (float)(t2-t1)/CLOCKS_PER_SEC;
            printf("position_dynamique sans symétrie (%d,%d,%d,%d) = %d\nTemps = %f",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),temps);
        }

        if(argv[5][0] == 'f') {
            t1 = clock();
            int res = position_dynamique(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
            t2 = clock();
            temps = (float)(t2-t1)/CLOCKS_PER_SEC;
            printf("position_dynamique avec symétrie (%d,%d,%d,%d) = %d\nTemps = %f",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),temps);
        }

    } else test();

    return 0;
}
