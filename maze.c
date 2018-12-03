#include "maze.h"


int getch(){
  int ch;
  struct termios buf;
  struct termios save;
  tcgetattr(0,&save);
  buf=save;
  buf.c_lflag &= ~(ICANON | ECHO);
  buf.c_cc[VMIN]=1;
  buf.c_cc[VTIME]=0;
  tcsetattr(0,TCSAFLUSH,&buf);
  ch=getchar();
  tcsetattr(0,TCSAFLUSH,&save);
  return ch;
}

void map_clear(){
  int i,j;

  for(i=0;i<20;i++){
    for(j=0;j<20;j++){
      map[i][j]=0;
    }
  }
}

void goal_set(){
  int x,y;

  for(x=0;x<20;x++){
    for(y=0;y<20;y++){
      if(map[y][x]==4)map[y][x]=0;
    }
  }

  while(1){
    x=rand()%20;
    y=rand()%20;
    if(map[y][x]==0){
      map[y][x]=4;
      break;
    }
  }
}

void item_break(User *u){
  int x,y;
  x=u->x;
  y=u->y;
  if(map[y-1][x]==1)map[y-1][x]=0;
  if(map[y+1][x]==1)map[y+1][x]=0;
  if(map[y][x-1]==1)map[y][x-1]=0;
  if(map[y][x+1]==1)map[y][x+1]=0;

  
  map_print();
}

void item_switch(){
  int temp;
  
  temp=user->x;
  user->x=bot->x;
  bot->x=temp;
  temp=user->y;
  user->y=bot->y;
  bot->y=temp;
  map[user->y][user->x]=2;
  map[bot->y][bot->x]=3;

  
  map_print();
}
Queue *create_queue(){
  Queue *n;

  n=(Queue *)malloc(sizeof(Queue));
  n->data=0;
  n->link=NULL;
  return n;
}

void Enqueue(Queue *q,int num){
  Queue *n,*p;
  p=q;
  n=create_queue();
  n->data=num;

  n->link=p->link;
  p->link=n;
}

void sub_Enqueue(Queue *q,int num){
  Queue *n,*p;
  p=q;
  n=create_queue();
  n->data=num;
  while(p->link!=NULL){
    p=p->link;
  }
  p->link=n;
}

int Dequeue(Queue *q){
  Queue *p,*t;
  int tmp;
  p=q;
  while(p->link!=NULL){
    t=p;
    p=p->link;
  }
  if(p->data==0){
    return 0;
  }else{
    tmp=p->data;
    free(p);
    t->link=NULL;
    return tmp;
  }
}
