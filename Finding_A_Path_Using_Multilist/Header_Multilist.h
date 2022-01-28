//Structure that contains the data
typedef struct data
{
	int row;
	int col;
	int value;
}data;

//Structure which can either become the header or a data node
struct node
{
	struct node* down;
	struct node* right;
	int h;
	union
	{
		struct node* next;
		data data;
	}u;
};
typedef struct node node;

//Structure that points to the first header node
struct bot
{
	struct node* head;
};
typedef struct bot bot;

//Structure that contains the data of each node in the stack
struct snode
{
	node* pnode;
	struct snode* link;
};
typedef struct snode snode;

//Structure that points to the top of the stack
struct stack
{
	struct snode* top;
};
typedef struct stack stack;

//Declaration of functions
void init(bot*);
void init1(stack*);
int create_matrix(char*, bot*);
void display(bot*);
int search_path(bot*, stack*);
void display_outputfile(stack*);