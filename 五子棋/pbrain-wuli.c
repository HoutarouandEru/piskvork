#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {int x;int y;} POINT;
typedef int BOARD[21][21];
void convert(char *s,int *i);   

POINT my_point, opp_point;  
BOARD board;

void evaluate() ;
void many( int check[20][20][8][2][2]);
void val(int check[20][20][8][2][2], BOARD a1,BOARD a2 )  ;


int main()
{
//	freopen("out.out","w",stdout);
	char input[10];
//	BOARD board;  //opp:1 my:2
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
				  evaluate(); 
    printf("%d,%d\n", my_point.x, my_point.y);
	
    
        	    fflush(stdout);
            	break;

			case 2: 
           		 printf("10,10\n");
           	  	 fflush(stdout);
            	break;

			case 3: 
    	        printf("%d,%d\n", my_point.x, my_point.y);
        	    fflush(stdout);
            	break;

			case 4: 
			    printf("Restart-OK\n");
			    fflush(stdout);
		    	break;  

			case 5: 
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
void convert(char *s,int *i)  
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

void evaluate()  
{	
	BOARD bef,aft;//opp:1 my:2
	BOARD a1,a2;	
	int i,j,k;
	int check[20][20][8][2][2];
	int x1,x2,y1,y2;  
	int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};  
  int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; 
	int x,y;
/*	
	for (i = 0;i <= 19;i++)
	   for (j = 0; j<=19;j++)
	   {
	   		bef[i][j] = board[i][j];
	   		aft[i][j] = board[i][j]; 
	   }
*/	   
	   memset(a1,0,sizeof(a1));
	   memset(a2,0,sizeof(a2));
//	   memset(check,0,sizeof(check));
	   
	    for (i = 1;i < 19; i++)
       for (j = 1;j < 19; j++)
        {
        	if (board[i][j] == 1) for (k = 0;k < 8;k++) if (board[dx[k]][dy[k]] == 0) a1[dx[k]][dy[k]] = 100;
        	if (board[i][j] == 2) for (k = 0;k < 8;k++) if (board[dx[k]][dy[k]] == 0) a2[dx[k]][dy[k]] = 100;	
        }
        
     x1 = 0; x2 = 0; y1 = 0; y2 = 0;   
	   many(check);
	   val(check,a1,a2);
	    for( i = 0; i < 20; i++ )  
        for( j = 0; j < 20; j++ )  
        {  
            if( a1[x1][y1] < a1[i][j] && board[i][j] == 0)   
                {x1 = i; y1 = j;}  // computer 
        }  
        
   for( i = 0; i < 20; i++ )  
        for( j = 0; j < 20; j++ )  
        {  
            if( a2[x2][y2] < a2[i][j] && board[i][j] == 0)   
                {x2 = i; y2 = j;}  // my_ai  
        } 
   
              
      if (a1[x1][y1]>a2[x2][y2]) {board[x1][y1] = 2 ;my_point.x = x1; my_point.y = y1; }
        else {board[x2][y2] = 2; my_point.x = x2; my_point.y = y2; }
        
   /*    
   		 printf("********************board\n");  	
           		for (i=0;i<20;i++) {for (j=0;j<20;j++) printf("%d  ",board[i][j]);	printf("\n");}         
   printf("********************a1\n");  
       for (i=0;i<20;i++) {for (j=0;j<20;j++) printf("%d   ",a1[i][j]);	printf("\n");}     	
       printf("********************a2\n");  
       for (i=0;i<20;i++) {for (j=0;j<20;j++) printf("%d   ",a2[i][j]);	printf("\n");}    
       printf("********************\n");
    */   
      
}


void many(  int check[20][20][8][2][2])
{
	int i, j, k, t, tt;  
  int tx, ty;  
  int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};  
  int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; 
    for ( i = 0; i < 20; i++ )  // col  
        for ( j = 0; j < 20; j++ )  // row  
            if ( board[i][j] == 0 )  
            {  
                for ( k = 0; k < 8; k++ )  // direction  
                {  
                    // computer 
                    tt = 0;  
                    tx = i;  
                    ty = j;  
                    for ( t = 0; t < 5; t++ )  
                    {  
                        tx += dx[k];  
                        ty += dy[k];  
                        if ( tx >= 20 || tx < 1 || ty >= 20 || ty < 1 )  
                            break;  
                        if( board[tx][ty] == 1 )  
                            tt++;  
                        else  if (board[tx][ty] == 0)  break;  
                        	    else {check[tx][ty][k][0][1] == 1 ;break;}
                    }  
                    check[i][j][k][0][0] = tt;  
                    // my_ai  
                    tt = 0;  
                    tx = i;  
                    ty = j;  
                    for ( t = 0; t < 5; t++ )  
                    {  
                        tx += dx[k];  
                        ty += dy[k];  
                        if ( tx >= 20 || tx < 1 || ty >= 20 || ty < 1 )  
                            break;  
                        if( board[tx][ty] == 2 )  
                            tt++;  
                        else if (board[tx][ty] == 0)  break;  
                        	   else {check[tx][ty][k][1][1] == 1 ;break;} 
                            break;  
                    }  
                    check[i][j][k][1][0] = tt;  
                }  
            }  
}  

   


void val(  int check[20][20][8][2][2], BOARD a1,BOARD a2 )  
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
                    if ( check[i][j][k][0][0] + check[i][j][k+4][0][0] == 4 )   win += 1000;//c5
                    if ( check[i][j][k][0][0] + check[i][j][k+4][0][0] == 3 )   //4
                    	{
                    	if (check[i][j][k][0][1] + check[i][j][k][0][1] ==0)   win +=900;//h4
                    	if (check[i][j][k][0][1] + check[i][j][k][0][1] ==1) //s4
                    		{
                    		if (check[i][j][(k + 2) % 4][0][0] + check[i][j][(k + 6) % 4][0][0] ==3) win += 900;//s4s4
                    		if (check[i][j][(k + 2) % 4][0][0] + check[i][j][(k + 6) % 4][0][0] ==2 && check[i][j][(k + 2) % 4][0][1] + check[i][j][(k + 6) % 4][0][1] == 0) win +=900;//s4h3
                    		if (check[i][j][(k + 2) % 4][0][0] + check[i][j][(k + 6) % 4][0][0] <=1) win += 600;//s4		
                    	  }	
                      }
                    if ( check[i][j][k][0][0] + check[i][j][k+4][0][0] == 2 ) //3
                    	{
                    		if (check[i][j][k][0][1] + check[i][j][k+4][0][1] == 0)//h3
                    			{
                    				if (check[i][j][(k + 2) % 4][0][0] + check[i][j][(k + 6) % 4][0][0] ==2 && check[i][j][(k + 2) % 4][0][1] + check[i][j][(k + 6) % 4][0][1] ==0) win += 800;//h3h3
                    				if (check[i][j][(k + 2) % 4][0][0] + check[i][j][(k + 6) % 4][0][0] ==2 && check[i][j][(k + 2) % 4][0][1] + check[i][j][(k + 6) % 4][0][1] ==1) win += 700;//h3s3	
                    			  if (check[i][j][(k + 2) % 4][0][0] + check[i][j][(k + 6) % 4][0][0] <=1) win += 500;//h3
                    			} 
                    		if (check[i][j][k][0][1] + check[i][j][k+4][0][1] == 1 && check[i][j][(k + 2) % 4][0][0] + check[i][j][(k + 6) % 4][0][0] <= 1) win +=300;	//s3
                    	} 
                    if (check[i][j][k][0][0] + check[i][j][k+4][0][0] == 1 && check[i][j][(k + 2) % 4][0][0] + check[i][j][(k + 6) % 4][0][0] == 1 && check[i][j][(k + 2) % 4][0][1] + check[i][j][(k + 6) % 4][0][1] == 0 && check[i][j][k][0][1] + check[i][j][k+4][0][1] == 0)
                    	win += 400;//h2h2
                   
                }  
                a1[i][j] = win;  // computer  
                
                win = 0;  
                for ( k = 0; k < 4; k++ )  // direction  
                {  
                    if ( check[i][j][k][1][0] + check[i][j][k+4][1][0] == 4 )   win += 1000;//c5
                    if ( check[i][j][k][1][0] + check[i][j][k+4][1][0] == 3 )   //4
                    	{
                    	if (check[i][j][k][1][1] + check[i][j][k][1][1] ==0)   win +=900;//h4
                    	if (check[i][j][k][1][1] + check[i][j][k][1][1] ==1) //s4
                    		{
                    		if (check[i][j][(k + 2) % 4][1][0] + check[i][j][(k + 6) % 4][1][0] ==3) win += 900;//s4s4
                    		if (check[i][j][(k + 2) % 4][1][0] + check[i][j][(k + 6) % 4][1][0] ==2 && check[i][j][(k + 2) % 4][1][1] + check[i][j][(k + 6) % 4][1][1] == 0) win +=900;//s4h3
                    		if (check[i][j][(k + 2) % 4][1][0] + check[i][j][(k + 6) % 4][1][0] <=1) win += 600;//s4		
                    	  }	
                      }
                    if ( check[i][j][k][1][0] + check[i][j][k+4][1][0] == 2 ) //3
                    	{
                    		if (check[i][j][k][1][1] + check[i][j][k+4][1][1] == 0)//h3
                    			{
                    				if (check[i][j][(k + 2) % 4][1][0] + check[i][j][(k + 6) % 4][1][0] ==2 && check[i][j][(k + 2) % 4][1][1] + check[i][j][(k + 6) % 4][1][1] ==0) win += 800;//h3h3
                    				if (check[i][j][(k + 2) % 4][1][0] + check[i][j][(k + 6) % 4][1][0] ==2 && check[i][j][(k + 2) % 4][1][1] + check[i][j][(k + 6) % 4][1][1] ==1) win += 700;//h3s3	
                    			  if (check[i][j][(k + 2) % 4][1][0] + check[i][j][(k + 6) % 4][1][0] <=1) win += 500;//h3
                    			} 
                    		if (check[i][j][k][1][1] + check[i][j][k+4][1][1] == 1 && check[i][j][(k + 2) % 4][1][0] + check[i][j][(k + 6) % 4][1][0] <= 1) win +=300;	//s3
                    	} 
                    if (check[i][j][k][1][0] + check[i][j][k+4][1][0] == 1 && check[i][j][(k + 2) % 4][1][0] + check[i][j][(k + 6) % 4][1][0] == 1 && check[i][j][(k + 2) % 4][1][1] + check[i][j][(k + 6) % 4][1][1] == 0 && check[i][j][k][1][1] + check[i][j][k+4][1][1] == 0)
                    	win += 400;//h2h2
                }  
                a2[i][j] = win;  // my_ai  
            }  
        }  
}  
