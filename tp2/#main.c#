#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct point_s{
  struct point_s* next;
  struct point_s* previous;
  int x;
  int y;
};

struct point_s* add_point(struct point_s* p,int before, int x, int y);

void save_point(struct point_s** res, struct point_s** p);

void consume(struct point_s** p){
  if((*p)->next==NULL){
    free(*p);
    *p=NULL;
  }else{
    *p=(*p)->next;
    free((*p)->previous);
    (*p)->previous=NULL;
  }
}

void try_save( struct point_s** res, struct point_s** ref, struct point_s** p){
	printf("try save");
  if((*res)->x < (*p)->x){
    printf("cas1");
    save_point(res,p);
  }else if((*res)->x > (*p)->x){
    if((*ref)->x > (*p)->x){
      printf("cas2");
      /*in this case, the line of p can't cut the line and create an interssant intersect before the next point)*/
      consume(p);
    }else{
      if((*p)->next->x != (*ref)->x){
	/*intersect */
	printf("cas3");
	*res= add_point(*res,0, (*ref)->x,(*p)->y);
        consume(ref);
      }
	printf("cas3-2");
      consume(p);
    }
  }else{
    printf("cas5");
    consume(p);
  }
}

void save_point(struct point_s** res, struct point_s** p){
  if(*res==NULL){
    *res=*p;
  }else{
    (*res)->next=*p;
    (*p)->previous=*res;
    *res=*p;
    if((*p)->next==NULL){
      *p==NULL;
      printf("p null \n");
    }else{
      *p=(*p)->next;
      (*res)->next->previous=NULL;
      (*res)->next=NULL;
    }
  }
}

void select_point( struct point_s** res, struct point_s** p1, struct point_s** p2){
  if(*res==NULL){
    printf("first save...");
    if((*p1)->x <(*p2)->x){
      save_point(res,p1);
    }else if((*p1)->x > (*p2)->x){
      save_point(res,p2);
    }else if((*p1)->y== (*p2)->y){
      save_point(res,p1);
      consume(p2);
    }else if((*p1)->y < (*p2)->y){
      save_point(res,p1);
    }else{
      save_point(res,p2);
    }
    printf("first save end...");
  }else if((*p1)->x == (*p2)->x){
    printf("x==x\n");
    if((*res)->y==(*p1)->y && (*res)->y== (*p2)->y){
      consume(p1);
      save_point(res,p2);
    }else if((*p1)->y > (*res)->y){
      if((*p1)->y > (*p2)->y){
	save_point(res,p1);
      }else{
	save_point(res,p2);
      }
    }else{
      if((*p1)->y < (*p2)->y){
	save_point(res,p1);
      }else{
	save_point(res,p2);
      }
    }
  }else if((*p1)->x < (*p2)->x){
    
      printf("x1<x2\n");
    try_save(res,p2,p1);
  }else{
    
      printf("x1>x2\n");
      printf("p1 %d %d\n", (*p2)->x, (*p2)->y);
      printf("p1 %d %d\n", (*p1)->x, (*p1)->y);
      printf("res %d %d\n", (*res)->x, (*res)->y);
    try_save(res,p1,p2);
  }
}

struct point_s* add_point(struct point_s* p,int before, int x, int y){
  struct point_s* tmp;
  tmp= (struct point_s*) malloc(sizeof(struct point_s));
  tmp->x=x;
  tmp->y=y;
  if(p!=NULL){
    if(before){
      p->previous=tmp;
      tmp->next=p;
    }else{
      p->next=tmp;
      tmp->previous=p;
    }
  }
  return tmp;
}

/*clean fusion between two line*/
struct point_s* fusion( struct point_s* p1, struct point_s* p2){
  struct point_s* tmp, *res;
  res=NULL;
  printf("fusiiiiiioooooonnnnnnnn\n");
  
  printf("res x %d  y %d \n ",p2->next->x,p2->next->y);

  printf("res x %d  y %d \n ",p2->x,p2->y);
  select_point(&res,&p1,&p2);

  printf("res x %d  y %d \n \n",p2->x,p2->y);
  /*we works on tmp to save the first point in result as res*/
  if(res==NULL){
    printf("ça devrait pas être null..\n");
  }
  tmp=res;
  printf("res x %d  y %d \n  boucle\n",res->x,res->y);
  while(p1!=NULL && p2!= NULL){
      printf("dedans\n");
      printf("p1 %d %d \np2 %d %d\n",p1->x,p1->y,p2->x,p2->y);
    select_point(&tmp,&p1,&p2);
  }
  
  if(p1==NULL){
      printf("p1 vide\n");
    if(p2->y!=0){
      tmp->next=p2;
      p2->previous=tmp;
    }else if(p2->next !=NULL){
      tmp->next=p2->next;
      p2->next->previous=tmp;
    }
  }else{
      printf("p2 vide\n");
    if(p1->y!=0){
      tmp->next=p1;
      p1->previous=tmp;
    }else if(p1->next !=NULL){
      tmp->next=p1->next;
      p1->next->previous=tmp;
    }
  }
  return res;
}

/*return a clean line*/
struct point_s* resolve(struct point_s*p, int length){
  printf("on resoud %d\n", length);
  if(length==1){
    return p;
  }else if(length==2){
    if(p->x < p->next->x){
      printf("on resoud 2 dans le cas simple\n");
      /*if the entry file is clean( x y z with x<z) we are in this case*/
      return  p;
    }else{      
      printf("on resoud 2 dans le cas dur\n");
      p->previous=p->next;
      p->next->next=p;
      p->next=NULL;
      return p->previous;
    }
  }else{
    /*we cut in 2 sub problems.*/
    struct point_s* tmp1, * tmp2;
    int i,j;
    printf("on resoud et p est %d %d\n", p->x,p->y);
    j=length/2;
    tmp1 = p;
    tmp2 = p;
    for(i=0;i<j;i++){
      tmp2=tmp2->next;
    }
    tmp2->previous->next=NULL;
    tmp2->previous=NULL;
    tmp1=resolve(tmp1,j);
      printf("resolu, ça bloque plus haut\n");
    tmp2=resolve(tmp2, length-j);
      printf("resolu, ça bloque plus haut\n");
    /*fusion of 2 sub problems*/
    return fusion(tmp1, tmp2);
  }
}

void pt_to_buff(char* buff, struct point_s *p,int length){
  sprintf(buff,"");
  for(int i=0; i<length;i++){
    sprintf(buff,"%s %d,%d",buff,p->x,p->y);
    p=p->next;
  }
}

void subdiv(char tmp[3][5],char * buff){
  int tmpcpt,cpt,i;
  i=0;
  cpt=0;
  tmpcpt;
  while(buff[i]!=NULL && buff[i]!='\0'){
    printf("%c // %d %d\n",buff[i],cpt,i);
    if(buff[i]==' ' || buff[i]=='/' || buff[i]==','){
      cpt=0;
      tmpcpt++;
    }else{
      tmp[tmpcpt][cpt]=buff[i];
      cpt++;
    }
  }
}

/*Only read and write in file. Launch the fonction resolve on the polyline*/
int main(int argc, char** argv){
  FILE* ifile;
  FILE* ofile;
  int nb_point;
  if(argc!=2){
    int cpt,nb_point;
    char buff[100];
    struct point_s* first;
    first=NULL;
    cpt=1;
    nb_point=0;
    printf("Veuillez renseigner un seul fichier. mode entier direct\n");
    while(cpt<argc-2){
      nb_point+=2;
      first=add_point(first,1,atoi(argv[cpt++]),atoi(argv[cpt++]));      
      first=add_point(first,1,atoi(argv[cpt++]),0);
    }

    pt_to_buff(buff,first, nb_point);
    printf("%s\n",buff);
    first = resolve(first, nb_point);
  
    //ofile= fopen("out.svg", "r");
    
    pt_to_buff(buff,first, nb_point);
    printf("%s\n",buff);
    
  }
  ifile= fopen(argv[1], "r");
  if(ifile!=NULL){
    char buff[10];
    fgets(buff,10,ifile);
    nb_point= atoi(buff)*2;
    printf("%d points\n", nb_point);
  }
  
  if(ifile!=NULL){
    int cpt;
    struct point_s* first;
    char buff[100];
    first=NULL;
    while (fgets(buff, 100, ifile)){
      char tmp[3][5];
      int int1, int2,int3;
      printf("buff\n%s \n",buff);
      subdiv(tmp,buff);
      //tmp[0]= strtok (buff,delim);
      int1 = atoi(tmp[0]);
      //tmp[1] = strtok (NULL,delim);
      int2 = atoi(tmp[1]);
      //tmp[2] = (NULL,delim);
      int3 = atoi(tmp[2]);
      
      if (cpt<nb_point){
	first=add_point(first,1,int3,0);
	cpt++;
      }
      if (cpt<nb_point){
	first=add_point(first,1,int1,int2);
	cpt++;
      }
    }
    
    pt_to_buff(buff,first, nb_point);
    printf("%s\n",buff);
    first = resolve(first, nb_point);
    fclose(ifile);
  
    //ofile= fopen("out.svg", "r");
    
    pt_to_buff(buff,first, nb_point);
    printf("%s\n",buff);
    //fclose(ofile);
  }
}
