# Data-Structures
This repository contains a few C programs that i wrote for a few simple but unique problems.

A particular ‘RPA’ firm is in the process of developing a restaurant which has bot waiters. Bot needs to deliver the food from the specified exit door, of the kitchen with multiple exit doors to the specified table.

The restaurant has blocked areas where Bot cannot move and the passages where it can move. The layout of restaurant can be rectangular or square. Layout map can be considered as a matrix of cells where cell with ‘0’ represents the passage and cell with ‘1’, the blocked area. Bot has memorised this map in a particular format for faster processing. Given a particular table location bot needs to find the path from the kitchen from the specified exit door to the table to serve the customer. Bot has a constraint it can move only in either right or down direction one step at a time (i.e. only to the adjacent cell in right or down direction provided it is not blocked) with first preference to right direction.

I provide the code that helps the bot with the path from a specific exit door of the kitchen to the mentioned table if there exists one. If multiple paths exists my code finds any one.

At the time of this commit, there are two programs in this repository as a solution to the above question.
Both the programs deal with a kind of a maze which is a 2D matrix present in input.txt. 
First line in this file indicates the start point for the Bot, second line termination point, 3rd line onwards represent the layout matrix.
My code reads the matrix from the input.txt file and creates the matrix. 
It then finds a path from the sarting point to ending point if possible and prints each coordinate onto an output file that is created.

In the first program, I have used a Multilist to create the 2D matrix.
The output file is output.txt

In the second program, I have used a Graph data structure to create the 2D matrix.
There are two output files. One for BFS traversal and one for DFS traversal called outbfs.txt and outdfs.txt.

Both these files contain:
1. Client File
2. Driver File
3. Header File
