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

User *create_user(int tx,int ty,int tname){
  User *n;
  n=(User *)malloc(sizeof(User));
  n->x=tx;
  n->y=ty;
  n->dir=rand()%4;
  n->name=tname;
  return n;
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

void user_set(){
  int x,y;
  int cnt=0;
  while(cnt<2){
    x=rand()%20;
    y=rand()%20;
    if(map[y][x]==0){
      if(cnt==0){
	map[y][x]=2;
	user=create_user(x,y,2);
      }else{
	map[y][x]=3;
	bot=create_user(x,y,3);
      }
      cnt++;
    }
  }
}

void map_set(){
  int t=0,i,r1,r2,j;
  
  map_clear();
  for(i=0;i<160;i++){
    r1=rand()%20;
    r2=rand()%20;
    if(map[r1][r2]==0)map[r1][r2]=1;
    else i--;
  }
  while(t<6){
    r1=rand()%20;
    r2=rand()%20;
    if(map[r1][r2]==0){
      map[r1][r2]=rand()%4+6;
      t++;
    }
  }
  user_set();
  Q[0]=create_queue();
  Q[1]=create_queue();
}

void map_print(){
  int i,j;
  Queue *p;

  system("clear");

  for(i=0;i<20;i++){
    for(j=0;j<20;j++){
      switch(map[i][j]){
	case 0:
		printf("  ");
		break;
	case 1:
		printf("□ ");
		break;
	case 2:
		printf("♥ ");
		break;
	case 3:
		printf("♠ ");
		break;
	case 4:
		printf("★ ");
		break;
	case 6:
		printf("ⓙ ");
		break;
	case 7:
		printf("ⓑ ");
		break;
	case 8:
		printf("ⓦ ");
		break;
	case 9:
		printf("ⓢ ");
		break;
	default:
		break;
      }
    }
    if(i==9 || i==10){
      if(i==9){
	switch(user->dir){
	  case 0:
	    printf("\t↑  ");
	    break;
	  case 1:
	    printf("\t→  ");
	    break;
	  case 2:
	    printf("\t↓  ");
	    break;
	  case 3:
	    printf("\t←  ");
	    break;
	}
	printf("User : ");
      }else{
	switch(bot->dir){
	  case 0:
	    printf("\t↑  ");
	    break;
	  case 1:
	    printf("\t→  ");
	    break;
	  case 2:
	    printf("\t↓  ");
	    break;
	  case 3:
	    printf("\t←  ");
	    break;
	}
	printf("Bot : ");
      }p=Q[i-9];
      while(p!=NULL){
	switch(p->data){
	  case 6:
	    printf("ⓙ ┃ ");
	    break;
	  case 7:
	    printf("ⓑ ┃ ");
	    break;
	  case 8:
	    printf("ⓦ ┃ ");
	    break;
	  case 9:
	    printf("ⓢ ┃ ");
	    break;
	  default:
	    break;
	}
	p=p->link;
      }
    }
    printf("\n");
  }
  printf("\nspace:Use Itemp         q:Exit Game\n");
}

int move_check(User *u){
  int result=0;

  switch(u->dir){
    case 0:
      if(u->y-1<0) result=-1; 
      else result=map[u->y-1][u->x];
      break;
    case 1:
      if(u->x+1>19) result=-1;
      else result=map[u->y][u->x+1];
      break;
    case 2:
      if(u->y+1>19) result=-1;
      else result=map[u->y+1][u->x];
      break;
    case 3:
      if(u->x-1<0) result=-1;
      else result=map[u->y][u->x-1];
      break;
    default:
      break;
  }
  return result;
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

void item_wall(User *u){
  int x,y;
  x=u->x;
  y=u->y;
  if(map[y-1][x]==0)map[y-1][x]=1;
  if(map[y+1][x]==0)map[y+1][x]=1;
  if(map[y][x-1]==0)map[y][x-1]=1;
  if(map[y][x+1]==0)map[y][x+1]=1;

  
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

void move(User *u){
  map[u->y][u->x]=0;
  switch(u->dir){
    case 0:
      map[u->y-1][u->x]=u->name;
      u->y--;
      break;
    case 1:
      map[u->y][u->x+1]=u->name;
      u->x++;
      break;
    case 2:
      map[u->y+1][u->x]=u->name;
      u->y++;
      break;
    case 3:
      map[u->y][u->x-1]=u->name;
      u->x--;
      break;
  }
}

int position_check(User *u){
  int i,result=1,tmp;
  User *p;
  p=u;

  for(i=0;i<4;i++){
    p->dir=i;
    tmp=move_check(p);
    if(tmp!=2 && tmp!=3 && tmp!=1 && tmp!=-1) result=0;
  }

  return result;
}



void move_character(User *u){
  int data,tdir;
  
  tdir=u->dir;
  if(position_check(u)){
    u->dir=tdir;
    sleep(1);
  }else{
  u->dir=tdir;
  sleep(1);
  u->dir=rand()%4;
  data=move_check(u);
  while(data==2 || data==3 || data==1 || data==-1){
    u->dir=rand()%4;
    data=move_check(u);
  }
  switch(data){
    case 0:
      move(u);
      break;
    case 4:
      move(u);
      end=0;
      break;
    case 6:
      move(u);
      if(u->name==2)Enqueue(Q[0],6);
      else Enqueue(Q[1],6);
      break;
    case 7:
      move(u);
      if(u->name==2)Enqueue(Q[0],7);
      else Enqueue(Q[1],7);
      break;
    case 8:
      move(u);
      if(u->name==2)Enqueue(Q[0],8);
      else Enqueue(Q[1],8);
      break;
    case 9:
      move(u);
      if(u->name==2)Enqueue(Q[0],9);
      else Enqueue(Q[1],9);
      break;
  }
  }
}



void *item_thread(){
  int i,r,tmp;

  while(end){
    r=rand()%20+10;
    for(i=0;i<r;i++){
      sleep(1);
      if(end==0)break;
    }
    tmp=Dequeue(Q[1]);
    switch(tmp){
      case 6:
	item_jump(bot);
	break;
      case 7:
	item_break(bot);
	break;
      case 8:
	item_wall(bot);
	break;
      case 9:
	item_switch();
	break;
      default:
	break;
    }
  }
  
  pthread_exit(NULL);
}

void *user_thread(){
  while(end){
    move_character(user);
    
    map_print();
  }
  pthread_exit(NULL);
}

void *bot_thread(){
  while(end){
    move_character(bot);
    
  }

  pthread_exit(NULL);
}


void *goal_thread(){
  int i;
  while(end){
    goal_set();
    for(i=0;i<15;i++){
      sleep(1);
      if(end==0)break;
    }
  }
  pthread_exit(NULL);
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
