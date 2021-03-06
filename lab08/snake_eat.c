#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD '>'
#define SNAKE_BODY '-'
#define BLANK_CELL ' '
#define SNAKE_FOOD '+'
#define WALL_SELL '#'

//snake stepping: dy=-1(up),1(down); dx =-1(left),1(right), 0(no move)
void snakeMove(int dy,int dx);
//put a food randomized on a blank cell
void put_food(void);
//out cells of the grid
void output(void);
//outs when gameover
void gameover(void);

char map[12][12]=
	{"############",
	"#---->     #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"############"};
int flag1=1,flag2=1;	
// define vars for snake,notice name of vars in C
int snakeX[SNAKE_MAX_LENGTH]={1,2,3,4,5};       //蛇身和蛇头坐标 
int snakeY[SNAKE_MAX_LENGTH]={1,1,1,1,1};
int snakeLength = 5;

int main(){
	char ch;
	int dy,dx;
	put_food();   //生成食物 
	output();     //生成初始图
	while(1){
			dy=0;
			dx=0;
			scanf("%c",&ch);
			if(ch=='a'||ch=='s'||ch=='w'||ch=='d'){
				switch(ch){
					case'w':
						dy=-1;
						break;
					case's':
						dy=1;
						break;
					case'a':
						dx=-1;
						break;
					case'd':
						dx=1;
						break;
				}
				snakeMove(dy,dx);
				put_food();
				output();
				gameover();
				if(!flag1){
					return 0;
				}
				if(snakeLength==SNAKE_MAX_LENGTH){
					printf("You Win!!\n");
					return 0;
				}
			} 
	} 
	return 0;
}
void snakeMove(int dy,int dx){
	int i;
	if(map[snakeY[snakeLength-1]+dy][snakeX[snakeLength-1]+dx]==SNAKE_FOOD){
		snakeLength++;
		flag2=1;     //重新生成食物 
		snakeX[snakeLength-1]=snakeX[snakeLength-2]+dx;      //改编蛇头位置                    //由于长度加长  故只需要改变蛇头位置即可 
		snakeY[snakeLength-1]=snakeY[snakeLength-2]+dy;
		map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]=SNAKE_BODY;
		map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]=SNAKE_HEAD;
	}
	else{
		map[snakeY[0]][snakeX[0]]=BLANK_CELL;                                   //把蛇尾位置换为空格 
		for(i=0;i<snakeLength-1;i++){
			snakeX[i]=snakeX[i+1];                                              //把整条蛇的坐标往后推一位 
			snakeY[i]=snakeY[i+1];
			map[snakeY[i]][snakeX[i]]=SNAKE_BODY;
		}
		snakeX[snakeLength-1]=snakeX[snakeLength-2]+dx;                         //蛇头位置做出相应变化 
		snakeY[snakeLength-1]=snakeY[snakeLength-2]+dy;
		map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]=SNAKE_HEAD;	
}
void put_food(void){
	int y,x;
	if(flag2){                                          //若flag2为true  则需要生成一个食物 
		y=rand()%10+1;
		x=rand()%19+1;                                  //保证食物的坐标处在方框内 
		while(map[y][x]!=BLANK_CELL){                   //若当前位置不为空  则重新生成随机数直至位置为空 
			y=rand()%10+1;
			x=rand()%19+1;
		}
		map[y][x]=SNAKE_FOOD;                           //在当前位置放食物 
		flag2=0;	                                    //flag2为0  暂时不用放食物了 
	}
}
void output(void){
	int i;
	for(i=0;i<12;i++){
		printf("%s\n",map[i]);                      //把表的每行打印出来 
	}
}

void gameover(void){
	int i;
	for(i=0;i<snakeLength-1;i++){
		if((snakeX[i]==snakeX[snakeLength-1]&&snakeY[i]==snakeY[snakeLength-1])||snakeX[snakeLength-1]==0||snakeX[snakeLength-1]==21||snakeY[snakeLength-1]==0||snakeY[snakeLength-1]==11){
			printf("Game Over!!\n");                      //判断蛇头是否碰撞到自身或者碰到墙壁   是则Game Over 
			flag1=0;                                      //flag1为0表示不用继续游戏了 
			break;
		}
	}
}
}

