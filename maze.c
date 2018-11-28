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
