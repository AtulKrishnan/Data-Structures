#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Header_Multilist.h"

extern int xstart, ystart;
extern int xend, yend;
extern int row;
extern int col;
extern int tcol;
int flag1 = 0;
int flag2 = 0;

//Initializing the header of the multilist
void init(bot* b1)
{
	b1->head = NULL;
}

//Initializing the top of the stack
void init1(stack* s1)
{
	s1->top = NULL;
}

//Creating the header and data nodes of the multilist
void getnode(bot* b2, int i)
{
	//Creates header row if its in the first row or if number of rows > columns
	if(row == 0 || (row>0 && (row>tcol)))
	{
		node* htemp = (node*)malloc(sizeof(node));
		htemp->down = htemp;
		htemp->right = htemp;
		htemp->h = 1;
		if(b2->head == NULL)
		{
			htemp->u.next = htemp;
			b2->head = htemp;
		}
		else
		{
			node* p = b2->head;
			node* t = p;
			while(p && p->u.next != t)
			{
				p = p->u.next;
			}
			htemp->u.next = b2->head;
			p->u.next = htemp;
		}
	}

	//Creates data node only if the value is 0
	if(i == 0)
	{
		int count = 0;
		node* dtemp = (node*)malloc(sizeof(node));
		dtemp->down = NULL;
		dtemp->right = NULL;
		dtemp->u.data.row = row;
		dtemp->u.data.col = col;
		dtemp->u.data.value = i;
		dtemp->h = 0;
		
		//Searching for header node of row
		node* p = b2->head;
		while(count != row)
		{
			p = p->u.next;
			count = count + 1;
		}
		node* present = NULL;
		node* t = p;
		while(p && p->right != t)
		{
			present = p->right;
			p = p->right;
		}
		if(present == NULL)
		{
			dtemp->right = t;
			t->right = dtemp;
		}
		else
		{
			dtemp->right = t;
			present->right = dtemp;
		}
		
		//Searching for header node of column
		p = b2->head;
		count = 0;
		while(count != col)
		{
			p = p->u.next;
			count = count + 1;
		}
		present = NULL;
		t = p;
		while(p && p->down != t)
		{
			present = p->down;
			p = p->down;
		}
		if(present == NULL)
		{
			dtemp->down = p->down;
			p->down = dtemp;
		}
		else
		{
			dtemp->down = present->down;
			present->down = dtemp;
		}
	}
}
				
		

int create_matrix(char* input, bot* b1)
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
		tcol = col;
		col = 0;
		char* token = strtok(line, " ");
		i = atoi(token);
		getnode(b1, i);
		token = strtok(NULL, " ");
		i = atoi(token);
		while(i == 0 || i == 1)
		{
			col = col + 1;
			getnode(b1, i);
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

//Displays the multilist as a 2D array
void display(bot* b1)
{
	node* p = b1->head->right;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<=col;j++)
		{
			if(p->u.data.row == i && p->u.data.col == j)
			{
				printf("%d ", p->u.data.value);
				p = p->right;
			}
			else
			{
				printf("1 ");
			}
		}
		printf("\n");
		if (p && p->u.next && p->u.next->right)
			p = p->u.next->right;
		
	}
}

//Pushes into the stack
void push(node* n, stack* s1)
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
snode* pop(stack* s1)
{
	if(s1->top == NULL)
	{
		return NULL;
	}
	else
	{
		snode* t;
		t = s1->top->link;
		return(s1->top);
		free(s1->top);
		s1->top = t;
	}
} 		

//Recursively checks, and finds the best path till the end coordinate if present
void search(node* p, stack *s1)
{
	if(p->u.data.col == xend && p->u.data.row == yend)
	{
		push(p, s1);
		//printf("%d %d\n", p->u.data.row, p->u.data.col);
		flag1 = 1;
		return;
	}
	if(p->right->u.data.col == p->u.data.col + 1 && flag1 == 0)
	{
		push(p, s1);
		//printf("%d %d\n", p->u.data.col, p->u.data.row);
		search(p->right, s1);
	}
	if(p->down->u.data.row == p->u.data.row + 1 && flag1 == 0)
	{
		if(s1->top->pnode != p)
		{
			push(p, s1);
			//printf("%d %d\n", p->u.data.col, p->u.data.row);
		}
		search(p->down, s1);
	}
	if(((p->u.data.col > xend && p->u.data.row > yend) || (s1->top->link == NULL)) && (flag1 == 0))
	{
		//printf("-1");
		flag1 = 1;
		flag2 = 1;
		return;
	}
	else
	{
		snode* t = pop(s1);
		return;
	}
}

//Searches for the starting coordinate and calls search
int search_path(bot* b1, stack* s1)
{
	node* p = b1->head->right;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<=col;j++)
		{
			if(p->u.data.row == xstart && p->u.data.col == ystart)
			{
				printf("\nThe Path is:\n");
				search(p, s1);
				break;
			}
			if(p->u.data.row == i && p->u.data.col == j)
			{
				p = p->right;
			}
		}
		if(flag2 == 1)
			return 0;
		else
			return 1;
		if (p && p->u.next && p->u.next->right)
			p = p->u.next->right;		
	}
}

//Recursively prints the elements in the stack in reverse order
void display1(snode* s, FILE* fp1)
{
	if(s->link != NULL)
	{
		display1(s->link, fp1);
	}
	fprintf(fp1, "%d %d\n", s->pnode->u.data.row, s->pnode->u.data.col);
}	

//Creates a file pointer and checks if a path is found and calls display1
void display_outputfile(stack* s1)
{
	FILE* fp1 = fopen("output.txt", "a+");
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
	
