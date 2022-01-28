#include<stdio.h>
#include "PES2UG20CS076_H.h"

int xstart, ystart;
int xend, yend;
int row = 0;
int col = 0;
int tcol = 0;

int main()
{
	bot b1;
	stack s1;
	char input[50];
	
	//Initializing the header to multilist
	init(&b1);

	//Accepts the input file to be read
	printf("Enter the input file which you wish to read: ");
	scanf("%s", input);

	//Creates the multilist matrix
	if(create_matrix(input, &b1))
	{
		printf("\nThe input file was succesfully read\n");
	}
	else
	{
		printf("\nThe input file could not be read\n");
	}

	//Displays the multilist as a matrix
	display(&b1);
	
	//Initializes the top of the stack
	init1(&s1);
	
	//Searches if a path exists
	if(search_path(&b1 , &s1))
	{
		printf("\nA path was succesfully found and copied on to the output file\n");
	}
	else
	{
		printf("\nNo path was found from the start destination to the end\n");
	}

	//Prints the path if present in output file output.txt
	display_outputfile(&s1);
	
	return(0);
}