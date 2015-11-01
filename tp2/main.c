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
    //free(*p);
    *p=NULL;
  }else{
    *p=(*p)->next;
    //free((*p)->previous);
    //(*p)->previous=NULL;
  }
}

void try_save( struct point_s** res, struct point_s** ref, struct point_s** p){
  if((*res)->x < (*p)->x){
    if((*ref)->previous!=NULL &&((*ref)->previous->y < (*p)->y ||(*ref)->y < (*p)->y)){
      save_point(res,p);
    }else{
      consume(p);
    }
  }else if((*res)->x > (*p)->x){
    if((*ref)->x > (*p)->x){
      /*in this case, the line of p can't cut the line and create an interssant intersect before the next point)*/
      consume(p);
    }else{
      if((*p)->next->x != (*ref)->x){
	/*intersect */
	*res= add_point(*res,0, (*ref)->x,(*p)->y);
        consume(ref);
      }
      consume(p);
    }
  }else{
    consume(p);
  }
}

void save_point(struct point_s** res, struct point_s** p){
  struct point_s* tmp;
  tmp= (struct point_s*)malloc(sizeof(struct point_s));
  //printf("---- %d %d \n",(*p)->x , (*p)->y);
  tmp->x= (*p)->x;
  tmp->y= (*p)->y;
  tmp->next=NULL;
  if(*res==NULL){
    *res=tmp;
    tmp->previous=NULL;
  }else{
    (*res)->next=tmp;
    tmp->previous=*res;
    *res=tmp;
    if((*p)->next==NULL){
      *p==NULL;
    }else{
      *p=(*p)->next;
      //(*res)->next->previous=NULL;
      //(*res)->next=NULL;
    }
  }
}

void select_point( struct point_s** res, struct point_s** p1, struct point_s** p2){
  if(*res==NULL){
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
  }else if((*p1)->x == (*p2)->x){
    if((*res)->y==(*p1)->y && (*res)->y== (*p2)->y){
      consume(p1);
      save_point(res,p2);
    }else if((*p1)->y > (*res)->y || (*p2)->y > (*res)->y){
      printf(" %d %d \n",(*p1)->y , (*p2)->y);
      if((*p1)->y > (*p2)->y){
	printf(" *%d %d \n",(*p1)->y , (*p2)->y);
	consume(p2);
	save_point(res,p1);
      }else{
	printf(" %d *%d \n",(*p1)->y , (*p2)->y);

	consume(p1);
	save_point(res,p2);
      }
    }else{
      if((*p1)->y < (*p2)->y){
	consume(p2);
	save_point(res,p1);
      }else{
	consume(p1);
	save_point(res,p2);
      }
    }
  }else if((*p1)->x < (*p2)->x){
    try_save(res,p2,p1);
  }else{
    try_save(&(*res),&(*p1),&(*p2));
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
struct point_s* fusion(struct point_s* p1, struct point_s* p2){
  struct point_s* tmp, *res;
  res=NULL;
  select_point(&res,&p1,&p2);
  /*we works on tmp to save the first point in result as res*/
  tmp=res;
  while(p1!=NULL && p2!= NULL){
    select_point(&tmp,&p1,&p2);
  }
  if(p1==NULL){
    if(p2 !=NULL){
      tmp->next=p2;
      p2->previous=tmp;
    }
  }else{
    if(p1 !=NULL){
      tmp->next=p1;
      p1->previous=tmp;
    }
  }
  return res;
}

/*return a clean line*/
struct point_s* resolve(struct point_s*p, int length){
  if(length==1){
    return p;
  }else if(length==2){
    if(p->x < p->next->x){
      /*if the entry file is clean( x y z with x<z) we are in this case*/
      return  p;
    }else{
      if(p->x >p->next->y){
	p->next=NULL;
	return p;
      }else{
	p->next->previous=NULL;
	return p->next;
      }
    }
  }else{
    /*we cut in 2 sub problems.*/
    struct point_s* tmp1, * tmp2;
    int i,j;
    j=length/2;
    tmp1 = p;
    tmp2 = p;
    for(i=0;i<j;i++){
      tmp2=tmp2->next;
    }
    tmp2->previous->next=NULL;
    tmp2->previous=NULL;
    tmp1=resolve(tmp1,j);
    tmp2=resolve(tmp2, length-j);
    /*fusion of 2 sub problems*/
    return fusion(tmp1, tmp2);
  }
}

void pt_to_buff(char* buff, struct point_s *p,int length){
  sprintf(buff,"");
  while(p!=NULL){
    if(p->previous!= NULL){
      sprintf(buff,"%s %d,%d",buff,p->x,p->previous->y);
    }else if (p->y !=0){
      sprintf(buff,"%s %d,%d",buff,p->x,0);
    }
    sprintf(buff,"%s (%d,%d)",buff,p->x,p->y);
    p=p->next;
  }
}

void subdiv(char tmp[3][5],char * buff){
  int tmpcpt,cpt,i;
  i=0;
  cpt=0;
  tmpcpt=0;
  while(tmpcpt<3 && cpt<5){
    if(buff[i]<48 || buff[i]>57){
      printf("delim found \n");
      tmp[tmpcpt][cpt]='\0';
      cpt=0;
      tmpcpt++;
    }else{
      printf("delim not found \n");
      tmp[tmpcpt][cpt]=buff[i];
      cpt++;
    }
    printf("tmpbuff %s %s %s\n", tmp[0],tmp[1],tmp[2]);
    i++;
  }
}

void write_svg(struct point_s * first, int nb_point){
  char buff[100];
  FILE* ofile;
  ofile= fopen("out.svg", "w+");

  fputs("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"600\" height=\"500\" viewBox=\"0 -150 300 150\"><polyline points=\"", ofile);
  pt_to_buff(buff,first, nb_point);
  fputs(buff, ofile);
  fputs("\" stroke=\"green\" stroke-width=\"0.2\" fill=\"none\" transform=\" scale(10,-10)\" /></svg>", ofile);
  //fclose(ofile);
}

/*Only read and write in file. Launch the fonction resolve on the polyline*/
int main(int argc, char** argv){
  FILE* ifile;
  int nb_point;
  char buff[100];
  struct point_s* first;
  first=NULL;
    
  if(argc!=2){
    int cpt;
    cpt=1;
    nb_point=0;
    printf("Veuillez renseigner un seul fichier. mode entier direct\n");
    while(cpt<argc-2){
      int int1, int2, int3;
      nb_point+=2;
      int1=atoi(argv[cpt++]);
      int2=atoi(argv[cpt++]);
      int3=atoi(argv[cpt++]);
      first=add_point(first,1,int3,0);
      first=add_point(first,1,int1,int2);
    }

    pt_to_buff(buff,first, nb_point);
    printf("%s\n",buff);
    first = resolve(first, nb_point);
  
    //ofile= fopen("out.svg", "r");
    pt_to_buff(buff,first, nb_point);
    printf("\n\n%s\n",buff);
    printf("erire dans out.svg \n");
    write_svg(first, nb_point);
    return 0;
  }else{
    ifile= fopen(argv[1], "r");
    if(ifile!=NULL){
      char buff[10];
      fgets(buff,10,ifile);
      nb_point= atoi(buff)*2;
      printf("%d points\n", nb_point);
    }
    
    if(ifile!=NULL){
      int cpt;
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
	  first=add_point(first,1,int1,int2);
	  
	  cpt++;
	}
	if (cpt<nb_point){
	  first=add_point(first,1,int3,0);
	  cpt++;
	}
      }
      
      pt_to_buff(buff,first, nb_point);
      printf("\n%s\n",buff);
      first = resolve(first, nb_point);
      write_svg(first, nb_point);
      //fclose(ifile);
    }
    
    
  }
  
}
