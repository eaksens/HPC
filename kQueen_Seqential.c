#include <stdio.h>
#include<stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#define N 8

int solutionCount = 0; 
struct timeval t0, t1;

/* A utility function to print solution */
void printSolution(int board[N][N]) 
{ 
	solutionCount = solutionCount + 1;  
    printf("Solution count: %d\n",solutionCount);  
    for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N; j++) 
            printf(" %d ", board[i][j]); 
        printf("\n"); 
    } 
    printf("\n"); 
} 
  

bool validPlace(int board[N][N], int row, int col) 
{ 
    int i, j; 
  
    /* Check this row on left side */
    for (i = 0; i < col; i++) 
        if (board[row][i]) 
            return false; 
  
    /* Check upper diagonal on left side */
    for (i=row, j=col; i>=0 && j>=0; i--, j--) 
        if (board[i][j]) 
            return false; 
  
    /* Check lower diagonal on left side */
    for (i=row, j=col; j>=0 && i<N; i++, j--) 
        if (board[i][j]) 
            return false; 
  
    return true; 
} 
  
/* A recursive utility function to solve N 
Queen problem */
bool solveNQUtil(int board[N][N], int col) 
{ 
    /* base case: If all queens are placed 
    then return true */
    if (col == N) 
    { 
		printSolution(board); 
		return true; 
    } 
    /* Consider this column and try placing 
    this queen in all rows one by one */
    bool res = false; 
    for (int i = 0; i < N; i++) 
    { 
        /* Check if queen can be placed on 
        board[i][col] */
        if ( validPlace(board, i, col) ) 
        { 
            /* Place this queen in board[i][col] */
            board[i][col] = 1; 
  
            // Make result true if any placement 
            // is possible 
            res = solveNQUtil(board, col + 1) || res; 
  
           
            board[i][col] = 0; // BACKTRACK 
        } 
    } 
  
    /* If queen can not be place in any row in 
        this column col then return false */
    return res; 
} 
  

void solveNQ() 
{ 
    int board[N][N]={0}; 
   // memset(board, 0, sizeof(board)); 
  
    if (solveNQUtil(board, 0) == false) 
    { 
        printf("Solution does not exist"); 
        return ; 
    } 
  
    return ; 
} 
  
// driver program to test above function 
int main() 
{ 
	//long t0, t1;
	gettimeofday (&t0, NULL);
    solveNQ(); 
	gettimeofday (&t1, NULL);
	
	long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	//print out the time
	printf("Time used to calculate is %ld microsecond \n", elapsed);
    return 0; 
}
