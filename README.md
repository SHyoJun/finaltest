# finaltest

maze.c 로 입력받아 미로 도착지점 찾기 프로그래밍을 수행

1.미로의 크기는 최대 20 * 20 을 넘어서지 않는다

2.봇과 사용자 간의 1:1 게임이다

3.봇과 사용자 모두 아이템 획득 및 사용 가능하다.

4.아이템은 큐로 저장되고, 먼저 획득한 순서대로 사용 가능하다.

5.아이템은 재생되지 않고 맵 초기화 될때 함께 랜덤으로 생성된다.

6.도착지점은 일정시간이 지나면 쓰레드에 의해 랜덤위치로 이동 된다.

7.봇, 사용자 모두 랜덤으로 움직인다.(방향 설정 불가)


# 아이템 구성
ⓙ 뛰어넘기 : 벽이 있을 경우 이동방향에 따라 사용하면 벽을 뛰어넘을 수 있다.

거리 제한이 없으며 점프 최초 도착지점이 맵 바깥이라면 점프하지 않고 아이템이 사라지고 제자리에 남는다.

ⓑ 벽 제거 : 사용자의 상하좌우 생성되어 있는 벽을 부순다. 벽의 유무와 상관없이 상하좌우 한칸씩 부순다.

ⓦ 벽 쌓기 : 사용자의 상하좌우에 벽을 하나씩 생성시킨다. 아래 설명할 위치바꾸기와 같이 쓰면 효과적이다.

ⓢ 위치반전 : 아이템을 사용하면 봇과 위치를 바꾼다.

# 코딩 Overview
# 이동가능 구역 확인 함수
int move_check(int temp){

  int result=0;
  
  if(temp==1){
  
    switch(user.dir){
    
      case 0:
      
       if(map[user.y-1][user.x]!=1 && map[user.y-1][user.x]!=3)result=1; // 북쪽 검사
       
       break;
       
      case 1:
      
       if(map[user.y][user.x+1]!=1 && map[user.y][user.x+1]!=3)result=1; // 동쪽 검사
       
       break;
       
      case 2:
      
       if(map[user.y+1][user.x]!=1 && map[user.y+1][user.x]!=3)result=1; // 남쪽 검사
       
       break;
       
      case 3:
      
       if(map[user.y][user.x-1]!=1 && map[user.y][user.x-1]!=3)result=1; // 서쪽 검사
       
       break;
       
      default:
      
       break;
       
    }
    
  }
  
  else{
  
    switch(bot.dir){
    
      case 0:
      
       if(map[bot.y-1][bot.x]!=1 && map[bot.y-1][bot.x]!=2)result=1; // 북쪽 검사
       
       break;
       
     case 1:
     
  if(map[bot.y][bot.x+1]!=1 && map[bot.y][bot.x+1]!=2)result=1; // 동쪽 검사
  
       break;
       
     case 2:
     
     if(map[bot.y+1][bot.x]!=1 && map[bot.y+1][bot.x]!=2)result=1; // 남쪽 검사
     
       break;
       
	 case 3:
	 
       if(map[bot.y][bot.x-1]!=1 && map[bot.y][bot.x-1]!=2)result=1; // 서쪽 검사
       
       break;
       
  default:
  
      break;
      
	 }
	 
 }
 
 return result;

}



# Develop Overview

ProjectName : (Queue+Thread) 미로찾기

Corder : 박정민 / 송효준 / 이요나

Organiz. : 조선대학교

Major : 컴퓨터 공학과

DateTime : 2018.12

Develop OS : ubuntu

PorgramLang : C

TextEditor : VIM - Vi IMproved 8.1

Encording : UTF-8 (Linux Basic)

Compiler : GCC 6.5

# 컴파일

리눅스 환경에서 세 파일을 모두 같은 폴더에 위치시킨

「gcc -o main main.c -lpthread」

라는 명령어로 pthread 라이브러리를 추가시켜 주어야 한다.


# Description
int getch() : 키보드 입력하면 엔터키없이 바로 인식하는 함수

create_user() : User구조체 생성하고 포인터형으로 리턴

int move_check() : 첫 매개변수가 user포인터.다음위치값 리턴(배열범위초과한경우 -1리턴)

int position_check() : 상하좌우가 벽or상대캐릭터or범위바깥 으로막히면 1리턴 아니면0리턴

move_character() : 이동함수 전체사용(move들어간 함수들 이용해서 이동작업처리).첫 매개변수가 user포인터

create_queue() : Queue구조체 생성하고 포인터형으로리턴

Enqueue() : 아이템먹으면 큐에삽입.2번째 매개변수가 아이템(위에 번호)


