#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

enum dim_e {width,height};

typedef enum dim_e dimension;

typedef int (func_t)(int,int,int,int);

static func_t* recursive;
static int ****tab, state,game_width,game_height,x_dead, y_dead,next_cut_in,user_number,stop;
static char user_number_buff[10];
static char *header[10];
static int canfree = 1;

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; }) 


/*______rules______*/

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
  return tab[m-1][n-1][i][j];
}


int solve_and_launch(int m, int n, int i, int j){
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
  x_dead--;
  y_dead--;
  position_dyna(m,n,x_dead, y_dead);
  game();
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

/*____interface____*/
void add_number(int u){
  user_number=user_number*10+(u-48);
  sprintf(user_number_buff, "%d", user_number);
}

void inc_state(){
  state= (state+1)%3;
}

void printconfig(){
  char *line;
  int i,j;
  line=malloc(sizeof(char)*game_width);
  for(j=0;j<game_height;j++){
    for(i=0;i<game_width;i++){
      line[i]='O';
    }
    if(j==y_dead){
      line[x_dead]='X';
    }
    mvprintw(4+j, 3, line);
  }
  
}

void cpu_play(){
  int res,index;
  index=0;
  
}

void change_configuration(){
  if( next_cut_in==width){
    if (user_number< x_dead){
      x_dead = x_dead-user_number;
    }
    game_width= user_number;
  } else{
    if(user_number< y_dead){
      y_dead = y_dead-user_number;
    }
    game_height= user_number;
  }
  user_number=0;
  sprintf(user_number_buff, "%d", user_number);
}

void step(){
  if(state==0){
    cpu_play();
    inc_state();
  }else if(state==2) {
    change_configuration();
    inc_state();
  }else if(state==9){
    stop=0;
  }else if(state==8){
    state=0;
  }
}

void on_touch(){
  int c;
  c = getch();
  if(47<c && c<58){
    //number pressed
    if(state==2){
      add_number(c);
    }
  }else if(c==10){
    //enter pressed
    step();
  }else if(c==119){
    //w
    if(state==1){
      next_cut_in=width;
      inc_state();
    }
  }else if(c==104){
    //h
    if(state==1){
      next_cut_in=height;
      inc_state();
    }
  }else{
    mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
    refresh();  
  }
}

int game() {
  WINDOW *boite;

  initscr();
  header[8]="Ready to start";
  header[0]="CPU turn, push enter";
  header[1]="Your turn, cut in height(h) or width(w) ?";
  header[2]="Your turn, cut  at ? (writte a number and push enter)";
  boite= subwin(stdscr, 30, 90, 2,1);
  state=8;
  user_number=0;
  sprintf(user_number_buff, "%d", user_number);
  stop=1;
  while(stop) {
    clear();// Efface la fenêtre (donc l'ancien message)
    
    box(boite, ACS_VLINE, ACS_HLINE);
    mvprintw(0,0,header[state]);
    if(state==2){
      mvprintw(1,0,user_number_buff);
    }
    printconfig();
    refresh();
    on_touch();
    
    /*if(getch() != 410)
      break;*/
  }

  endwin();

  free(boite);

  return 0;
}

int main (int argc, char *argv[]){

    int res;
    game_width=atoi(argv[1]);
    game_height= atoi(argv[2]);
    x_dead=atoi(argv[3]);
    y_dead=atoi(argv[4]);
    recursive=position_dyna;
    solve_and_launch(game_width, game_height, x_dead,y_dead);
    return 0;
}
