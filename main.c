#include "maze.h"

int map[20][20];
int end=1;
User *bot,*user;
Queue *Q[0];

int main(){
  int i,res,tmp;
  pthread_t thread[4];

  srand((int)time(NULL));
  system("setterm -cursor off");

  map_set();
  //map_print();

  res=pthread_create(&thread[0],NULL,user_thread,NULL);
  if(res!=0) printf("User thread create failed!!\n");
  res=pthread_create(&thread[1],NULL,bot_thread,NULL);
  if(res!=0) printf("Bot thread create failed!!\n");
  res=pthread_create(&thread[2],NULL,goal_thread,NULL);
  if(res!=0) printf("Goal thread create failed!!\n");
  res=pthread_create(&thread[3],NULL,item_thread,NULL);
  if(res!=0) printf("item thread create failed!!\n");

Enqueue(Q[0],6);

  while(end){
    tmp=getch();
    if(tmp==32){
      tmp=Dequeue(Q[0]);
      switch(tmp){
	case 6:
	  item_jump(user);
	  break;
	case 7:
	  item_break(user);
	  break;
	case 8:
	  item_wall(user);
	  break;
	case 9:
	  item_switch();
	  break;
	default:
	  break;
      }
    }else if(tmp==113)end=0;
  }
  //쓰레드와 동시에 메인에서 동작할부분
  for(i=0;i<4;i++){
    res=pthread_join(thread[i],NULL);
    if(res!=0) printf("%d thread join failed!!\n",i+1);
  }

  system("setterm -cursor on");
  return 0;
}

