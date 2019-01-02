/*
Parallel MPI version
CIS 677 High-Performance Computing
Programming Assignment #4
Message-passing: Distributed Solutions to the k-Queens Problem
Author: Mai Eaksen
*/

#include <stdio.h>
#include<stdbool.h> 
#include <string.h>
#include <unistd.h>
#include <mpi.h>

#define N 8
#define MASTER 0
#define TAG 0
#define MSGSIZE 28000
#define MAX 25
int solutionCount = 0; 
double t1, t2;
/* A utility function to print solution */
void printSolution(int board[N][N]) 
{ 
	solutionCount = solutionCount + 1;
	char output[32000];
	for(int i = 0; i < 32000; i++){
		output[i] = 0;
	}
	int offset = 0;
	
	for(int i = 0; i < N; i++){
		int queen = 0;
		for(int j = 0; j < N; j++){
			if(board[i][j] == 1){
				queen = j;
				//printf(" %d ", board[i][j]); 
				//printf("\n"); 
			}
		}
		offset += sprintf(output + offset, "%d ", queen);
	}
	//printf("%s\n", output);
//    printf("Solution count: %d\n",solutionCount);  
   /*for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N; j++) 
            printf(" %d ", board[i][j]); 
        
		printf("\n"); 
    } 
    printf("\n"); */
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
bool solveNQueenSolutionUtil(int board[N][N], int col) 
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
    bool result = false; 
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
            result = solveNQueenSolutionUtil(board, col + 1) || result; 
  
            /* If placing queen in board[i][col] 
            doesn't lead to a solution, then 
            remove queen from board[i][col] */
            board[i][col] = 0; // BACKTRACK 
        } 
    } 
  
    /* If queen can not be place in any row in 
        this column col then return false */
    return result; 
} 
  
void solveNQueen(int rank) 
{ 
    int board[N][N] ={0}; 
   // memset(board, 0, sizeof(board)); 
	board[rank][0] = 1;	
   
	/*if (validPlace(board, 1 ,rank) == false ) 
		board[rank][1] = 1;*/
	
	if (solveNQueenSolutionUtil(board, 1)==false) 
	{ 
		printf("Solution does not exist\n"); 
		return; 
	} 
  
    return; 
} 
  
// driver program to test above function 

int main(int argc, char* argv[]) 
{ 
	int my_rank;

	MPI_Init(&argc, &argv);
  
	t1 = MPI_Wtime();
	//rank is column the queen is in for the first row	
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	//size is number of processes
	int num_nodes = N;
    MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
	
	//solutions = *solveNQueen;
	if (my_rank < N) 
	{
		solveNQueen(my_rank);
	}
	else{
		solutionCount = 0;
	}
	
	if(my_rank != MASTER)
	{	//master and tag are 0
		MPI_Send(&solutionCount, 1, MPI_INT, MASTER, TAG, MPI_COMM_WORLD);
		
	}
	else
	{
		for (int source = 1; source < num_nodes; source++) {
			int rsolutionCount;
			
			MPI_Recv(&rsolutionCount, 1, MPI_INT, source, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			solutionCount = solutionCount + rsolutionCount;
		}
		printf("Number of solution is %d \n", solutionCount);
	}
	
	t2 = MPI_Wtime();
	MPI_Finalize();
	
	printf("Elapsed time is %f\n", t2-t1);
	return 0;
}
