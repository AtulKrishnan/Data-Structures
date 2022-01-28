//Contains the link to the adjacent vertex
struct neighbor
{
	struct vertex* vlink;
	struct neighbor* nlink;
};
typedef struct neighbor neighbor;

//Contains the data of the vertex
struct vertex
{
	int vid;
	int value;
	int row;
	int col;
	int visited;
	struct neighbor* link;
	struct vertex* next;
	struct vertex* plink;
};
typedef struct vertex vertex;

//Points at the first vertex in the linked list
struct header
{
	struct vertex* head;
};
typedef struct header header;

//Structure that contains the data of each node in the stack
struct snode
{
	vertex* pnode;
	struct snode* link;
};
typedef struct snode snode;

//Structure that points to the top of the stack
struct stack
{
	struct snode* top;
};
typedef struct stack stack;

//Structure that contains the data of each node in the queue
struct qnode
{
	vertex* vnode;
	struct qnode* link;
};
typedef struct qnode qnode;

//Structure that contains the links to the front and rear of the queue
struct queue
{
	struct qnode* front;
	struct qnode* rear;
};
typedef struct queue queue;

void init(header*);
void init1(stack*);
void init2(queue*);
int create_graph(char*, header*);
void display(header*);
int dfs_path(header*, stack*);
void display_outdfsfile(stack*);
int bfs_path(header*, queue*, stack*);
void display_outbfsfile(stack*);