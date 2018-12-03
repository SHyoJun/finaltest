#ifndef __MAZE_H__
#define __MAZE_H__

int getch();
void map_clear();
void goal_set();
void map_set();
void map_print();
void item_break(User *);
void item_wall(User *);
void item_switch();
Queue *create_queue();
void Enqueue(Queue *,int );
void sub_Enqueue(Queue *,int );
int Dequeue(Queue *);
void *item_thread(); 
void *goal_thread();
#endif
