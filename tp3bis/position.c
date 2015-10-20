#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum dim_e {width,height};

typedef enum dim_e dimension;

typedef int (func_t)(int,int,int,int);

static func_t* recursive;
static int ****tab;
static int canfree = 1;

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; }) 


int launch_rec_one(int arr[4],dimension d, int cpt){
  if(cpt<=arr[d+2]){
    if(d==0){
      return recursive(arr[0]-cpt, arr[1], arr[2]-cpt,arr[3]);
    }else{
      return recursive(arr[0], arr[1]-cpt, arr[2],arr[3]-cpt);
    }
  }else{
    
    if(d==0){
      return recursive(cpt, arr[1],arr[2],arr[3]);
    }else{
      return recursive(arr[0], cpt, arr[2],arr[3]);
    }
  }
}


int cut_in(int arr[],dimension d){
  int cpt,tmp,res;
  /*res must be never equal to 0, except when m and n are equal to 1*/
  res=1;
  /*we search the greatest int<0 or if not exist, the greatest int
   after we add+1 to the aboslute value and change the sign
   we start to 1 to avoid test the same case in infinity*/
  for(cpt=1; cpt<arr[d];cpt++){
    tmp=launch_rec_one(arr,d,cpt);
    /*we don't have change sign*/
    if(res>0 && tmp>0) {
      res=max(res,tmp+1);
    } else if (res>0 && tmp<=0){
      res=tmp-1;
    } else if (res<0 && tmp<=0){
      res=max(res, tmp-1);
    }/*else {
      res=res;
    }*/
  }
  return - res;
}

int cut_in_height(int arr[]){
  return cut_in(arr, height);
}

int cut_in_width(int arr[]){
  return cut_in(arr, width);
}

int position_naive(int m, int n, int i, int j){
  int width, height;
  int arr[4];
  if(m==1&&n==1){
    return 0;
  }
  arr[0]=m;
  arr[1]=n;
  arr[2]=i;
  arr[3]=j;
  if(n==1){
    return cut_in_width(arr);
  }
  if(m==1){
    return cut_in_height(arr);
  }
  
  width=cut_in_width(arr);
  height=cut_in_height(arr);
   
  if(width<0 && height<0){
    return max( width, height);
  }if(width<0){
    return height;
  }else if(height<0){
    return width;
  }else{
    return min(width, height);
  }
}

/*dyna_one*/
int position_dyna(int m, int n, int i, int j){
  int width, height;
  int arr[4];
  if(tab[m-1][n-1][i][j]!=0){
    return tab[m-1][n-1][i][j];
  }
  if(m==1&&n==1){
    tab[m-1][n-1][i][j]=0;
  }else{
    arr[0]=m;
    arr[1]=n;
    arr[2]=i;
    arr[3]=j;
    if(n==1){
      tab[m-1][n-1][i][j]=cut_in_width(arr);
    }
    if(m==1){
      tab[m-1][n-1][i][j]=cut_in_height(arr);
    }
    width=cut_in_width(arr);
    height=cut_in_height(arr);
   
    if(width<0 && height<0){
      tab[m-1][n-1][i][j]=max( width, height);
    }if(width<0){
      tab[m-1][n-1][i][j]=height;
    }else if(height<0){
      tab[m-1][n-1][i][j]=width;
    }else{
      tab[m-1][n-1][i][j]=min( width, height);
    }
  }
  //printf("%d %d %d %d  console.log %d \n",m,n,i,j,tab[m-1][n-1][i][j]);
  return tab[m-1][n-1][i][j];
}

int position_dyna_fast(int m, int n, int i, int j){
  int width, height, arr[4],tmp;
  
  if(i<j){
    tmp=i;
    i=j;
    j=i;
  }
  if((m/2)<i){
    i=m-i>=0?m-i:i-m;
  }
  if((n/2)<j){
    j=n-j>=0?n-j:j-n;
  }
  if(tab[m-1][n-1][i][j]!=0){
    return tab[m-1][n-1][i][j];
  }
  if(m==1&&n==1){
    tab[m-1][n-1][i][j]=0;
  }else{
    arr[0]=m;
    arr[1]=n;
    arr[2]=i;
    arr[3]=j;
    if(n==1){
      tab[m-1][n-1][i][j]=cut_in_width(arr);
    }
    if(m==1){
      tab[m-1][n-1][i][j]=cut_in_height(arr);
    }
    width=cut_in_width(arr);
    height=cut_in_height(arr);
   
    if(width<0 && height<0){
      tab[m-1][n-1][i][j]=max( width, height);
    }if(width<0){
      tab[m-1][n-1][i][j]=height;
    }else if(height<0){
      tab[m-1][n-1][i][j]=width;
    }else{
      tab[m-1][n-1][i][j]=min( width, height);
    }
  }
  /*printf("%d %d %d %d  console.log %d \n",m,n,i,j,tab[m-1][n-1][i][j]);*/
  return tab[m-1][n-1][i][j];
}


int position_dyna_one(int m, int n, int i, int j){
  int k,l,o,p,solution;
  tab = (int****)malloc(sizeof(int***)*m);
  for(k=0; k<m; k++)
    {
      tab[k] = (int***)malloc(sizeof(int**)*n);
      for(l=0; l<n; l++)
	{
	  tab[k][l] = (int**)malloc(sizeof(int*)*i);
	  for( o=0; o<i;o++)
	    {
	      tab[k][l][o] = (int*)malloc(sizeof(int)*j);
	      for(p=0;p<j;p++){
		tab[k][l][o][p]=0;
	      }
	    }
	}
    }
  
  solution =position_dyna(m,n,i-1,j-1);
  if(canfree){
  for(k=0; k<m; k++)
    {
      for(l=0; l<n; l++)
	{
	  for( o=0; o<i;o++)
	    {
	      free(tab[k][l][o]);    
	    }
	  free(tab[k][l]);
	}
      free(tab[k]);
    }
  free(tab);
  }

  return solution;
}

void search_for(int m, int n, int eq){
  int i, j;
  int res;
  
  for(i=1;i<m-1;i++){
    for(j=1;j<n-1;j++){
	if (tab[m-1][n-1][i][j] == eq) printf("couple (%d, %d) \n",i,j);
    }
  }
  printf("\n");
}

int main (int argc, char *argv[]){

    int res;
    float temps;
    clock_t t1, t2;
    t1 = clock();
    if(argc==4){
      recursive=position_dyna;
      search_for(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    }else if(argc>5){
      if (argv[5][0]=='n'){
	recursive=position_naive;
	res = position_naive(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])-1, atoi(argv[4])-1);
	printf("Résultat = %d\n",res);
      }else if(argv[5][0]=='d'){
	recursive=position_dyna;
	res = position_dyna_one(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	printf("Résultat = %d\n",res);
      }else if(argv[5][0]=='f'){
	recursive=position_dyna_fast;
	res = position_dyna_one(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	printf("Résultat = %d\n",res);
      }else{
	recursive=position_dyna;
	res = position_dyna_one(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	printf("Résultat = %d\n",res);
      }
    }else{
      recursive=position_dyna;
      res = position_dyna_one(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
      //if(!canfree) search_for(127,127,127);
      printf("Résultat = %d\n",res);
    }
     
    
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

    return 0;
}
