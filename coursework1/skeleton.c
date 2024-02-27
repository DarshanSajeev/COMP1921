#include <stdio.h>
#include <stdlib.h>

/*Creates a structure for the Maze which includes it's size and where every #, ' ', S and E is*/
typedef struct MazeStruct{
    int row;
    int column;
} Maze;

/*Creates the Player structure that holds the current position of the player and */
typedef struct PlayerStruct{
    char name[20];
    int xpos;
    int ypos;
}Player;

/*Loads the maze onto the map and checks if the maze meets the requirements*/
int LoadMaze(FILE filename){
    //Open file
    //Store file in suitable variable

    //Checks if the map meets the requirements of the game
        // Checks for unsuitable characters in the file
        // Checks for the correct number of colums/rows
    //Extract file and use contents to create map
    // Store column and row numbers

    //Suitable output if incorrect file type/name
}

/*Places the user at S and allows the player to move with WASD*/
int Movement(){
    // Uses the Validation function when an input is detected
    // Changes the user's position on the Map
    // Checks if user is on 'E'
        // If so, GameEnd function is tiggered
}

/*Makes sure the user inputs are valid and stopping the user from going off the maze or through walls*/
int Validation(){

    // Checks if the user has inputted 'W', 'A', 'S' or 'D' or their respective lowercase inputs
    // Checks if the movement is valid against the rules:
        //Checks if the user will be travelling through ' '
        //Checks if the player will still be on the game board after the move

    // If incorrect input, error message is produced
}

/*Allows the map to show when 'M' is pressed*/
int Map(){
    // Prints out the map
    // Dispalys the player's location with an 'X'
}

int GameEnd(){
    // Suitable game end message
    // Close file
}

int main(){
    // Validates the file using LoadMaze function
    // While loops to collect user inputs every turn using Movement function
    // Gives option to use the Map fucntion when the user inputs 'M'
}