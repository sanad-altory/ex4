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
typedef struct {
    int row , col , length;
    char direction;
}Slots;

int task1_robot_paths(int x, int y);
float task2_human_pyramid(float arr[PYRAMID][PYRAMID], int row , int col);
int task3_parenthesis_validator(char expected);
int task4_queens_battle(int size,int row ,int col,int Queens[size][size], char board[size][size],int region[255]);
int solve_crossword(char grid[MAX_SIZE][MAX_SIZE], Slots slots[], int slot_index, int num_slots, char words[MAX_SLOTS][MAX_LENGTH], int word_index[], int num_words);
void print_grid(char grid[MAX_SIZE][MAX_SIZE], int size, int row, int col);
void initializeRegion(int region[255], int index) {
    if (index < 255) {
        region[index] = 0;
        initializeRegion(region, index + 1);
    }
}
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
                //Robot Paths
            case 1: {
                int column , row ;
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d", &column, &row);
                //check if the user enter a negative number return 0 else continue checking.
                if (column < MIN_NUMBER || MIN_NUMBER > row)
                    printf(" %d" , MIN_NUMBER);
                else {
                    //calling the recursion function to return the number of routes.
                    printf("The total number of paths the robot can take to reach home is: %d\n" ,task1_robot_paths(column, row) );
                }
                break;
            }
            case 2: {
                printf("Please enter the weights of the cheerleaders:\n");
                // an integer to check if the user enter a negative number.
                int negative_weight = 0;
                float list[PYRAMID][PYRAMID];
                //A loop that Ask the user to enter weights of the cheerleading team.
                for (int i = 0; i < PYRAMID; i++) {
                    for (int j = 0; j <= i; j++) {
                        scanf("%f", &list[i][j]);
                        //check if the user entered a negative number.
                        if (list[i][j] < MIN_NUMBER) {
                            printf("Negative weights are not supported.\n");
                            negative_weight = 1;
                        }
                    }//get out of the loop and back to the main menu.
                    if(negative_weight)
                        break;
                }
                if(!negative_weight) {
                    for (int i = 0; i < PYRAMID; i++) {
                        for (int j = 0; j <= i; j++) {
                            //print the new weights after calling the recursion function.
                            printf("%.2f ", task2_human_pyramid(list,i, j));
                        }
                        printf("\n");
                    }
                }
                break;
            }
            case 3: {
                clearBuffer();
                printf("Please enter a term for validation:\n");

                if (task3_parenthesis_validator('\0')) {
                    printf("The parentheses are balanced correctly.\n");
                } else {
                    printf("The parentheses are not balanced correctly.\n");
                }
                break;
            }
            case 4: {
                printf("Please enter the board dimensions :\n");
                int size;
                if(scanf("%d", &size) > MAX_SIZE)
                    break;
                char board[size][size];
                int Queenss[size][size];
                printf("Please enter the %d*%d puzzle board\n", size ,size);
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        scanf(" %c", &board[i][j]);
                        Queenss[i][j] = 0;
                    }
                }
                int region_used[255];
                initializeRegion(region_used,0);
                if(task4_queens_battle(size , MIN_NUMBER,MIN_NUMBER,Queenss, board , region_used)) {
                    printf("Soloution\n");
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < size; j++) {
                            if (Queenss[i][j] == 1) {
                                printf("X ");
                            }else
                                printf("* ");
                        }
                        printf("\n");
                    }
                }else
                    printf("Queens battle failed.\n");
                break;
            }
            case 5: {
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
                if (solve_crossword(grid, slots, 0, num_slots, words, word_index, num_words)) {
                    print_grid(grid, size, 0, 0);
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
            //clearBuffer();
            scanf("%*s");

        }

    } while (task != 6);
}
//A Recursion function to check all the possible routes that the robot need to make.
int task1_robot_paths(int x, int y)
{
    //n,m for saving num of the routes.
    int n = 0, m = 0 ;
    //The base case is when the robot get to his destination (0,0).
    if (x == MIN_NUMBER && y == MIN_NUMBER)
        return 1;
    //check all the possible routes until you get to (0,y).
    if (x > MIN_NUMBER)
       n =task1_robot_paths(x - 1, y);
    //check all the possible routes until you get to (x,0).
    if (y > MIN_NUMBER)
       m =task1_robot_paths(x, y - 1);
    // return the all possible routes to get to (0,0).
    return n + m ;
}
//A function that get weights by their position in the array and make the changes on them
float task2_human_pyramid(float arr[PYRAMID][PYRAMID], int row , int col)
{
    if (col > row)
        return 0;
    // if the weight on top of the pyramid don't make changes.
    if( col == MIN_NUMBER && row == MIN_NUMBER)
        return arr[row][col];
    /* the first if is for the weights that are in the middle
     * the second if is for the weights that are in leftist side */
    if (row >= col && col > MIN_NUMBER)
        return  task2_human_pyramid(arr, row -1, col - 1)/2 + task2_human_pyramid(arr, row -1, col)/2 + arr[row][col];
    if(col == MIN_NUMBER && row > col)
        return  task2_human_pyramid(arr, row -1, col)/2 + arr[row][col] ;
    //to check that is not out of the boundreis.
    return 0;
}
void clearBuffer() {
    // Consume any characters remaining in the input buffer until a newline
    scanf("%*[^ \n]"); // This consumes all characters except '\n'
    scanf("%*c");      // This consumes the newline itself
}

int task3_parenthesis_validator(char expected) {
    char c;
    scanf("%c", &c);
    if (c == '\n') {
        return expected == '\0';
    }
    if (c == '(') {
        if (!task3_parenthesis_validator(')')) return 0;
    } else if (c == '[') {
        if (!task3_parenthesis_validator(']')) return 0;
    } else if (c == '{') {
        if (!task3_parenthesis_validator('}')) return 0;
    } else if (c == '<') {
        if (!task3_parenthesis_validator('>')) return 0;
    } else if (c == ')' || c == ']' || c == '}' || c == '>') {
        return c == expected;
    }
    return task3_parenthesis_validator(expected);
}


int isRowSafe(int size,int row ,int col,int Queens[size][size]) {
    if(col == size)
        return 1 ;
    if(Queens[row][col] == 1)
        return 0;
    return isRowSafe(size,row,col + 1,Queens);
}

int isColSafe(int size,int row ,int col,int Queens[size][size]) {
    if(row == size) {
        return 1;
    }
    if(Queens[row][col] == 1)
        return 0;
    return isColSafe(size,row + 1,col,Queens);
}

int isSafeSquare(int size,int row ,int col,int Queens[size][size], char board[size][size],int region[255],int flag) {
    if(row >= size || col >= size || row < 0 || col < 0) {
        flag = 1 ;
        return flag;
    }
    if(Queens[row][col] == 1 ) {
        flag = 0;
        return flag;
    }
    if(!flag){
        flag = 1;
        return flag;
    }
    return isSafeSquare(size, row + 1 ,col + 1 ,Queens,board,region,MIN_NUMBER)&&
            isSafeSquare(size, row + 1 ,col - 1 ,Queens,board,region,MIN_NUMBER)&&
            isSafeSquare(size, row - 1 ,col + 1 ,Queens,board,region,MIN_NUMBER)&&
            isSafeSquare(size, row - 1 ,col - 1 ,Queens,board,region,MIN_NUMBER);
}

int task4_queens_battle(int size,int row ,int col,int Queens[size][size], char board[size][size],int region[255]) {
    if(col == size) {
        return 1;
    }
    if(row == size) {
        return 0;
    }
    if(isSafeSquare(size , row , col , Queens,board,region ,1) &&
        isRowSafe(size,row, 0,Queens) &&
        isColSafe(size, 0,col,Queens) &&
        region[(int)board[row][col]] == 0 ) {
        Queens[row][col] = 1;
        region[(int)board[row][col]] = 1;
        if (task4_queens_battle(size, 0,col + 1,Queens,board,region)) {
            return 1 ;
        }
        Queens[row][col] = 0;
        region[(int)board[row][col]] = 0;
    }
    return task4_queens_battle(size ,row +1 , col , Queens ,board , region);
}
void print_grid(char grid[MAX_SIZE][MAX_SIZE], int size, int row, int col) {
    if (row == size) {
        return;
    }
    if (col == size) {
        printf("\n");
        print_grid(grid, size, row + 1, 0);
        return;
    }
    printf("| ");
    printf("%c ", grid[row][col]);
    print_grid(grid, size, row, col + 1);
}

int can_place_word(char grid[MAX_SIZE][MAX_SIZE], char word[], int row, int col, int length, char direction, int idx) {
    if (direction == 'H') {
        if (col + length > MAX_SIZE) return 0;
        if (idx == length) return 1;
        if (grid[row][col + idx] == '#' || grid[row][col + idx] == word[idx]) {
            return can_place_word(grid, word, row, col, length, direction, idx + 1);
        }
        return 0;
    } else if (direction == 'V') {
        if (row + length > MAX_SIZE) return 0;
        if (idx == length) return 1;
        if (grid[row + idx][col] == '#' || grid[row + idx][col] == word[idx]) {
            return can_place_word(grid, word, row, col, length, direction, idx + 1);
        }
        return 0;
    }
    return 0;
}
void place_word(char grid[MAX_SIZE][MAX_SIZE], char word[], int row, int col, int length, char direction, int idx) {
    if (idx == length) return;

    if (direction == 'H') {
        grid[row][col + idx] = word[idx];
        place_word(grid, word, row, col, length, direction, idx + 1);
    } else if (direction == 'V') {
        grid[row + idx][col] = word[idx];
        place_word(grid, word, row, col, length, direction, idx + 1);
    }
}

void remove_word(char grid[MAX_SIZE][MAX_SIZE], int row, int col, int length, char direction, int idx) {
    if (idx == length) return;

    if (direction == 'H') {
        grid[row][col + idx] = '#';
        remove_word(grid, row, col, length, direction, idx + 1);
    } else if (direction == 'V') {
        grid[row + idx][col] = '#';
        remove_word(grid, row, col, length, direction, idx + 1);
    }
}
int solve_crossword_for_slot(char grid[MAX_SIZE][MAX_SIZE], Slots slots[], int slot_index, int num_slots, char words[MAX_SLOTS][MAX_LENGTH],
    int word_index[], int num_words, int row, int col, int length, char direction, int word_idx) {
    if (word_idx == num_words) {
        return 0; // No more words to try
    }
    if (word_index[word_idx] == 0 && (int)strlen( words[word_idx]) == length && can_place_word(grid, words[word_idx], row, col, length, direction, 0)) {
        place_word(grid, words[word_idx], row, col, length, direction, 0);
        word_index[word_idx] = 1; // Mark the word as used

        if (solve_crossword(grid, slots, slot_index + 1, num_slots, words, word_index, num_words)) {
            return 1;
        }
        remove_word(grid, row, col, length, direction, 0); // Backtrack
        word_index[word_idx] = 0; // Unmark the word as used
    }
    return solve_crossword_for_slot(grid, slots, slot_index, num_slots, words, word_index, num_words, row, col, length, direction, word_idx + 1);
}

int solve_crossword(char grid[MAX_SIZE][MAX_SIZE], Slots slots[], int slot_index, int num_slots, char words[MAX_SLOTS][MAX_LENGTH], int word_index[], int num_words) {
    if (slot_index == num_slots) {
        return 1; // All slots are filled
    }
    int row = slots[slot_index].row,length = slots[slot_index].length,col = slots[slot_index].col;
    char direction = slots[slot_index].direction;
    // Try each word in the dictionary
    return solve_crossword_for_slot(grid, slots, slot_index, num_slots, words, word_index, num_words, row, col, length, direction, 0);
}



