#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {int x;int y;} POINT;
typedef int BOARD[21][21];
void convert(char *s,int *i);   //把收到的命令转化为相应的switch中的数字
//void evaluate(struct point location);   //这是一个评估函数，用来计算落子的位置

POINT my_point, opp_point;  

void evaluate(BOARD board,int oppx,int oppy) ;
void many( BOARD bef, int check[21][21][8][2]);
void val(BOARD board,int check[21][21][8][2], BOARD a1,BOARD a2 )  ;


int main()
{
	
	char input[10];
	BOARD board;  //opp:1 my:2
	int size, cmd;	
//	POINT my_point, opp_point;  	
	
	while(1){      
		scanf("%s",input);
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

			case 1: 
			    scanf("%d,%d", &opp_point.x, &opp_point.y);
			    board[opp_point.x][opp_point.y] = 1;
				  evaluate(board,opp_point.x,opp_point.y); 
        
            printf("%d,%d\n", my_point.x, my_point.y);
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

void evaluate(BOARD board, int oppx,int oppy)  //计算返回落子的位置
{	
	BOARD bef,aft;//opp:1 my:2
	BOARD a1,a2;
	
	int i,j,k;
	int check[21][21][8][2];
	int x1 = 1, x2 = 1, y1 = 1, y2 = 1;  
	int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};  
  int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; 
	int x,y;
	board[oppx][oppy] = 1;
	for (i = 1;i <= 20;i++)
	   for (j = 1; j<=20;j++)
	   {
	   		bef[i][j] = board[i][j];
	   		aft[i][j] = board[i][j]; 
	   }
	   memset(a1,0,sizeof(a1));
	   memset(a2,0,sizeof(a1));
	   memset(check,0,sizeof(a1));
	   
	    for (i = 0;i < 20; i++)
       for (j = 0;j < 20; j++)
        {
        	if (board[i][j] == 1) for (k = 0;k < 8;k++) if (board[dx[k]][dy[k]] == 0) a1[dx[k]][dy[k]] = 10;
        	if (board[i][j] == 2) for (k = 0;k < 8;k++) if (board[dx[k]][dy[k]] == 0) a2[dx[k]][dy[k]] = 10;	
        }
        
        
	   many(bef,check);
	   val(bef,check,a1,a2);
	    for( i = 0; i < 20; i++ )  
        for( j = 0; j < 20; j++ )  
        {  
            if( a1[x1][y1] < a1[i][j] )   
                {x1 = i; y1 = j;}  // computer 
        }  
        
   for( i = 0; i < 20; i++ )  
        for( j = 0; j < 20; j++ )  
        {  
            if( a2[x2][y2] < a2[i][j] )   
                {x2 = i; y2 = j;}  // my_ai  
        } 
   
              
      if (a1[x1][y1]>a2[x2][y2]) {board[x1][y1] = 2 ;my_point.x = x1; my_point.y = y1; }
        else {board[x2][y2] = 2; my_point.x = x2; my_point.y = y2; }
 
}


void many( BOARD bef, int check[21][21][8][2])
{
	int i, j, k, t, cnt;  
  int tx, ty;  
  int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};  
  int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; 
    for ( i = 0; i < 20; i++ )  // col  
        for ( j = 0; j < 20; j++ )  // row  
            if ( bef[i][j] == 0 )  
            {  
                for ( k = 0; k < 8; k++ )  // direction  
                {  
                    // computer 
                    cnt = 0;  
                    tx = i;  
                    ty = j;  
                    for ( t = 0; t < 5; t++ )  
                    {  
                        tx += dx[k];  
                        ty += dy[k];  
                        if ( tx > 20 || tx < 1 || ty > 20 || ty < 1 )  
                            break;  
                        if( bef[tx][ty] == 1 )  
                            cnt++;  
                        else  
                            break;  
                    }  
                    check[i][j][k][0] = cnt;  
                    // my_ai 
 
                    cnt = 0;  
                    tx = i;  
                    ty = j;  
                    for ( t = 0; t < 5; t++ )  
                    {  
                        tx += dx[k];  
                        ty += dy[k];  
                        if ( tx > 20 || tx < 1 || ty > 20 || ty < 1 )  
                            break;  
                        if( bef[tx][ty] == 2 )  
                            cnt++;  
                        else  
                            break;  
                    }  
                    check[i][j][k][1] = cnt;  
                }  
            }  
}  

   


void val( BOARD board, int check[21][21][8][2], BOARD a1,BOARD a2 )  
{  
    int i, j, k;  
    int win;  
  
    for ( i = 0; i < 20; i++ )  // col  
        for ( j = 0; j < 20; j++ )  // row  
        {  
            if ( board[i][j] == 0 )  
            {  
                win = 0;  
                for ( k = 0; k < 4; k++ )  // direction  
                {  
                    if ( check[i][j][k][0] + check[i][j][k+4][0] >= 4 )  
                        win += 10000;  
                    else if ( check[i][j][k][0] + check[i][j][k+4][0] == 3 )  
                        win += 1000;   
                    else if ( check[i][j][k][0] + check[i][j][k+4][0] == 2 )  
                        win += 100;  
                    else if ( check[i][j][k][0] + check[i][j][k+4][0] == 1 )  
                        win += 10;  
                }  
                a1[i][j] = win;  // computer  
                win = 0;  
                for ( k = 0; k < 4; k++ )  // direction  
                {  
                    if ( check[i][j][k][1] + check[i][j][k+4][1] >= 4 )  
                        win += 10000;  
                    else if ( check[i][j][k][1] + check[i][j][k+4][1] == 3 )  
                        win += 1000;   
                    else if ( check[i][j][k][1] + check[i][j][k+4][1] == 2 )  
                        win += 100;  
                    else if ( check[i][j][k][1] + check[i][j][k+4][1] == 1 )  
                        win += 10;  
                }  
                a2[i][j] = win;  // my_ai  
            }  
        }  
}  
