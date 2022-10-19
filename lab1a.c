/*
 * lab1a.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

void display_world(void);

void promp_next_generation(void);

int main(void)
{
	int n;

	/* initialize the world */
	initialize_world_from_file("glider.txt");


	for (n = 0; n < NUM_GENERATIONS; n++){
		next_generation();
		promp_next_generation(); //(optional): Visualise world in each generation
	}

	/* Output final world state */
	display_world();


	return 0;
}

void next_generation(void) {
	/* For every cell, set the state in the next
	   generation according to the Game of Life rules

	   Hint: use get_next_state(x,y) and set_next_state(x,y) */

	for(int x=0; x<get_world_width();x++){ //Going through all columns
		for(int y=0;y<get_world_height();y++){ //Going through all lines
			set_cell_state(x,y,get_next_state(x,y)); //Update cell_state with next_state value (ALIVE or DEAD)
		}
	}

	finalize_evolution(); //Copy result into world[][]
}

int get_next_state(int x, int y) {
	/* For the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */
	int numNeighbors=num_neighbors(x,y);

	switch (numNeighbors)
	{
	//Case of solitude:
	case 0:
	case 1:
		return DEAD;
		break;
	//Case of life / Birth
	case 2:
	case 3:
		return ALIVE;
		break;

	//Case of overpopultation
	default:
		return DEAD;
		break;
	}
}

int num_neighbors(int x, int y) {
	/* For the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) as a hard code, this function takes care of size overflow
	   
	*/

	int numNeighbors=0;
	//Left column
	numNeighbors+=get_cell_state(x-1,y+1);
	numNeighbors+=get_cell_state(x-1,y);
	numNeighbors+=get_cell_state(x-1,y-1);
	//Center column
	numNeighbors+=get_cell_state(x,y+1);
	numNeighbors+=get_cell_state(x,y-1);
	//Right column
	numNeighbors+=get_cell_state(x+1,y+1);
	numNeighbors+=get_cell_state(x+1,y);
	numNeighbors+=get_cell_state(x+1,y-1);

	return numNeighbors;

}

void display_world(void){
	char charState[2]="*.";

	system("cls"); //clear the console on WINDOWS
	for(int x=0; x<get_world_width();x++){ //Going through all columns
		printf("|"); //Start of line
		for(int y=0;y<get_world_height();y++){ //Going through all lines
			printf(" %c |",charState[get_cell_state(x,y)]); //Print DEAD or ALIVE char and form a cell
		}
		printf("\n"); //End of line
	}
}

void promp_next_generation(){
	char useless;
	display_world();
	printf("\n***** Next generation? *****\n");
	scanf("%c",&useless);
}