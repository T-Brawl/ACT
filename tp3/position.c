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
    assert(m);
    assert(n);
    assert(i);
    assert(j);
    if(m == 1 && n == 1) return 0;

    for(cpt=1; cpt<m;cpt++){

        if(cpt<i){
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

        if(cpt<j){
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

int position_dynamique(unsigned int m, unsigned int n, unsigned int i, unsigned int j){

    int a,b,c,d;

    struct case_position array[m+1][n+1][i+1][j+1];
    struct case_position *cell = malloc(sizeof(struct case_position));
    cell->check = 0;
    cell->val = 0;
     for(a=1;a<=m;a++)
        for(b=1;b<=n;b++)
            for(c=1;c<=i && i<=m;c++)
                for(d=1;d<=j && j<=n;d++) {
                    printf("%d\t%d\t%d\t%d\n",a,b,c,d);
                    array[a][b][c][d] = *cell;
                }

    array[1][1][1][1].check = 1;

    return 0;
}

int main (int argc, char *argv[]){

    int res;

    //res = position(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    res = position_naive(100,100,50,50);
    printf("Résultat = %d\n",res);

    return 0;
}
