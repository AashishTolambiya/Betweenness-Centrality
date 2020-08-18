#include<stdio.h> 
#include<stdlib.h>
#include<ncurses.h>
#include "3_header.h"
#include<time.h>

int main() 
{ 
int max_component_no, i, option;
float prob_factor, *bfs_bc, *floyd_bc;
struct Graph* graph;
char filename[100];
clock_t t; 
    
printf("\nProgram to calculate Betweeness Centrality !");
again1:
printf("\nChoose one option :\n1. Load Graph from a text file\n2. Generate random graph (Erdos-Renyl Model)\n");
scanf("%d", &option);	
	
	if(option != 1 && option !=2)
	{
	printf("\nInvalid option\n");
	exit(0);
	}
	
	if(option == 1)
	{
	FILE *fptr;

	printf("\nEnter the filename to open : "); 
	scanf("%s", filename);

	fptr = fopen(filename, "r");
		if(fptr == NULL) 
		{ 
		printf("\nCannot open file!\n"); 
		exit(0);
		}

	graph = Upload_graph(filename, fptr);
		if(graph == NULL)
		{
		exit(0);
		}
	}
	
	else
	{
	printf("\nEnter details of Erdos-Renyl Model for random graph generation!!");
    
		do{
		printf("\nNumber of nodes (n>0)   : ");
		scanf("%d",&no_of_nodes);
		}while(no_of_nodes<=0);
	
		do{
		printf("\nProbabilty Factor (0<p<=1) : ");
		scanf("%f",&prob_factor);
		}while(prob_factor<=0 || prob_factor > 1);

	graph = ErdosRenyi(no_of_nodes, prob_factor);
	}
	
struct Conn_Comp* cc = (struct Conn_Comp*) malloc(sizeof(struct Conn_Comp));
max_component_no = find_connected_comp(graph, no_of_nodes, cc);

printf("\nEnter 1 to print Graph adjacency list, else enter 2 to continue with further processing : ");
scanf("%d", &option);

	if(option != 1 && option !=2)
	{
	printf("\nInvalid option\n");
	exit(0);
	}

	if(option == 1)
	{
	printGraph(graph);
	}
	
printf("\nCalculating Betweenness Centrality using BFS..\n");
t = clock(); 
bfs_bc = Execute_BFS(graph, no_of_nodes, cc, max_component_no);
t = clock() - t; 
double time_taken_bfs = ((double)t)/CLOCKS_PER_SEC;
char file1[] = "BFS_Execution_Time.txt";
Write_Execution_Time(file1, no_of_nodes, time_taken_bfs);

arr = (int** )malloc((no_of_nodes+1) * sizeof(int *));
	for (i=1; i<=no_of_nodes; i++)
	{
	arr[i] = (int *)malloc((no_of_nodes+1) * sizeof(int));
	}
arr = Convert_AdjList_AdjMat(graph, arr);

printf("\nCalculating Betweenness Centrality using Floyd Warshall..\n");
t = clock(); 
floyd_bc = Execute_Flyod_Warshall(arr, no_of_nodes);
t = clock() - t; 
double time_taken_floyd = ((double)t)/CLOCKS_PER_SEC;
char file2[] = "Floyd_Execution_Time.txt";
Write_Execution_Time(file2, no_of_nodes, time_taken_floyd);

	for(i=1; i<=no_of_nodes; i++)
	{
		if(cc->arr_com[i].component == max_component_no)
		{
		printf("\nBFS_BC[%d] = %f\tFloyd_BC[%d] = %f", i, bfs_bc[i], i, floyd_bc[i]);
		}
	}

printf("\nBFS_Execution_Time : %lf\nFloyd_Execution_Time : %lf", time_taken_bfs, time_taken_floyd);
printf("\n");  
return 0; 
}
