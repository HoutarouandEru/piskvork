#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//#include "windows.h"
#define ZERO_LEVEL 100
#define FIRST_LEVEL 90
#define SECOND_LEVEL 80
#define THIRD_LEVEL 70
#define FOURTH_LEVEL 60
#define FIFTH_LEVEL 50
#define SIXTH_LEVEL 40
#define SEVENTH_LEVEL 30
#define EIGHTH_LEVEL 20
#define NINTH_LEVEL 10
#define TENTH_LEVEL 0

typedef struct {int x;int y;} POINT;
typedef int BOARD[21][21];
void convert(char *s,int *i);   //把收到的命令转化为相应的switch中的数字
//void evaluate(struct point location);   //这是一个评估函数，用来计算落子的位置
int main()
{
	
	char input[10];
	BOARD board;  //定义一个数组，用来记录棋盘上已落子的位置；并记opp的落子为-1，my的落子为0；
	int size, cmd;
	POINT my_point, opp_point;      
	
	while(1){       //收服务器发来的信号并给出相应的反馈
		scanf("%s", input);
    	convert(input,&cmd);
		switch (cmd){
			case 0: // START
				scanf("%d", &size);
				if (size == 20)
					printf("OK\n");
				else
					printf("ERROR message\n");
				fflush(stdout);
				break;

			case 1: //TURN  计算落子的位置
			    scanf("%d,%d", &opp_point.x, &opp_point.y);
			    /*这里放AI算法*///evaluate(opp_point);
        		printf("%d,%d\n", rand()%20, rand()%20);//每次获取一个随机数并输出。
           // printf("%d,%d\n", my_point.x, my_point.y);
        	    fflush(stdout);
            	break;

			case 2: // BEGIN  先后手的判定
           		 printf("10,10\n");
           	  	 fflush(stdout);
            	break;

			case 3: // BOARD 边界条件 
    	        printf("%d,%d\n", my_point.x, my_point.y);
        	    fflush(stdout);
            	break;

			case 4: // 重新开始一句
			    printf("Restart-OK\n");
			    fflush(stdout);
		    	break;  

			case 5: // 命令为结束
			    printf("none\n");
			    return -1;
		    	fflush(stdout);
		    	break;

			default:
			    break;
		}
	}
    return 0;
}
void convert(char *s,int *i)  //把收到的命令转化为相应的switch中的数字
{
	switch(*s){
	    case 'S':
	        *i = 0;
	        break;
	    case 'T':
	        *i = 1;
	        break;
	    case 'R':
	        *i = 4;
	        break;
	    case 'E':
	        *i = 5;
	        break;
	    case 'B':{
	        switch(*(s+1))
	           case 'E':
	               *i = 2;
	               break;
	           case 'O':
	               *i = 3;
	               break;
	    }
	        break;
	    default:
	        *i = 6;
	        break;
	}
}	
/*
void evaluate(struct point location)  //计算返回落子的位置
{
	int board[21][21];
	board[opp_point.x][opp_point.y] = -1;
}*/
