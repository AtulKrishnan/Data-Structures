#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "PES2UG20CS076_H.h"

extern int xstart, ystart;
extern int xend, yend;
extern int row;
extern int col;
extern int vid;
int flag1 = 0;
int flag2 = 0;

//Initializing the header of the multilist
void init(header* h1)
{
	h1->head = NULL;
}

//Initializing the stack top to NULL
void init1(stack* s1)
{
	s1->top = NULL;
}

//Initializing the front and rear of the queue
void init2(queue* q1)
{
	q1->front = NULL;
	q1->rear = NULL;
}

//Creating the vertex nodes and the neighbor nodes of the adjacency list representation
void getnode(header* h2, int i)
{
	//Does not create vertex if value is 1
	if(i == 1)
		return;
	else if(i == 0)
	{
		//Creating vertex for the given value
		vertex* vtemp = (vertex*)malloc(sizeof(vertex));
		vid = vid + 1;
		vtemp->value = i;
		vtemp->vid = vid;
		vtemp->row = row;
		vtemp->col = col;
		vtemp->visited = 0;
		vtemp->link = NULL;
		vtemp->next = NULL;
		vtemp->plink = vtemp;

		//Inserting at front for vertex linked list
		if(h2->head == NULL)
			h2->head = vtemp;
		else
		{
			vtemp->next = h2->head;
			h2->head = vtemp;
		}
		
		vertex* p = h2->head;
		while(p != NULL)
		{
			//Checking if the vertex has an adjacent node on left
			if(p->row == row && p->col == col-1)
			{
				neighbor* ntemp = (neighbor*)malloc(sizeof(neighbor));
				ntemp->vlink = vtemp;
				ntemp->nlink = NULL;
				
				//Inserting at front for ajacent nodes list
				if(p->link == NULL)
					p->link = ntemp;
				else
				{
					ntemp->nlink = p->link;
					p->link = ntemp;
				}
			}

			//Checking if the vertex has an adjacent node on top
			if(p->row == row-1 && p->col == col)
			{
				neighbor* ntemp = (neighbor*)malloc(sizeof(neighbor));
				ntemp->vlink = vtemp;
				ntemp->nlink = NULL;

				//Inserting at front for adjacent nodes list
				if(p->link == NULL)
					p->link = ntemp;
				else
				{
					ntemp->nlink = p->link;
					p->link = ntemp;
				}
			}
			p = p->next;
		}
	}
}

//Read the values from the input file
int create_graph(char* input, header* h1)
{
	//Opening the file
	FILE* fp = fopen(input, "r");
	if(fp == NULL)
	{
		return 0;
	}
	char key[10], line[500];
	int i;	

	// Getting start and end coordinates from the file
	fgets(key, 10, fp);
	char* token = strtok(key, " ");
	xstart = atoi(token);
	token = strtok(NULL, " ");
	ystart = atoi(token);
	fgets(key, 10, fp);
	token = strtok(key, " ");
	xend = atoi(token);
	token = strtok(NULL, " ");
	yend = atoi(token);

	
	//Reading line by line from the file
	while(fgets(line, 50, fp) != NULL)
	{
		col = 0;
		char* token = strtok(line, " ");
		i = atoi(token);
		getnode(h1, i);
		token = strtok(NULL, " ");
		i = atoi(token);
		while(i == 0 || i == 1)
		{
			col = col + 1;
			getnode(h1, i);
			token = strtok(NULL, " ");
			i = -1;
			if (token)
				i = atoi(token);
		}
		row = row + 1;
	}
	fclose(fp);
	return(1);
}

//Display the graph in the form of a matrix
void display(header* h1)
{
	vertex* p = h1->head;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<=col;j++)
		{
			flag1 = 1;
			p = h1->head;
			while(p != NULL)
			{
				if(p->row == i && p->col == j)
				{
					printf("%d ", p->value);
					flag1 = 0;
					break;
				}
				p = p->next;
			}
			if(flag1 == 1)
				printf("1 ");
		}
		printf("\n");
	}
}

//Pushes into the stack
void push(vertex* n, stack* s1)
{
	snode* temp = (snode*)malloc(sizeof(snode*));
	temp->pnode = n;
	temp->link = NULL;
	if(s1->top == NULL)
	{
		s1->top = temp;
	}
	else
	{
		temp->link = s1->top;
		s1->top = temp;
	}
}

//Pops from the stack
void pop(stack* s1)
{
	if(s1->top == NULL)
	{
		return;
	}
	else
	{
		snode* t;
		t = s1->top->link;
		free(s1->top);
		s1->top = t;
	}
} 

//Recursive DFS function to find the end coordinate
void dfs_find(vertex* p, stack* s1)
{
	p->visited = 1;
	if(p->row == xend && p->col == yend)
	{
		push(p, s1);
		//printf("%d %d\n", p->row, p->col);
		flag1 = 1;
		return;
	}
	for(neighbor *i = p->link; i != NULL; i = i->nlink)
	{
		if(flag1 == 1)
			return;
		if(i->vlink->visited != 1)
		{
			push(p, s1);
			//printf("%d %d\n", p->row, p->col);
			dfs_find(i->vlink, s1);
		}
	}
	if(flag1 != 1)
		pop(s1);
}

//Find the starting coordinates and calls the recursive function dfs_find
int dfs_path(header* h1, stack* s1)
{
	flag1 = 0;
	vertex* p = h1->head;
	while(p != NULL)
	{
		//Searches for starting coordinates
		if(p->row == xstart && p->col == ystart)
		{
			printf("\n");
			dfs_find(p, s1);
			if(flag1 == 0)
				flag2 = 1;
			break;
		}
		p = p->next;
	}
	if(flag2 == 1)
		return 0;
	else
		return 1;
}

//Recursively print the elements in the stack in reverse order
void display1(snode* s, FILE* fp1)
{
	if(s->link != NULL)
	{
		display1(s->link, fp1);
	}
	fprintf(fp1, "%d %d\n", s->pnode->row, s->pnode->col);
}	

//Creates a file pointer and checks if a path is found and calls display1
void display_outdfsfile(stack* s1)
{
	FILE* fp1 = fopen("outdfs.txt", "a+");
	if(fp1 == NULL)
	{
		printf("The output file is not found\n");
		return;
	}
	snode* s = s1->top;
	if(flag2 == 1)
	{
		fprintf(fp1, "The Path is not found:\n-1");
	}
	else
	{
		fprintf(fp1, "The Path is:\n");
		display1(s, fp1);
	}
	fclose(fp1);
}

//Function to insert at the rear of a queue
void enque(vertex* n, queue* q1)
{
	qnode* temp = (qnode*)malloc(sizeof(qnode));
	temp->vnode = n;
	temp->link = NULL;
	if(q1->front == NULL)
	{
		q1->front = temp;
		q1->rear = temp;
	}
	else
	{
		q1->rear->link = temp;
		q1->rear = temp;
	}
}

//Function to delete from the front of a queue
void deque(queue* q1)
{
	if(q1->front == NULL)
	{
		return;
	}
	else
	{
		//qnode* t;
		//t = q1->front->link;
		//return(q1->front);
		//free(q1->front);
		q1->front = q1->front->link;
	}
} 

//Does the BFS traversal of the entire graph and links each vertex to its parent node through plink
int bfs_path(header* h1, queue* q1, stack* s1)
{
	vertex* p = h1->head;
	int flag3 = 0;

	//Makes all nodes unvisited
	while(p != NULL)
	{
		p->visited = 0;
		p = p->next;
	}
	p = h1->head;
	while(p != NULL)
	{
		//Searches for starting coordinates
		if(p->row == xstart && p->col == ystart)
		{
			break;
		}
		p = p->next;
	}
	p->visited = 1;
	//printf("%d %d\n", p->row, p->col);
	enque(p, q1);
	qnode* v;
	while(q1->front != NULL)
	{
		v = q1->front;
		deque(q1);
		for(neighbor *i = v->vnode->link; i != NULL; i = i->nlink)
		{
			if(i->vlink->visited != 1)
			{
				i->vlink->visited = 1;
				//printf("%d %d\n", i->vlink->row, i->vlink->col);
				enque(i->vlink, q1);
				i->vlink->plink = v->vnode;
			}
		}
		free(v);
	}
	//printf("\n");
	p = h1->head;
	while(p != NULL)
	{
		//Finds the coordinates of the destination element if it exists
		if(p->row == xend && p->col == yend)
		{
			flag3 = 1;
			break;
		}
		p = p->next;
	}	
	if(flag3 != 1)
		return 0;

	//Making the stack empty
	while(s1->top != NULL)
		pop(s1);

	//Traversing from the destination element to the start element using the link to its parent and pushing into the stack
	while(p->row != xstart || p->col != ystart)
	{
		if(p == p->plink)
			return 0;
		else
		{
			push(p, s1);
			//printf("%d %d\n", p->row, p->col);
			p = p->plink;
		}
	}
	push(p, s1);
	return 1;
}

//Prints the coordinates of the path if it exists into a outbfs file
void display_outbfsfile(stack* s1)
{
	FILE* fp1 = fopen("outbfs.txt", "a+");
	if(fp1 == NULL)
	{
		printf("The output file is not found\n");
		return;
	}
	snode* s = s1->top;
	if(flag2 == 1)
	{
		fprintf(fp1, "The Path is not found:\n-1");
	}
	else
	{
		fprintf(fp1, "The Path is:\n");
		while(s != NULL)
		{
			fprintf(fp1, "%d %d\n", s->pnode->row, s->pnode->col);
			s = s->link;
		}
	}
	fclose(fp1);
}