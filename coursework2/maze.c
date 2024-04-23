/**
 * @file maze.c
 * @author Darshan Sajeev
 * @brief Code for the maze game for COMP1921 Assignment 2
 * NOTE - You can remove or edit this file however you like - this is just a provided skeleton code
 * which may be useful to anyone who did not complete assignment 1.
 */

#include <stdio.h>
#include <stdlib.h>

// defines for max and min permitted dimensions
#define MAX_DIM 100
#define MIN_DIM 5

// defines for the required autograder exit codes
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3

typedef struct __Coord
{
    int x;
    int y;
} coord;

typedef struct __Maze
{
    char **map;
    int height;
    int width;
    coord start;
    coord end;
} maze;

/**
 * @brief Initialise a maze object - allocate memory and set attributes
 *
 * @param this pointer to the maze to be initialised
 * @param height height to allocate
 * @param width width to allocate
 * @return int 0 on success, 1 on fail
 */
int create_maze(maze *this, int height, int width)
{
    //Allocate space for the map
    //Code adapted from https://stackoverflow.com/questions/37650088/in-c-how-do-i-allocate-space-for-my-struct
    this->map = (char **)malloc(height * sizeof(char **));
    //Check if map is empty
    if(this->map == NULL){
        return 1;
    }
    // //Read the maze
    // for(int i=0; i < this->height; i++){
    //     this->map[i] = (char *)malloc((width + 1) * sizeof(char));
    //     if (this->map[i] == NULL){
    //         for(int j = 0; j < i; j++){
    //             free(this->map);
    //         }
    //         free(this->map);
    //         return 1;
    //     }
    // }

    //Success condition
    this->height = height;
    this->width = width;
    return 0;
}

/**
 * @brief Free the memory allocated to the maze struct
 *
 * @param this the pointer to the struct to free
 */
//Code adapted from https://stackoverflow.com/questions/13590812/c-freeing-structs
void free_maze(maze *this)
{
    for (int i = 0; i < this->height; i++) {
        free(this->map[i]);
    }
    free(this->map);
}

/**
 * @brief Validate and return the width of the mazefile
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid width (5-100)
 */
int get_width(FILE *file)
{
    //Code adapted from https://stackoverflow.com/questions/27169161/how-do-i-check-if-the-line-is-over
    //and https://stackoverflow.com/questions/12080129/how-can-know-if-the-end-of-line-in-c
    //and https://stackoverflow.com/questions/32366665/resetting-pointer-to-the-start-of-file
    //Increase width until end of line is reached 
    int width = 0;
    int temp = fgetc(file);
    while (temp != EOF && temp != '\n'){
        width++;
    }
    fseek(file, 0, SEEK_SET);
    return width;
}

/**
 * @brief Validate and return the height of the mazefile
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid height (5-100)
 */
int get_height(FILE *file)
{
    int height = 0;
    int temp = fgetc(file);
    while (temp != EOF && temp != '\n'){
        height++;
    }
    fseek(file, 0, SEEK_SET);
    return height;
}

/**
 * @brief read in a maze file into a struct
 *
 * @param this Maze struct to be used
 * @param file Maze file pointer
 * @return int 0 on success, 1 on fail
 */
int read_maze(maze *this, FILE *file)
{
    this->width = get_width(file);
    this->height = get_height(file);

    this->map = (char **)malloc(this->height * sizeof(char *));
    if (this->map == NULL) {
        return 1; // Allocation failed
    }
    for (int i = 0; i < this->height; i++) {
        this->map[i] = (char *)malloc((this->width + 1) * sizeof(char));
        if (this->map[i] == NULL) {
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(this->map[j]);
            }
            free(this->map);
            return 1; // Allocation failed
        }
        fgets(this->map[i], this->width + 1, file);

        // Set start and end coordinates manually
        // (You need to implement this logic)
    }

    // Add a return statement for successful completion
    return 0; // Success
}

/**
 * @brief Prints the maze out - code provided to ensure correct formatting
 *
 * @param this pointer to maze to print
 * @param player the current player location
 */
void print_maze(maze *this, coord *player)
{
    // make sure we have a leading newline..
    printf("\n");
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // decide whether player is on this spot or not
            if (player->x == j && player->y == i)
            {
                printf("X");
            }
            else
            {
                printf("%c", this->map[i][j]);
            }
        }
        // end each row with a newline.
        printf("\n");
    }
}

/**
 * @brief Validates and performs a movement in a given direction
 *
 * @param this Maze struct
 * @param player The player's current position
 * @param direction The desired direction to move in
 */
void move(maze *this, coord *player, char direction)
{
    switch (direction) {
        case 'w':
        case 'W':
            if (player->y > 0 && this->map[player->y - 1][player->x] != '#') {
                player->y--;
            }
            break;
        case 'a':
        case 'A':
            if (player->x > 0 && this->map[player->y][player->x - 1] != '#') {
                player->x--;
            }
            break;
        case 's':
        case 'S':
            if (player->y < this->height - 1 && this->map[player->y + 1][player->x] != '#') {
                player->y++;
            }
            break;
        case 'd':
        case 'D':
            if (player->x < this->width - 1 && this->map[player->y][player->x + 1] != '#') {
                player->x++;
            }
            break;
        default:
            printf("Invalid input\n");
            break;
    }
}

/**
 * @brief Check whether the player has won and return a pseudo-boolean
 *
 * @param this current maze
 * @param player player position
 * @return int 0 for false, 1 for true
 */
int has_won(maze *this, coord *player)
{
    if (this->map[player->y][player->x] == 'E') {
        return 1; // Player has reached the end and won
    } else {
        return 0; // Player has not won yet
    }
}

// int main()
// {
//     // check args

//     // set up some useful variables (you can rename or remove these if you want)
//     coord *player;
//     maze *this_maze = malloc(sizeof(maze));
//     FILE *f;

//     // open and validate mazefile

//     // read in mazefile to struct

//     // maze game loop

//     // win

//     // return, free, exit
// }

int main() {
    // Check arguments if needed

    // Set up some useful variables
    coord player;
    maze this_maze;
    FILE *file;

    // Open and validate maze file
    file = fopen("maze.txt", "r"); // Replace "maze.txt" with your maze file name
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FILE_ERROR;
    }

    // Read maze file into struct
    if (read_maze(&this_maze, file) != 0) {
        fprintf(stderr, "Error reading maze\n");
        fclose(file);
        return EXIT_MAZE_ERROR;
    }
    fclose(file);

    // Initialize player position to the starting point
    player.x = this_maze.start.x;
    player.y = this_maze.start.y;

    // Maze game loop
    char input;
    while (1) {
        print_maze(&this_maze, &player);

        printf("Enter movement (W/A/S/D), show map (M), or quit (Q): ");
        scanf(" %c", &input);

        if (input == 'q' || input == 'Q') {
            break; // Quit the game loop
        } else if (input == 'm' || input == 'M') {
            print_maze(&this_maze, &player); // Show the entire map
        } else {
            move(&this_maze, &player, input); // Move the player
            if (has_won(&this_maze, &player)) {
                printf("Congratulations! You have won!\n");
                break; // Exit the game loop
            }
        }
    }

    // Free allocated memory and exit
    free_maze(&this_maze);
    return EXIT_SUCCESS;
}
