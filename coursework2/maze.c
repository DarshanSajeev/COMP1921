/**
 * @file maze.c
 * @author Darshan Sajeev
 * @brief Code for the maze game for COMP1921 Assignment 2
 * NOTE - You can remove or edit this file however you like - this is just a provided skeleton code
 * which may be useful to anyone who did not complete assignment 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

//Code adapted from https://stackoverflow.com/questions/37650088/in-c-how-do-i-allocate-space-for-my-struct
int create_maze(maze *this, int height, int width)
{
    // Check if height and width are within the allowed range
    if (height < MIN_DIM || height > MAX_DIM || width < MIN_DIM || width > MAX_DIM) {
        fprintf(stderr, "Error: Maze dimensions must be between %d and %d\n", MIN_DIM, MAX_DIM);
        return 1;
    }

    // Allocate space for the map
    this->map = (char **)malloc(height * sizeof(char *));
    if (this->map == NULL) {
        return 1; // Allocation failed
    }

    // Allocate space for each row
    for (int i = 0; i < height; i++) {
        this->map[i] = (char *)malloc((width + 1) * sizeof(char));
        if (this->map[i] == NULL) {
            // Free memory for previously allocated rows
            for (int j = 0; j < i; j++) {
                free(this->map[j]);
            }
            free(this->map);
        }
        // Add spaces to every row 
        memset(this->map[i], ' ', width);
        this->map[i][width] = '\0';
    }

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
    //free every space in the struct
    for (int i = 0; i < this->height; i++) {
        free(this->map[i]);
    }
    free(this->map);
}

/**
 * @brief Validate and return the width of the maze file
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
    int temp;
    while ((temp = fgetc(file)) != '\n' && temp != EOF) {
        width++;
    }
    fseek(file, 0, SEEK_SET);
    return width;
}

/**
 * @brief Validate and return the height of the maze file
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid height (5-100)
 */
int get_height(FILE *file)
{
    //Same as get_width
    int height = 0;
    int temp;
    while ((temp = fgetc(file)) != EOF) {
        if (temp == '\n') {
            height++;
        }
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

/*Code adapted from https://stackoverflow.com/questions/13590812/c-freeing-structs*/
int read_maze(maze *this, FILE *file)
{
    // Initialize start and end points
    this->start.x = -1;
    this->start.y = -1;
    this->end.x = -1;
    this->end.y = -1;

    // Read the maze dimensions
    this->width = get_width(file);
    this->height = get_height(file);

    // Return error when height and width too big
    if (this->width > MAX_DIM || this->height > MAX_DIM) {
        return EXIT_MAZE_ERROR;
    }
    // Return error when width and height too small
    if (this->width < MIN_DIM || this->height < MIN_DIM) {
        return EXIT_MAZE_ERROR;
    }

    // Allocate memory for the maze map
    this->map = (char **)malloc(this->height * sizeof(char *));
    if (this->map == NULL) {
        return EXIT_MAZE_ERROR;
    }

    // Loop through each row of the maze
    for (int i = 0; i < this->height; i++) {
        // Allocate memory for each row
        this->map[i] = (char *)malloc((this->width + 1) * sizeof(char));
        if (this->map[i] == NULL) {
            // Free memory for previously allocated rows
            for (int j = 0; j < i; j++) {
                free(this->map[j]);
            }
            free(this->map);
            return EXIT_MAZE_ERROR;
        }

        // Read the characters of the current row
        int j = 0;
        int c;
        // Read characters until newline or EOF is encountered
        while ((c = fgetc(file)) != '\n' && c != EOF && j < this->width) {
            this->map[i][j++] = c;
        }
        // Fill remaining characters with spaces if necessary
        while (j < this->width) {
            this->map[i][j++] = ' ';
        }
        this->map[i][j] = '\0';

        // Check if the row length is consistent
        if (j != this->width) {
            return EXIT_MAZE_ERROR;
        }

        // Find start and end points
        for (int k = 0; k < this->width; k++) {
            // Check for S and E
            if (this->map[i][k] == 'S') {
                if (this->start.x != -1 || this->start.y != -1) {
                    return EXIT_MAZE_ERROR;
                }
                this->start.x = k;
                this->start.y = i;
            } else if (this->map[i][k] == 'E') {
                if (this->end.x != -1 || this->end.y != -1) {
                    return EXIT_MAZE_ERROR;
                }
                this->end.x = k;
                this->end.y = i;
            // Check for incorrect character
            } else if (this->map[i][k] != '#' && this->map[i][k] != ' ') {
                return EXIT_MAZE_ERROR;
            }
        }
    }

    // Check if start and end points are found
    if (this->start.x == -1 || this->start.y == -1) {
        return EXIT_MAZE_ERROR;
    }
    if (this->end.x == -1 || this->end.y == -1) {
        return EXIT_MAZE_ERROR;
    }

    return 0;
}

/**
 * @brief Prints the maze out - code provided to ensure correct formatting
 *
 * @param this pointer to maze to print
 * @param player the current player location
 */
void print_maze(maze *this, coord *player)
{
    printf("\n");
    //Loop through the mazed to place the player
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
    //Collect input from user
    switch (direction) {
        case 'w':
        case 'W':
        //Check if player is able to move up and if there is a '#'
            if (player->y > 0 && this->map[player->y - 1][player->x] != '#') {
                player->y--;
            }
            break;
        case 'a':
        case 'A':
            //Check if player is able to move left and if there is a '#'
            if (player->x > 0 && this->map[player->y][player->x - 1] != '#') {
                player->x--;
            }
            break;
        case 's':
        case 'S':
            //Check if player is able to move down and if there is a '#'
            if (player->y < this->height - 1 && this->map[player->y + 1][player->x] != '#') {
                player->y++;
            }
            break;
        case 'd':
        case 'D':
            //Check if player is able to move right and if there is a '#'
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
//Check if the character the player is on is E
int has_won(maze *this, coord *player)
{
    if (this->map[player->y][player->x] == 'E') {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <maze_file>\n", argv[0]);
        return EXIT_ARG_ERROR;
    }

    // Set up some useful variables
    coord player;
    maze this_maze;
    FILE *file;

    // Open and validate maze file
    file = fopen(argv[1], "r");
    if (file == NULL) {
        return EXIT_FILE_ERROR;
    }

    // Read maze file into struct
    int read_result = read_maze(&this_maze, file);
    fclose(file);

    if (read_result != 0) {
        return EXIT_MAZE_ERROR;
    }

    // Initialize player position to the starting point
    player.x = this_maze.start.x;
    player.y = this_maze.start.y;

    // Maze game loop
    char input;
    while (1) {
        printf("Enter movement (W/A/S/D), show map (M), or quit (Q): ");
        scanf(" %c", &input);
        getchar();

        if (input == 'q' || input == 'Q') {
            break; // Quit the game loop
        } else if (input == 'm' || input == 'M') {
            print_maze(&this_maze, &player); // Show the entire map
        } else {
            move(&this_maze, &player, input); // Move the player
            if (has_won(&this_maze, &player)) {
                printf("Congratulations! You have won!\n");
                return EXIT_SUCCESS; // Exit the program with success code
            }
        }
    }

    // Free allocated memory and exit
    free_maze(&this_maze);
    return EXIT_SUCCESS; // Exit the program with success code
}