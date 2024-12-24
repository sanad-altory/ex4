/******************
Name:SANAD ALTORY
ID:214633703
Assignment:EX4
*******************/

#include <stdio.h>
#include <string.h>
#define MIN_NUMBER 0
#define MAX_SIZE 20
#define TRUE 1
#define PYRAMID 5
#define MAX_DIMENSION 30
#define MAX_SLOTS 100
#define MAX_LENGTH 15
#define NUM_CHARCTER 256
// Structure to represent a slot in the crossword puzzle
typedef struct {
    int row , col , length;
    // 'H' for horizontal, 'V' for vertical
    char direction;
}Slots;

int task1RobotPaths(int x, int y);
float task2HumanPyramid(float arr[PYRAMID][PYRAMID], int row , int col);
int task3ParenthesisValidator(char expected);
int task4QueensBattle(int size,int row ,int col,int Queens[MAX_SIZE][MAX_SIZE], char board[MAX_SIZE][MAX_SIZE]
    ,int region[NUM_CHARCTER]);
int task5CrosswordGenerator(char grid[MAX_SIZE][MAX_SIZE], Slots slots[], int slot_index, int num_slots,
    char words[MAX_SLOTS][MAX_LENGTH], int word_index[], int num_words);
void print_grid(char grid[MAX_SIZE][MAX_SIZE], int size, int row, int col);
// Utility function to clear the input buffer
void clearBuffer();

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");
        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;

            case 1: {
                //Robot Paths
                int column , row ;
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d", &column, &row);
                // Check if the user entered negative numbers
                if (column < MIN_NUMBER || MIN_NUMBER > row)
                    printf(" %d" , MIN_NUMBER);
                else {
                    // Call the recursive function to calculate the number of paths
                    printf("The total number of paths the robot can take to reach home is: %d\n" ,task1RobotPaths(column, row) );
                }
                break;
            }
            case 2: {
                // Task 2: Human Pyramid
                printf("Please enter the weights of the cheerleaders:\n");
                // Variable to check for negative weights
                int negative_weight = 0;
                float list[PYRAMID][PYRAMID];
                // Loop to get the weights from the user
                for (int i = 0; i < PYRAMID; i++) {
                    for (int j = 0; j <= i; j++) {
                        scanf("%f", &list[i][j]);
                        // Check for negative weights
                        if (list[i][j] < MIN_NUMBER) {
                            printf("Negative weights are not supported.\n");
                            negative_weight = 1;
                        }
                    }// Exit the outer loop if a negative weight was found
                    if(negative_weight)
                        break;
                }
                if(!negative_weight) {
                    printf("The total weight on each cheerleader is:\n");
                    for (int i = 0; i < PYRAMID; i++) {
                        for (int j = 0; j <= i; j++) {
                            //print the new weights after calling the recursion function.
                            printf("%.2f ", task2HumanPyramid(list,i, j));
                        }
                        printf("\n");
                    }
                }
                break;
            }
            case 3: {
                // Task 3: Parenthesis Validation
                clearBuffer();
                printf("Please enter a term for validation:\n");

                if (task3ParenthesisValidator('\0')) {
                    printf("The parentheses are balanced correctly.\n");
                } else {
                    printf("The parentheses are not balanced correctly.\n");
                    clearBuffer();
                }
                break;
            }
            case 4: {
                // Task 4: Queens Battle
                printf("Please enter the board dimensions:\n");
                int size;
                if(scanf("%d", &size) > MAX_SIZE)
                    break;
                char board[MAX_SIZE][MAX_SIZE];
                //An array to mark Queens places on the board.
                int queens[MAX_SIZE][MAX_SIZE] = {{0}};
                printf("Please enter a %d*%d puzzle board:\n", size ,size);
                // Loop to read in the board
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        scanf(" %c", &board[i][j]);
                    }
                }// Array to keep track of regions used by queens
                int region_used[NUM_CHARCTER] = {0};
                // Call the function task4QueensBattle with the necessary parameters
                if(task4QueensBattle(size , MIN_NUMBER,MIN_NUMBER,queens, board , region_used)) {
                    printf("Solution:\n");
                    // If task4QueensBattle returns true, print the solution
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < size; j++) {
                            if (queens[i][j] == 1) {
                                printf("X ");
                            }else
                                printf("* ");
                        }
                        printf("\n");
                    }
                }else
                    printf("This puzzle cannot be solved.\n");
                break;
            }
            case 5: {
                // Task 5: Crossword Generator
                int size, num_slots, num_words;
                // Input the dimensions of the crossword grid
                printf("Please enter the dimensions of the crossword grid:\n");
                scanf("%d", &size);
                // Input the number of slots
                printf("Please enter the number of slots in the crossword:\n");
                scanf("%d", &num_slots);
                Slots slots[num_slots];
                printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                for (int i = 0; i < num_slots; i++) {
                    scanf("%d %d %d %c", &slots[i].row, &slots[i].col, &slots[i].length, &slots[i].direction);
                }
                // Input the number of words in the dictionary
                printf("Please enter the number of words in the dictionary:\n");
                scanf("%d", &num_words);
                while (num_words < num_slots) {
                    printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", num_slots);
                    scanf("%d", &num_words);
                }
                char words[MAX_SLOTS][MAX_LENGTH];
                printf("Please enter the words for the dictionary:\n");
                for (int i = 0; i < num_words; i++) {
                    scanf("%s", words[i]);
                }
                // Initialize the grid with '#' (empty cells)
                char grid[MAX_SIZE][MAX_SIZE];
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        grid[i][j] = '#';
                    }
                }
                // Array to keep track of which words have been used
                int word_index[MAX_SLOTS] = {0};
                // Try to solve the crossword puzzle
                if (task5CrosswordGenerator(grid, slots, MIN_NUMBER, num_slots, words, word_index, num_words)) {
                    print_grid(grid, size, MIN_NUMBER, MIN_NUMBER);
                } else {
                    printf("This crossword cannot be solved.\n");
                }
                break;
            }
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }
    } while (task != 6);
}
//A Recursion function to check all the possible routes that the robot need to make.
int task1RobotPaths(int x, int y)
{
    //n,m for saving num of the routes.
    int n = 0, m = 0 ;
    //The base case is when the robot get to his destination (0,0).
    if (x == MIN_NUMBER && y == MIN_NUMBER)
        return 1;
    //check all the possible routes until you get to (0,y).
    if (x > MIN_NUMBER)
       n =task1RobotPaths(x - 1, y);
    //check all the possible routes until you get to (x,0).
    if (y > MIN_NUMBER)
       m =task1RobotPaths(x, y - 1);
    // return the all possible routes to get to (0,0).
    return n + m ;
}
//A function that get weights by their position in the array and make the changes on them
float task2HumanPyramid(float arr[PYRAMID][PYRAMID], int row , int col)
{
    if (col > row)
        return 0;
    // if the weight on top of the pyramid don't make changes.
    if( col == MIN_NUMBER && row == MIN_NUMBER)
        return arr[row][col];
    /* the first if is for the weights that are in the middle
     * the second if is for the weights that are in leftist side */
    if (row >= col && col > MIN_NUMBER)
        return  task2HumanPyramid(arr, row -1, col - 1)/2 + task2HumanPyramid(arr, row -1, col)/2 + arr[row][col];
    if(col == MIN_NUMBER && row > col)
        return  task2HumanPyramid(arr, row -1, col)/2 + arr[row][col] ;
    //to check that is not out of the boundreis.
    return 0;
}
void clearBuffer() {
    // Consume any characters remaining in the input buffer until a newline
    scanf("%*[^ \n]"); // This consumes all characters except '\n'
    scanf("%*c");      // This consumes the newline itself
}

int task3ParenthesisValidator(char expected) {
    char c;
    scanf("%c", &c);
    // Base case: If the character is a newline, check if we have reached the end of the validation.
    if (c == '\n') {
        // If the expected character is '\0', it means the parentheses are balanced.
        return expected == '\0';
    }
    // Check for opening parentheses and call the function recursively to match them.
    if (c == '(')
        if (!task3ParenthesisValidator(')')) return 0;
     if (c == '[')
        if (!task3ParenthesisValidator(']')) return 0;
     if (c == '{')
        if (!task3ParenthesisValidator('}')) return 0;
     if (c == '<')
        if (!task3ParenthesisValidator('>')) return 0;

    // Check for closing parentheses, and validate if they match the expected parenthesis.
     if (c == ')' || c == ']' || c == '}' || c == '>') {
        // If the character matches the expected closing parenthesis, return 1 (true), otherwise return 0 (false).
        return c == expected;
    }
    // If none of the above conditions are met, call the function recursively with the same expected parameter.
    return task3ParenthesisValidator(expected);
}

// Checks if a row is safe for placing a queen by ensuring no queen is present in the row.
int isRowSafe(int size,int row ,int col,int Queens[MAX_SIZE][MAX_SIZE]) {
    //Reached end of row; no queens found, so it's safe.
    if(col == size)
        return 1 ;
    // A queen is already present in this row.
    if(Queens[row][col] == TRUE)
        return 0;
    // Recursively check the next column in the row.
    return isRowSafe(size,row,col + 1,Queens);
}
// Checks if a column is safe for placing a queen by ensuring no queen is present in the column.
int isColSafe(int size,int row ,int col,int Queens[MAX_SIZE][MAX_SIZE]) {
    // Reached the end of the column; no queens found, so it's safe.
    if(row == size)
        return 1;
    // A queen is already present in this column.
    if(Queens[row][col] == TRUE)
        return 0;
    // Recursively check the next row in the column.
    return isColSafe(size,row + 1,col,Queens);
}
// Checks if a square is safe by validating diagonal safety and ensuring it doesn't go out of bounds
int isSafeSquare(int size,int row ,int col,int Queens[MAX_SIZE][MAX_SIZE], char board[MAX_SIZE][MAX_SIZE]
    ,int region[NUM_CHARCTER],int expand) {
    // Out-of-bounds check.
    if(row >= size || col >= size || row < MIN_NUMBER || col < MIN_NUMBER) {
        expand = 1 ;
        return expand;
    }// A queen is present on this square.
    if(Queens[row][col] == TRUE ) {
        expand = 0;
        return expand;
    }// If expand is unset, set it and return safe.
    if(!expand){
        expand = 1;
        return expand;
    }// Recursively check all diagonal directions for safety.
    return isSafeSquare(size, row + 1 ,col + 1 ,Queens,board,region,MIN_NUMBER)&&
            isSafeSquare(size, row + 1 ,col - 1 ,Queens,board,region,MIN_NUMBER)&&
            isSafeSquare(size, row - 1 ,col + 1 ,Queens,board,region,MIN_NUMBER)&&
            isSafeSquare(size, row - 1 ,col - 1 ,Queens,board,region,MIN_NUMBER);
}
// Solves the problem of placing queens in the board while meeting the constraints.
int task4QueensBattle(int size,int row ,int col,int Queens[MAX_SIZE][MAX_SIZE], char board[MAX_SIZE][MAX_SIZE],int region[NUM_CHARCTER]) {
    // If all columns are processed, solution is found.
    if(col == size) {
        return 1;
    }// If all rows are processed for this column without success, backtrack.
    if(row == size) {
        return 0;
    }// Check all safety conditions: square, row, column, and region constraints.
    if(isSafeSquare(size , row , col , Queens,board,region ,TRUE) &&
        isRowSafe(size,row, MIN_NUMBER,Queens) &&
        isColSafe(size, MIN_NUMBER,col,Queens) &&
        region[(int)board[row][col]] == MIN_NUMBER ) {
        // Place the queen.
        Queens[row][col] = TRUE;
        // Mark the region as occupied.
        region[(int)board[row][col]] = TRUE;
        // Recursively attempt to place queens in the next column.
        if (task4QueensBattle(size, MIN_NUMBER,col + 1,Queens,board,region)) {
            return 1 ;
        }// Backtrack: Remove the queen and reset the region.
        Queens[row][col] = MIN_NUMBER;
        region[(int)board[row][col]] = MIN_NUMBER;
    }// Try the next row in the current column.
    return task4QueensBattle(size ,row +1 , col , Queens ,board , region);
}
// Function to print the grid row by row
void print_grid(char grid[MAX_SIZE][MAX_SIZE], int size, int row, int col) {
    // Base case: If all rows are printed, stop recursion
    if (row == size) {
        return;
    }// If end of the row is reached
    if (col == size) {
        printf("|\n");
        // Recursive call for the next row
        print_grid(grid, size, row + 1, MIN_NUMBER);
        return;
    }
    printf("| %c ", grid[row][col]);
    // Recursive call for the next column
    print_grid(grid, size, row, col + 1);
}
// Function to check if a word can be placed in the grid
int can_place_word(char grid[MAX_SIZE][MAX_SIZE], char word[], int row, int col, int length,
    char direction, int index) {
    // Horizontal placement
    if (direction == 'H') {
        // Out of bounds
        if (col + length > MAX_SIZE) return 0;
        // All characters match
        if (index == length) return 1;
        // Check if the current cell is empty or matches the word character
        if (grid[row][col + index] == '#' || grid[row][col + index] == word[index]) {
            return can_place_word(grid, word, row, col, length, direction, index + 1);
        }
        // Conflict found
        return 0;
    } else if (direction == 'V') {
        if (row + length > MAX_SIZE) return 0;
        if (index == length) return 1;
        if (grid[row + index][col] == '#' || grid[row + index][col] == word[index]) {
            return can_place_word(grid, word, row, col, length, direction, index + 1);
        }
        return 0;
    }
    return 0;
}// Function to place a word in the grid
void place_word(char grid[MAX_SIZE][MAX_SIZE], char word[], int row, int col, int length, char direction, int index) {
    if (index == length) return;

    if (direction == 'H') {
        grid[row][col + index] = word[index];
        place_word(grid, word, row, col, length, direction, index + 1);
    } else if (direction == 'V') {
        grid[row + index][col] = word[index];
        place_word(grid, word, row, col, length, direction, index + 1);
    }
}

void remove_word(char grid[MAX_SIZE][MAX_SIZE], int row, int col, int length, char direction, int index) {
    // Base case: Word removed completely
    if (index == length)
        return;
    // Horizontal placement
    if (direction == 'H') {
        // Place the character
        grid[row][col + index] = '#';
        // Recursive call for the next character
        remove_word(grid, row, col, length, direction, index + 1);
    } else if (direction == 'V') {
        grid[row + index][col] = '#';
        remove_word(grid, row, col, length, direction, index + 1);
    }
}// Function to remove a word from the grid (backtracking)
int task5Helper(char grid[MAX_SIZE][MAX_SIZE], Slots slots[], int slot_index, int num_slots,
    char words[MAX_SLOTS][MAX_LENGTH],int word_index[], int num_words, int row, int col, int length
    ,char direction, int word_idx) {
    // No more words to try
    if (word_idx == num_words) {
        return 0;
    }
    if (!word_index[word_idx]  && (int)strlen( words[word_idx]) == length && can_place_word(grid
        ,words[word_idx], row, col, length, direction, MIN_NUMBER)) {
        place_word(grid, words[word_idx], row, col, length, direction, MIN_NUMBER);
        // Mark the word as used
        word_index[word_idx] = 1;

        if (task5CrosswordGenerator(grid, slots, slot_index + 1, num_slots, words, word_index, num_words)) {
            return 1;
        }// Backtrack
        remove_word(grid, row, col, length, direction, MIN_NUMBER);
        // Unmark the word as used
        word_index[word_idx] = 0;
    }
    return task5Helper(grid, slots, slot_index, num_slots, words, word_index, num_words, row, col
        , length, direction, word_idx + 1);
}

int task5CrosswordGenerator(char grid[MAX_SIZE][MAX_SIZE], Slots slots[], int slot_index, int num_slots,
    char words[MAX_SLOTS][MAX_LENGTH], int word_index[], int num_words) {
    // All slots are filled
    if (slot_index == num_slots) {
        return 1;
    }
    int row = slots[slot_index].row,length = slots[slot_index].length,col = slots[slot_index].col;
    char direction = slots[slot_index].direction;
    // Try each word in the dictionary
    return task5Helper(grid, slots, slot_index, num_slots, words, word_index, num_words, row, col
        , length, direction, MIN_NUMBER);
}



