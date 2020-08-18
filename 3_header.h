
struct AdjListNode 
{ 
	int dest; 
	struct AdjListNode* next; 
}; 
  
struct AdjList 
{ 
	struct AdjListNode *head;  
}; 

struct Graph 
{ 
	int V;
	struct AdjList* array; 
}; 
  
struct Comp_Size
{
	int cmp_size;
};

struct Comp_List
{
	struct Comp_Size* arr_com_size_list;
};

struct Conn_Comp_Vis
{
	int visited;
};

struct Conn_Comp_Com
{
	int component;	
};

struct Conn_Comp
{
	struct Conn_Comp_Vis* arr_vis;
	struct Conn_Comp_Com* arr_com;
};

struct QueueNode
{
	int key;
	struct QueueNode* next;
};

struct BFS_Vis
{
	int visited;
};

struct BFS_Dist
{
	int distance;
};

struct BFS_Data
{
	struct QueueNode* front;
	struct QueueNode* rear;
	struct BFS_Vis* arr_vis;
	struct BFS_Dist* arr_dist;
};

//struct definition for Left Child Right Sibling tree representation
struct LCRS_Node
{
	int key;
	int bfs_done_flag;
	struct LCRS_Node* child;
	struct LCRS_Node* next;
};

struct LCRS_Root
{
	struct LCRS_Node* root;
};

struct LCRS_child_count
{
	int count;
};

struct LCRS_child_count_list
{
	struct LCRS_child_count* count_list;
};

struct Total_count
{
	int count;
};

struct Total_count_list
{
	struct Total_count* count_list;
};

void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
struct AdjListNode* newAdjListNode(int dest);
struct Graph* ErdosRenyi(int n, float p);
struct Graph* createGraph(int V);
int find_connected_comp(struct Graph* graph, int n, struct Conn_Comp* cc);
void dfs(struct Graph* graph, struct Conn_Comp* cc, int v, int compnum);
float* Execute_BFS(struct Graph* graph, int n, struct Conn_Comp* cc, int max_comp);
void bfs(struct Graph* graph, int n, int src, int** bfs_dist, int** bfs_path);
struct LCRS_Node* Add_Node(struct LCRS_Node* LCRS_curr_node, int child_node, int key);
struct LCRS_Node* Find_LCRS_node(struct LCRS_Node* root, int key);
int Count_LCRS_children(struct LCRS_Node* root, struct LCRS_child_count* no_of_child);
int** Convert_AdjList_AdjMat(struct Graph* graph, int** arr);
float* Execute_Flyod_Warshall(int** arr, int no_of_nodes);
struct Graph* Upload_graph(char* filename, FILE *fptr);
int Find_no_of_nodes(FILE *fptr);
void Write_Execution_Time(char filename[], int n, double time);
double total_path_count; int no_of_nodes; int max_size; int **arr;
