#include <stdlib.h>
#include <stdio.h>

struct coord_s {
  int x;
  int y;
};

struct part_s{
  int top_lx;
  int bot_rx;
  int top_ly;
  int bot_ry;
};

struct list_part_s{
  struct list_part_s *next;
  struct list_part_s *previous;
  struct part_s *part;
}

struct cert_s{
  int nb_part;
  struct part_s * arr;
}

int is_valid(struct part_s * arr_p,int arr_p_c, char **arr_t, int ham, int size_max){
  int i,j,k;
  for(i=0;i<arr_p_c;i++){
    struct part_s part= arr_p[i];
    int nb_ham=0;
    int nb_c=0;
    for(j=part.top_lx; j<=part.bot_rx;){
      for(k=part.top_ly;k<=part.bot_ry;k++){
	switch (arr_t[j][k]) {
	case 'u' :
	  return -2;
	case 'H' :
	  nb_ham++;
	default:
	  nb_c++;
	  arr_t[j][k]='u';
	}
      }
    }
    if(nb_ham<ham){
      return -1;
    }
    if(nb_c>size_max){
      return -3
    }
    
  }
  return 0;
}


struct list_part_s * gen_part_for(int i,int j int arr_w,int arr_h,int ham, int size_max, struct list_part_s ptn){
  int k,l;
  for(k=i;k<arr_w;k++){
    
    if(i-k> size_max){
      break;
    }
    int nb_ham=0;
    for(l=j;j<arr_h;l++){
      if((i-k+1)*(j-l+1)>size_max){
	break;
      }
      for(m=i;m<=k; m++){
	if(arr[m][l]=='H'){
	  nb_ham++;
	}
      }
      if(nb_ham>ham){
	ptn->next=(struct list_part_s*)malloc(sizeof(struct list_part_s));
	ptn->next->previous=ptn;
	ptn=ptn->next;
	ptn->part=(struct part_s*)malloc(sizeof(struct part_s));
	ptn->part->top_lx=i;
	ptn->part->bot_rx=j;
	ptn->part->top_ly=k;
	ptn->part->bot_ry=l;
      }
    }
  }
  return ptn;
}

void generation( int ham, int size_max, int arr_h, int arr_w, char **arr){
  int i,j;
  struct list_part_s * head,res;
  res=head=(struct list_part_s*)malloc(size(struct list_part_s));
  for(i=0;i<arr_w;i++){
    for(j=0;j<arr_h;j++){
      head = gen_part_for(i,j,arr_w,arr_h,ham, size_max,head);
    }
  }
  return res;
}


int main(int argc, char** argv){
  FILE* fichier = NULL;
  char** arr;
  char buff[30], tmp[10];
  int ind,old_ind, entry[4],ent_ind;
  ind= old_ind=ent_ind=0;
  fichier = fopen(argv[1], "r");
  fgets(buff, 30, fichier);
  while(true){
    if(buff[ind]== ' '){
      strncpy ( tmp, buff[old_ind], ind - old_ind );
      entry[ent_ind]=atoi[tmp];
    }
    ind++;
  }
  arr= (char **)malloc(sizeof(char *)*entry[0]);
  for(ind=0; ind<entry[0];ind++){
    arr[ind]= (char*) malloc(sizeof(char)*entry[1]);
  }
  ind=0;
  while (fgets(arr[ind], entry[1], fichier) != NULL){
    ind++;
  }
  
}
