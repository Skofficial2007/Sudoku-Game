#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int puzzle[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0}};

int number[9][9];

int copy[9][9];
int num, count = 0, choice;
int x = 0, y = 0, a = 0, b = 0;
int filledX[50], filledY[50];

int valid(int copy[][9], int row, int column, int guess);
int find_empty_cell(int copy[][9], int *row, int *column);
int solve(int copy[][9]);
void SolvedPuzzle(int copy[][9]);
void emptySudoku(int puzzle[][9]);
void Add_Element_Randomly(int count, int puzzle[][9]);
void copyPuzzle(int puzzle[][9], int copy[][9]);
void resetPuzzle(int puzzle[][9], int copy[][9], int number[][9]);
void emptySpace();
void enterPos(int puzzle[][9], int *, int *);
void enterValue();
int isValid();
void FillnumInSudoku();
void printNewNumberInSudoku();
int deleteElement();
void enterPos_toDelete(int puzzle[][9], int *t1, int *t2);
int mainGame(int choice);
void printStatements();
void DefaultBoards();

int main()
{
    DefaultBoards();
    printStatements();
    mainGame(choice);

    return 0;
}

// To reset the puzzle to a default sudoku in case randomized sudoku is unsolvable
void resetPuzzle(int puzzle[][9], int copy[][9], int number[][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            puzzle[i][j] = number[i][j];
            copy[i][j] = puzzle[i][j];
        }
    }
}

// To make a copy of puzzle to be used in solve function
void copyPuzzle(int puzzle[][9], int copy[][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            copy[i][j] = puzzle[i][j];
        }
    }
}

// To check if guessed number is valid to enter at position
int valid(int copy[][9], int row, int column, int guess)
{
    int corner_x = (row/3)*3;
    int corner_y = (column/3)*3;

    for(int i = 0; i < 9; i++)
    {
        if(copy[row][i] == guess)
            return 0;
        if(copy[i][column] == guess)
            return 0;
        if(copy[corner_x + (i % 3)][corner_y + (i / 3)] == guess)
            return 0;
    }

    return 1;
}

// To find a empty location
int find_empty_cell(int copy[][9], int *row, int *column)
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(copy[i][j] == 0)
            {
                *row = i;
                *column = j;

                return 1;
            }
        }
    }

    return 0;
}

// To solve the sudoku
int solve(int copy[][9])
{
    int row, column;

    // If find_empty_cell returned 0 means the sudoku is completely filled
    if(!find_empty_cell(copy, &row, &column))
        return 1;
    
    for(int guess = 1; guess < 10; guess++)
    {
        if(valid(copy, row, column, guess))
        {
            copy[row][column] = guess;

            if(solve(copy))
                return 1;
            copy[row][column] = 0;
        }
    }

    return 0;
}

// To print empty sudoku to be filled by the user
void emptySudoku(int puzzle[][9])
{
    printf("\n\n");
    char ch = 196;

    printf("         1  2  3     4  5  6     7  8  9  \n");
    printf("      ------------------------------------\n");
    for(int i = 0; i < 9; i++)
    {
        printf("[%d]  || ", i+1);
        for(int j = 0; j < 9; j++)
        {
            if(j == 2 || j == 5 || j == 8)
            {
                if(puzzle[i][j] == 0)
                    printf(" %c || ", ch);
                else
                    printf(" %d || ", puzzle[i][j]);
            }
            else
            {
                if(puzzle[i][j] == 0)
                    printf(" %c ", ch);
                else
                    printf(" %d ", puzzle[i][j]);
            }
        }
        printf("\n");
        if(i == 2 || i == 5 || i == 8)
        {
            printf("      ------------------------------------\n");
        }
    }

    printf("\n\n");
}

// To print the solved sudoku if the person is failed to complete it
void SolvedPuzzle(int copy[][9])
{
    printf("\n\nYour Puzzle is: \n\n");
    printf("         1  2  3     4  5  6     7  8  9  \n");
    printf("      ------------------------------------\n");
    for(int i = 0; i < 9; i++)
    {
        printf("[%d]  || ", i+1);
        for(int j = 0; j < 9; j++)
        {
            if(j == 2 || j == 5 || j == 8)
            {
                printf(" %d || ", copy[i][j]);
            }
            else
            {
                printf(" %d ", copy[i][j]);
            }
        }
        printf("\n");
        if(i == 2 || i == 5 || i == 8)
        {
            printf("      ------------------------------------\n");
        }
    }

    char ch;
    scanf("%c",&ch);
    printf("\n\n");
}

// To make totally randomized sudoku
void Add_Element_Randomly(int count, int puzzle[][9])
{
    int i, j, num = 0;
    srand(time(NULL));

    while(count != 0)
    {
        i = rand()%9;
        j = rand()%9;

        while(puzzle[i][j] != 0)
        {
            i = rand()%9;
            j = rand()%9;
        }

        while(num == 0)
            num = rand()%10;
        
        while(!valid(puzzle, i, j, num))
        {
            num = rand()%10;
        }

        puzzle[i][j] = num;

        count--;
    }
}

// To store number of empty cells and location at which default elements was present
void emptySpace()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(puzzle[i][j] == 0)
                count++;
            else
            {
                filledX[a] = i;
                filledY[b] = j;
                a++;
                b++;
            }
        }
    }
}

// To input and check position where user want to enter number is valid to enter or not
void enterPos(int puzzle[][9], int *t1, int *t2)
{
    int x, y;
    printf("\nEnter position of array where you want to input (x, y) [1 to 9]: ");
    scanf("%d %d", &x, &y);
    x -= 1;
    y -= 1;
    while((x < 0 || x > 8 || y > 8 || y < 0) || puzzle[x][y] != 0)
    {
        printf("\nInvalid Input\n");
        printf("\nEnter a new position where you want to input number (x, y) [1 to 9]: ");
        scanf("%d %d", &x, &y);
        x -= 1;
        y -= 1;
    }

    *t1 = x;
    *t2 = y;
}

// To input a number to enter from user
void enterValue()
{
    printf("\nEnter your choice of number you want to enter: ");
    scanf("%d", &num);
    while((num < 1 || num > 9))
    {
        printf("\nInvalid Input\n");
        printf("\nEnter a different number you want to enter: ");
        scanf("%d", &num);
    }
}

// isValid function specially to handle input and check validation
int isValid()
{
    enterValue();
    int flag = 0;

    int row = x;
    int col = y;

    int startRow, startCol;

    startRow = floor(row / 3) * 3;
    startCol = floor(col / 3) * 3;

    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (puzzle[i][j] == num)
            {
                printf("\nThis Element already exist in that box\n");
                flag++;
            }
        }
    }

    for(int j = 0; j < 9; j++)
    {
        if(puzzle[row][j] == num)
        {
            printf("\nThis Element already exist in that row\n");
            flag++;
        }
    }

    for(int i = 0; i < 9; i++)
    {
        if(puzzle[i][col] == num)
        {
            printf("\nThis Element already exist in that column\n");
            flag++;
        }
    }

    return flag;
}

// To print a new sudoku with inputed number
void FillnumInSudoku()
{
    printf("\n\n");
    char ch = 196;
    char cnum = num + 48;

    printf("         1  2  3     4  5  6     7  8  9  \n");
    printf("      ------------------------------------\n");
    for(int i = 0; i < 9; i++)
    {
        printf("[%d]  || ", i+1);
        for(int j = 0; j < 9; j++)
        {
            if(j == 2 || j == 5 || j == 8)
            {
                if(puzzle[i][j] == 0)
                {
                    if(i == x && j == y)
                        printf(" %c || ", cnum);
                    else
                        printf(" %c || ", ch);
                }
                else
                {
                    printf(" %d || ", puzzle[i][j]);
                }
            }
            else
            {
                if(puzzle[i][j] == 0)
                {
                    if(i == x && j == y)
                        printf(" %c ", cnum);
                    else
                        printf(" %c ", ch);
                }
                else
                {
                    printf(" %d ", puzzle[i][j]);
                }
            }
        }
        printf("\n");
        if(i == 2 || i == 5 || i == 8)
        {
            printf("      ------------------------------------\n");
        }
    }

    printf("\n\n");
    count--;

    puzzle[x][y] = num;
}

// To print the new number in sudoku
void printNewNumberInSudoku()
{
    enterPos(puzzle, &x, &y);
    int flag = isValid();
    while(flag != 0)
    {
        flag = isValid();
    }
    FillnumInSudoku();
}

// Function to delete the entered elements
int deleteElement()
{
    enterPos_toDelete(puzzle, &x, &y);
    for(int i = 0; i < a; i++)
    {
        if(x == filledX[i] && y == filledY[i])
        {
            printf("\nThat's a default element you can't delete it\n");
            deleteElement();
            return 0;
        }
    }
    if(puzzle[x][y] == 0)
    {
        printf("\nThere is no element at (%d, %d)\n", x+1, y+1);
        deleteElement();
        return 0;
    }
    puzzle[x][y] = 0;
    printf("\nElement is Deleted\n\n");
    emptySudoku(puzzle);
    return 0;
}

// Had to create a enterPos_toDelete element function as previous one will not work with it
void enterPos_toDelete(int puzzle[][9], int *t1, int *t2)
{
    int x, y;
    printf("\nEnter position of array where you want to input (x, y) [1 to 9]: ");
    scanf("%d %d", &x, &y);
    x -= 1;
    y -= 1;
    while((x < 0 || x > 8 || y > 8 || y < 0))
    {
        printf("\nInvalid Input\n");
        printf("\nEnter a new position where you want to input number (x, y) [1 to 9]: ");
        scanf("%d %d", &x, &y);
        x -= 1;
        y -= 1;
    }

    *t1 = x;
    *t2 = y;
}

// To print basic rules and set up the overall game 
void printStatements()
{
    printf("\n\n\t\t---WELCOME TO SUDOKU---\n\n");
    printf("Here are some basic rules to play sudoku: \n\n");
    printf("RULE 1. You can use only numbers from 1 to 9.\n\n");
    printf("RULE 2. Each 3x3 block can only contain numbers from 1 to 9.\n\n");
    printf("RULE 3. Each vertical column can only contain numbers from 1 to 9.\n\n");
    printf("RULE 4. Each horizontal row can only contain numbers from 1 to 9.\n\n");
    printf("RULE 5. Each number in the 3x3 block, vertical column or horizontal row can be used only once.\n\n");
    printf("RULE 6. The game is over when the whole Sudoku grid is correctly filled with numbers.\n\n");

    printf("\n\nPress any key to continue: ");
    getchar();
    system("cls");

    printf("\n\n\t\t---How To Play Sudoku---\n\n");
    printf("\n-> Enter a certain position where you want to enter a number.\n");
    printf("\n-> How to check which position.\n");
    printf("\n-> Use the grid numbers provided in given sudoku and enter postion according to them.\n");
    printf("\n-> Same steps to delete a element.\n");
    printf("\n-> If you decide to see solution then what?\n");
    printf("\n-> If you do so game will end.\n");
    printf("\n\n\t\t---That's It Enjoy The Game---\n\n");
    printf("\n\nPress any key to continue: ");
    getchar();
    system("cls");

    Add_Element_Randomly(25, puzzle);
    copyPuzzle(puzzle, copy);

    // To check if the randomized sudoku is solveable or not
    while(1)
    {
        if(solve(copy))
        {
            break;
        }
        else
        {
            resetPuzzle(puzzle, copy, number);
        }
    }

    emptySpace();
    
    printf("\n\n---------------------------");
    printf("\n\nPress any key to Start");
    printf("\n\n---------------------------");
    printf("\n\nHere -> ");
    getchar();
    system("cls");
}

// Main game loop
int mainGame(int choice)
{
    system("cls");
    emptySudoku(puzzle);
    printNewNumberInSudoku();
    while(count != 0)
    {
        printf("\nDo you want to continue\n");
        printf("\nEnter from these choices: \n");
        printf("\n1. Yes, To enter a new element\n");
        printf("\n2. Yes, But to delete a element\n");
        printf("\n3. I want to see the sudoku once again\n");
        printf("\n4. I give up!!, I want it's Solution\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        system("cls");
        
        switch(choice)
        {
            case 1:
            {
                system("cls");
                emptySudoku(puzzle);
                printNewNumberInSudoku();
                break;
            }
            case 2:
            {
                system("cls");
                emptySudoku(puzzle);
                deleteElement();
                break;
            }
            case 3:
            {
                system("cls");
                emptySudoku(puzzle);
                break;
            }
            case 4:
            {
                system("cls");
                SolvedPuzzle(copy);
                printf("\n\nPress any key to EXIT: ");
                getchar();
                exit(1);
            }
            default:
            {
                printf("Invalid Input");
                break;
            }
        }
    }

    if(count == 0)
    {
        printf("\t\t!!!Congratulations!!!\t\t\n\n\t\t       YOU WON      \t\t\n\n");
    }
    
    return 0;
}

// To set puzzle to any of the default board in case randomization failed
void DefaultBoards()
{
    int board1[9][9] = {{6, 0, 1, 0, 0, 8, 0, 0, 9},
                        {0, 0, 0, 0, 0, 0, 0, 2, 0},
                        {0, 0, 7, 0, 1, 0, 3, 0, 0},
                        {0, 0, 0, 0, 0, 5, 0, 0, 0},
                        {0, 2, 0, 4, 0, 0, 0, 8, 0},
                        {3, 0, 0, 0, 0, 0, 9, 0, 0},
                        {0, 7, 0, 2, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 6, 0, 0, 1, 0},
                        {0, 1, 0, 0, 0, 0, 7, 0, 8}};

    int board2[9][9] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                        {6, 0, 0, 1, 9, 5, 0, 0, 0},
                        {0, 9, 8, 0, 0, 0, 0, 6, 0},
                        {8, 0, 0, 0, 6, 0, 0, 0, 3},
                        {4, 0, 0, 8, 0, 3, 0, 0, 1},
                        {7, 0, 0, 0, 2, 0, 0, 0, 6},
                        {0, 6, 0, 0, 0, 0, 2, 8, 0},
                        {0, 0, 0, 4, 1, 9, 0, 0, 5},
                        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    int board3[9][9] = {{0, 0, 0, 2, 0, 0, 7, 0, 1},
                        {6, 8, 0, 0, 7, 0, 0, 9, 0},
                        {1, 0, 0, 0, 0, 4, 5, 0, 0},
                        {8, 2, 0, 1, 0, 0, 0, 4, 0},
                        {0, 0, 4, 6, 0, 2, 9, 0, 0},
                        {0, 5, 0, 0, 0, 3, 0, 0, 8},
                        {0, 0, 9, 3, 0, 0, 0, 7, 4},
                        {0, 4, 0, 0, 0, 0, 0, 3, 6},
                        {7, 0, 3, 0, 1, 8, 0, 0, 0}};

    int r;
    srand(time(NULL));
    do
    {
        r = rand()%4;
    } while (r < 1);

    switch(r)
    {
        case 1:
        {
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    number[i][j] = board1[i][j];
                }
            }
            break;
        }
        case 2:
        {
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    number[i][j] = board2[i][j];
                }
            }
            break;
        }
        case 3:
        {
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    number[i][j] = board3[i][j];
                }
            }
            break;
        }
        default:
        {
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    number[i][j] = board3[i][j];
                }
            }
            break;
        }
    }
}
