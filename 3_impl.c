#include<stdio.h> 
#include<stdlib.h>
#include<ncurses.h>
#include<limits.h>
#include<string.h>
#include "3_header.h"
#include<time.h>
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"
#define GRN   "\x1B[32m"

struct AdjListNode* newAdjListNode(int dest) 
{ 
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	newNode->next = NULL; 
	return newNode; 
} 
  
struct Graph* createGraph(int V) 
{ 
int i;	
struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
graph->V = V;
  
graph->array = (struct AdjList*) malloc((V+1) * sizeof(struct AdjList)); 
printf("\nAdjacency list created");
	  
	
	for(i=1; i<=V; i++)
	{ 
	graph->array[i].head = NULL;
	}
printf("\nAdjacency list initialised");

return graph; 
} 

void addEdge(struct Graph* graph, int src, int dest) 
{ 
	struct AdjListNode* newNode = newAdjListNode(dest); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode;
  
	newNode = newAdjListNode(src); 
	newNode->next = graph->array[dest].head; 
	graph->array[dest].head = newNode; 
} 

void printGraph(struct Graph* graph) 
{ 
	int i;
	for (i=1; i<=graph->V; i++) 
	{ 
	struct AdjListNode* pCrawl = graph->array[i].head; 
	printf("\nAdjacency list of vertex %d\n head ", i); 
		while (pCrawl) 
		{ 
		printf("-> %d", pCrawl->dest); 
		pCrawl = pCrawl->next; 
		} 
	printf("\n"); 
	} 
} 

void Enqueue(struct BFS_Data* bfs_data, int key)
{
struct QueueNode* newnode = (struct QueueNode*) malloc(sizeof(struct QueueNode));
newnode->key = key;
newnode->next = NULL;
bfs_data->rear->next = newnode;
bfs_data->rear = newnode;
}

void Dequeue(struct BFS_Data* bfs_data)
{
struct QueueNode* temp = bfs_data->front;
bfs_data->front = bfs_data->front->next;
free(temp);
	if(bfs_data->front == NULL)
	{
	bfs_data->rear = NULL;
	}
}

struct LCRS_Node* Add_Node(struct LCRS_Node* LCRS_curr_node, int child_node, int key)
{
struct LCRS_Node* temp = (struct LCRS_Node*) malloc(sizeof(struct LCRS_Node));
temp->key = key;
temp->child = NULL;
temp->next = NULL;
temp->bfs_done_flag = 1;

	if(child_node)
	{
	LCRS_curr_node->child = temp;
	}
	else
	{
	LCRS_curr_node->next = temp;
	}

return temp;
}

struct LCRS_Node* Find_LCRS_node(struct LCRS_Node* root, int key)
{
	if(root != NULL)
	{
		if(root->key == key && root->bfs_done_flag == 1)
		{
		root->bfs_done_flag = 0;
		return root;
		}
		else
		{
		struct LCRS_Node* Found_Node = Find_LCRS_node(root->child, key);
			if(Found_Node == NULL)
			{
			Found_Node = Find_LCRS_node(root->next, key);
			}	
		return Found_Node;
		}
	}
	else
	{
	return NULL;
	}
}

int Count_LCRS_children(struct LCRS_Node* root, struct LCRS_child_count* count_list)
{
struct LCRS_Node* node;
int count = 0;
	if(root != NULL)
	{
		if(root->child != NULL)
		{
		count = count + Count_LCRS_children(root->child, count_list);
		node = root->child;
			while(node)
			{
			count = count + 1;
			node = node->next;
			count = count + Count_LCRS_children(node, count_list);
			}
			
		}
		
	count_list[root->key].count = count_list[root->key].count + count;
	}
return count;
}

void Display_LCRS_sibling(struct LCRS_Node* root)
{
struct LCRS_Node* node;
printf("\n%d", root->key);
	if(root != NULL)
	{
		if(root->child != NULL)
		{
		node = root->child;
			while(node)
			{
			printf(" --> %d", node->key);
			node = node->next;
			}
			
			Display_LCRS_sibling(root->child);
		}
		
		if(root->next != NULL)
		{
		Display_LCRS_sibling(root->next);
		}
	}
}

void Display_LCRS_child(struct LCRS_Node* root)
{
	if(root != NULL)
	{
		if(root->child != NULL)
		{
		printf("\n%d is child of %d", root->child->key, root->key);
		Display_LCRS_child(root->child);
		}
		
		if(root->next != NULL)
		{
		Display_LCRS_child(root->next);
		}
	}
}

void Display_LCRS(struct LCRS_Node* root)
{
printf("\nDisplaying Child nodes : \n");
Display_LCRS_child(root);
printf("\nDisplaying Sibling nodes : \n");
Display_LCRS_sibling(root);
}

void dfs(struct Graph* graph, struct Conn_Comp* cc, int v, int compnum)
{
int w; 
cc->arr_vis[v].visited = 1; 
cc->arr_com[v].component = compnum;
struct AdjListNode* pCrawl = graph->array[v].head; 
	while(pCrawl) 
	{
		if (!cc->arr_vis[pCrawl->dest].visited)
		{
		dfs(graph, cc, pCrawl->dest, compnum);
		} 
	pCrawl = pCrawl->next; 
	}
}

int find_connected_comp(struct Graph* graph, int n, struct Conn_Comp* cc)
{
int i, cn = 0, max_comp;
cc->arr_vis = (struct Conn_Comp_Vis*) malloc((n+1) * sizeof(struct Conn_Comp_Vis));
cc->arr_com = (struct Conn_Comp_Com*) malloc((n+1) * sizeof(struct Conn_Comp_Com));

	for(i=1; i<=n; i++)
	{
	cc->arr_vis[i].visited = 0; 
	cc->arr_com[i].component = 0;
	}

	for(i=1; i<=n; i++)
	{
		if(!cc->arr_vis[i].visited)
		{ 
		dfs(graph, cc, i, ++cn);
		}
	}
printf("\nGraph has %d components", cn);
struct Comp_List* cl = (struct Comp_List*) malloc(sizeof(struct Comp_List));
cl->arr_com_size_list = (struct Comp_Size*) malloc((cn+1) * sizeof(struct Comp_Size));

	for(i=1; i<=cn; i++)
	{
	cl->arr_com_size_list[i].cmp_size = 0;
	}

	for(i=1; i<=n; i++)
	{
	cl->arr_com_size_list[cc->arr_com[i].component].cmp_size = cl->arr_com_size_list[cc->arr_com[i].component].cmp_size + 1;
	}

printf("\nFollowing is list of components, and their size : ");
	for(i=1; i<=cn; i++)
	{
	printf("\n%d, %d,", i, cl->arr_com_size_list[i].cmp_size);
	}
	
max_size = cl->arr_com_size_list[1].cmp_size;
max_comp = 1;
	for(i=1; i<=cn; i++)
	{
		if(cl->arr_com_size_list[i].cmp_size > max_size)
		{
		max_size = cl->arr_com_size_list[i].cmp_size;
		max_comp = i;
		}
	}
printf("\nMaximum Component No. : %d, with size: %d nodes", max_comp, max_size);

return max_comp;
}

struct Graph* ErdosRenyi(int n, float p)
{
int i, j, edges=0;
double decide;
FILE *fp;
fp=fopen("Random_Graph.txt","w");
	if(fp == NULL) 
	{ 
	printf("\nCannot create new file to store Random Graph!\n"); 
	exit(0);
	}

struct Graph* graph = createGraph(n);
	for(i=1; i<=n-1; i++)
	{
		for(j=i+1; j<=n; j++)
		{
		decide = (double)rand()/(double)RAND_MAX;
			if(decide >= p)
			{
			continue;
			}
			else
			{
			addEdge(graph, i, j);
			edges++;
			fprintf(fp, "%d %d\n", i, j);
			}
		}
	}
printf("\nGraph Created with %d Edges", edges);
fclose(fp);
return graph;
}

int** Convert_AdjList_AdjMat(struct Graph* graph, int **arr)
{
int i, j, l, m;

	for(i=1; i<=graph->V; i++)
	{
		for(j=1; j<=graph->V; j++)
		{
		arr[i][j] = 99999;
		}
	}

	for(i=1; i<=graph->V; i++)
	{
		arr[i][i] = 0;
	}
	
	for(i=1; i<=graph->V; i++)
	{
	struct AdjListNode* pCrawl = graph->array[i].head;
		while(pCrawl)
		{
		arr[i][pCrawl->dest] = 1;
		pCrawl = pCrawl->next;
		}
	}

return arr;
}

void bfs(struct Graph* graph, int n, int src, int** bfs_dist, int** bfs_path)
{
int i, w, child_node, child_count, dummy;
struct AdjListNode* list_ptr;
struct BFS_Data* bfs_data = (struct BFS_Data*) malloc(sizeof(struct BFS_Data));
bfs_data->arr_vis = (struct BFS_Vis*) malloc((n+1) * sizeof(struct BFS_Vis));

	for(i=1; i<=n; i++)
	{
	bfs_data->arr_vis[i].visited = 0; 
	}

bfs_data->arr_vis[src].visited = 1;

struct QueueNode* newnode = (struct QueueNode*) malloc(sizeof(struct QueueNode));
newnode->key = src;
newnode->next = NULL;
bfs_data->front = newnode;
bfs_data->rear = newnode;

	while(bfs_data->front != NULL)
	{
	list_ptr = graph->array[bfs_data->front->key].head;
	child_node = 1;
		
		while(list_ptr)
		{
			if((bfs_data->arr_vis[list_ptr->dest].visited == 0) || ((bfs_data->arr_vis[list_ptr->dest].visited == 1) && (bfs_dist[src][list_ptr->dest] == (bfs_dist[src][bfs_data->front->key] + 1))))
			{
			Enqueue(bfs_data, list_ptr->dest);
			bfs_data->arr_vis[list_ptr->dest].visited = 1;
			bfs_dist[src][list_ptr->dest] = bfs_dist[src][bfs_data->front->key] + 1;
			bfs_path[src][list_ptr->dest] += 1;
			}
		list_ptr = list_ptr->next;
		}
	Dequeue(bfs_data);
	}
}

float* Execute_BFS(struct Graph* graph, int n, struct Conn_Comp* cc, int max_comp)
{
int i, j, k, l;
int **bfs_dist; int **bfs_path; float* bfs_bc;
total_path_count = 0;
struct Total_count_list* total_count_list = (struct Total_count_list*) malloc(sizeof(struct Total_count_list));
total_count_list->count_list = (struct Total_count*) malloc((n+1) * sizeof(struct Total_count));

bfs_dist = (int** )malloc((n+1) * sizeof(int *));
bfs_path = (int** )malloc((n+1) * sizeof(int *));
bfs_bc   = (float*)malloc((n+1) * sizeof(float));

	for (i=1; i<=n; i++)
	{
	bfs_dist[i] = (int *)malloc((n+1) * sizeof(int));
	bfs_path[i] = (int *)malloc((n+1) * sizeof(int));
	bfs_bc[i] = 0;
	}


	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
		bfs_dist[i][j] = 0;
		bfs_path[i][j] = 0;
		}
	}

clock_t t = clock();

	for(i=1; i<=n; i++)
	{
		if(cc->arr_com[i].component == max_comp)
		{
		bfs(graph, n, i, bfs_dist, bfs_path);
		}
	}

	for(k=1; k<=n; k++)
	{
		for(i=1; i<=n; i++)
		{
			for(j=1; j<=n; j++)
			{
				if((bfs_dist[i][k] + bfs_dist[k][j] == bfs_dist[i][j]) && (bfs_path[i][j] != 0))
				{
				bfs_bc[k] += (float) bfs_path[i][k] * bfs_path[k][j]/bfs_path[i][j];
				}			
			}
		}
	}
	
	for(i=1; i<=n; i++)
	{
	bfs_bc[i] = bfs_bc[i]/2;
	}
bfs_end:	
return bfs_bc;
}

float* Execute_Flyod_Warshall(int** arr, int no_of_nodes)
{
int i, j, k, l, m;
int** c = (int **)malloc((no_of_nodes+1) * sizeof(int *));
int** dist = (int **)malloc((no_of_nodes+1) * sizeof(int *));
int** path = (int **)malloc((no_of_nodes+1) * sizeof(int *));
int** p = (int **)malloc((no_of_nodes+1) * sizeof(int *));
float* floyd_bc = (float *)malloc((no_of_nodes+1) * sizeof(float));
	
	for (i=1; i<=no_of_nodes; i++)
	{
	c[i] = (int *)malloc((no_of_nodes+1) * sizeof(int));
	dist[i] = (int *)malloc((no_of_nodes+1) * sizeof(int));
	path[i] = (int *)malloc((no_of_nodes+1) * sizeof(int));
	p[i] = (int *)malloc((no_of_nodes+1) * sizeof(int));
	floyd_bc[i] = 0;
	}

	for(i=1; i<=no_of_nodes; i++)
	{
		for(j=1; j<=no_of_nodes; j++)
		{
		c[i][j] = arr[i][j];
		dist[i][j] = arr[i][j];
		path[i][j] = arr[i][j];
			if(i == j)
			{
			path[i][j] = 0;
			c[i][j] = 0;
			}
			if(arr[i][j] == 99999)
			{
			path[i][j] = 0;
			c[i][j] = 0;
			}
		p[i][j] = 0;
		}
	}
	
	for(k=1; k<=no_of_nodes; k++)
	{
		for(i=1; i<=no_of_nodes; i++)
		{
			for(j=1; j<=no_of_nodes; j++)
			{
				if(dist[i][k] + dist[k][j] == dist[i][j])
				{
				path[i][j] += path[i][k] * path[k][j];
				}

				if(dist[i][k] + dist[k][j] < dist[i][j])
				{
				dist[i][j] = dist[i][k] + dist[k][j];
				path[i][j] = path[i][k] * path[k][j];
				p[i][j] = k;
				}
				
			}
		}
	}

floyd_bc = (float *)malloc((no_of_nodes+1) * sizeof(float));
	
	for(k=1; k<=no_of_nodes; k++)
	{
		for(i=1; i<=no_of_nodes; i++)
		{
			for(j=1; j<=no_of_nodes; j++)
			{
				if((dist[i][k] + dist[k][j] == dist[i][j]) && (path[i][j] != 0))
				{
				floyd_bc[k] += (float) path[i][k] * path[k][j]/path[i][j];
				}			
			}
		}
	}

	for(i=1; i<=no_of_nodes; i++)
	{
	floyd_bc[i] = floyd_bc[i]/2;
	}

return floyd_bc;
}

struct Graph* Upload_graph(char* filename, FILE *fptr)
{
int node, src_node, trgt_node, flag, line = 1, edges = 0, n;
char c;
FILE *fptr1;
n = Find_no_of_nodes(fptr);
no_of_nodes = n;
	if(n == -1)
	{
	printf("\nGraph not created!\n");
	return NULL;
	}
struct Graph* graph = createGraph(n);
fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{ 
	printf("\nCannot open file!\n"); 
	exit(0);
	}

c = fgetc(fptr1);
	while (c != EOF) 
	{ 
	node = 0;
		while(c != 32)
		{
		node = node*10 + ((int) c - 48);
		c = fgetc(fptr1);
		}
    	  	
  	src_node = node;  	
	node = 0;
	c = fgetc(fptr1);
	    	while(c >= 48 && c <= 57)
	    	{
    		node = node*10 + ((int) c - 48);
    		c = fgetc(fptr1);
	    	}
    	   	
    	trgt_node = node;
    	addEdge(graph, src_node, trgt_node);
	edges++;			

	   	while( c != 10)
	    	{
	    	c = fgetc(fptr1);
	   	}
	c = fgetc(fptr1);
	}
fclose(fptr1);
printf("\nGraph created with %d Nodes and %d Edges\n", n, edges);
return graph;
}

int Find_no_of_nodes(FILE *fptr)
{
int node, flag, line = 1, n, max = -1;
char c;
c = fgetc(fptr); 
	while (c != EOF) 
	{ 
	node = 0;
	flag = 1;
		while(c != 32)
	    	{
			if( c >= 48 && c <= 57)
			{
			flag = 0;
			node = node*10 + ((int) c - 48);
			c = fgetc(fptr);
			}

			else
			{
			flag = 1;
			printf("\nInvalid input data in file, line no. : %d\n", line);
			break;
			}
		}
    		
    		if(flag)
	  	{
	    	printf("\nInvalid input data in file, line no. : %d\n", line);
	    	max = -1;
	    	break;
	    	}
  	
  		if(max < node)
  		{
  		max = node;
  		}

	node = 0;
	flag = 1;
	c = fgetc(fptr);
	    	while(c >= 48 && c <= 57)
	    	{
    		flag = 0;
    		node = node*10 + ((int) c - 48);
    		c = fgetc(fptr);
	    	}
    	
	    	if(flag)
	    	{
	    	printf("\nInvalid input data in file, line no. : %d\n", line);
	    	max = -1;
	    	break;
	    	}

  		if(max < node)
  		{
  		max = node;
  		}
    	
	   	while( c != 10)
	    	{
	    	c = fgetc(fptr);
	   	}
	line++;
	c = fgetc(fptr);
	}
fclose(fptr); 
return max;
}

void Write_Execution_Time(char filename[], int n, double time)
{
FILE *fptr;
fptr = fopen(filename, "a");
	if(fptr == NULL)
	{
	printf("\nCannot open %s file!\n", filename);
	exit(0);
	}
fprintf(fptr, "%d,%lf\n", n, time);
fclose(fptr);
}
