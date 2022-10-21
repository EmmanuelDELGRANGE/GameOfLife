/*
 * lifegame.c
 *
 *  Created on:
 *      Author:
 */
#include "lifegame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* hard-coded world size */
#define WORLDWIDTH 39
#define WORLDHEIGHT 20

/* character representations of cell states */
#define CHAR_ALIVE '*'
#define CHAR_DEAD ' '

/* current cell states of the world */
static int world[WORLDWIDTH][WORLDHEIGHT];

/* next generation cell states */
static int nextstates[WORLDWIDTH][WORLDHEIGHT];

/* functions to write for Part B of lab */
void initialize_world_from_file(const char * filename) {
	/* TODO: read the state of the world from a file with
	   name "filename". Assume file exists, is readable, and
	   the ith character of the jth line (zero-indexed) describes
	   world[i][j] according to the characters CHAR_ALIVE and
	   CHAR_DEAD

	   Assume a line does not contain more than 256 characters
	   (including newline). If a line doesn't contain WORLDWIDTH
	   characters, remaining cells in line are presumed DEAD.
	   Similarly, if the file does not contain WORLDHEIGHT lines,
	   remaining lines are presumed dead.

	   On error, print some useful error message and call abort().

	   Also need to reset the next generation to DEAD
	 */

	//***** VARIABLES *****
    int ligTemp, colTemp; // Creating and initializing temporary line and column cursors
    ligTemp=0;
    colTemp=0;

    FILE *mapFile=NULL; // Pointeur du fichier
    char charTemp=0; // Caractere lu dans le chichier


	//***** PROGRAM *****//
	//Opening file
    mapFile=fopen((const char*)filename,"r");
    if(mapFile==NULL)
    {
        printf("Erreur lors du chargement du fichier de map\n");
        exit(0);
    }


	//Reading values
    while(ligTemp<WORLDHEIGHT)  //Reading the values in the file char by char while ligTemp is smaller than ligSize
    {
        charTemp = fgetc(mapFile); //reading a character in the file
        if(charTemp==EOF)  //If End Of File is reached -> end of the function
        {
            ligTemp=WORLDHEIGHT;
        }
        else if(charTemp=='\n')  //If End Of Line is reached -> function continues but the values are putted to the next row of the matrix
        {
            ligTemp++;
            colTemp=0;
        }
		else if(colTemp>=WORLDWIDTH)//Skip if world line is already full
		{
			colTemp++;
		}
        else
        {

            world[ligTemp][colTemp]=((int)charTemp-'0'); //A normal character is detected so its send to its new matrix location
            colTemp++;
        }
    }
    fclose(mapFile); //Closing the file once the reading is done
    scanf("%c",&charTemp);



}

void save_world_to_file(const char * filename) {
	/* TODO: write the state of the world into a file with
	   name "filename". Assume the file can be created, or if
	   the file exists, overwrite the file. The ith character
	   of the jth line (zero-indexed) describes world[i][j]
	   using the characters CHAR_ALIVE and CHAR_DEAD

	   This file should be readable using the function
	   initialize_world_from_file(filename) above; we can use
	   it to resume a game later
	 */
	//Variables:
    int ligTemp, colTemp; // Creating and initializing temporary line and column cursors
    ligTemp=0;
    colTemp=0;
	FILE *mapFile=NULL; // Map File

    ///Opening map file
    mapFile= fopen ((const char*)filename, "w"); //Opening the designated save file
    if(mapFile==NULL)
    {
        printf("Erreur lors de la sauvegarde\n");
        exit(0);
    }


    for (ligTemp=0; ligTemp<WORLDHEIGHT; ligTemp++) //Going trough the rows of the matrix
    {
        for(colTemp=0; colTemp<WORLDWIDTH; colTemp++) //Going trough the columns of the matrix
        {
            fputc((world[ligTemp][colTemp])+48,mapFile); //putting the cell value from the matrix in the save file
        }
        if(ligTemp<(WORLDHEIGHT-1))fputc('\n',mapFile); //While the loop is not at the last row a '\n' is putted in the end of each rows
    }

    fclose(mapFile); //Closing the save file

}

/* you shouldn't need to edit anything below this line */

/* initializes the world to a hard-coded pattern, and resets
   all the cells in the next generation to DEAD */
void initialize_world(void) {
	int i, j;

	for (i = 0; i < WORLDWIDTH; i++)
		for (j = 0; j < WORLDHEIGHT; j++)
			world[i][j] = nextstates[i][j] = DEAD;
	/* pattern "glider" */
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;
}

int is_World_Empty(void) {
	for (int i = 0; i < WORLDWIDTH; i++)
		for (int j = 0; j < WORLDHEIGHT; j++)
			if (world[i][j] == ALIVE) return 0;
	return 1;
}

int get_world_width(void) {
	return WORLDWIDTH;
}

int get_world_height(void) {
	return WORLDHEIGHT;
}

int get_cell_state(int x, int y) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
		return DEAD;
	return world[x][y];
}

void set_cell_state(int x, int y, int state) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
		fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
		abort();
	}
	nextstates[x][y] = state;
}

void finalize_evolution(void) {
	int x, y;
	for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			world[x][y] = nextstates[x][y];
			nextstates[x][y] = DEAD;
		}
	}
}

void output_world(void) {
	char worldstr[2*WORLDWIDTH+2];
	int i, j;

	worldstr[2*WORLDWIDTH+1] = '\0';
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
	for (i = 0; i <= 2*WORLDWIDTH; i+=2)
		worldstr[i] = '|';
	for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
}
