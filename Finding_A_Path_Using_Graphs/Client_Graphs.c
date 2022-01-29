#include<stdio.h>
#include "Header_Graphs.h"

int xstart, ystart;
int xend, yend;
int row = 0;
int col = 0;
int vid = 0;

int main()
{
	header h1;
	stack s1;
	queue q1;
	char input[50];
	
	//Initializing the header to graph vertex
	init(&h1);

	//Accepts the input file to be read
	printf("Enter the input file which you wish to read: ");
	scanf("%s", input);

	//Creates the multilist matrix
	if(create_graph(input, &h1))
	{
		printf("\nThe input file was succesfully read\n");
	}
	else
	{
		printf("\nThe input file could not be read\n");
	}

	//Displays the graph as a matrix
	display(&h1);
	
	//Finds Path through DFS traversal and prints it into outdfs file
	init1(&s1);
	if(dfs_path(&h1, &s1))
	{
		printf("A path is found through DFS traversal and is printed onto the output file outdfs.txt\n");
		display_outdfsfile(&s1);
	}
	else
	{
		printf("No path is found through DFS traversal\n");
		display_outdfsfile(&s1);
	}

	//Finds path through BFS traversal and prints it into outbfs file
	init2(&q1);
	if(bfs_path(&h1, &q1, &s1))
	{
		printf("A path is found through BFS traversal and is printed onto the output file outbfs.txt\n");
		display_outbfsfile(&s1);
	}
	else
	{
		printf("No path is found through BFS traversal\n");
		display_outbfsfile(&s1);
	}

	return 0;
}
