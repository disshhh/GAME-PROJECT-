#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connect.h"

// #define C_ROWS 6
// #define C_COLS 7

// char board[C_ROWS][C_COLS];
// int currentPlayer = 1;

void printConBoard()
{
    system("cls"); // For Windows, use "cls" instead of "clear"
    printf("\n");
    for (int i = 0; i < C_ROWS; i++)
    {
        printf("|");
        for (int j = 0; j < C_COLS; j++)
        {
            if (board[i][j] == 'X')
            {
                printf(" \033[1;31mX\033[0m |"); // Red for Player X
            }
            else if (board[i][j] == 'O')
            {
                printf(" \033[1;33mO\033[0m |"); // Yellow for Player O (Computer)
            }
            else
            {
                printf("   |");
            }
        }
        printf("\n");
        printf("|");
        for (int j = 0; j < C_COLS; j++)
        {
            printf("---|");
        }
        printf("\n");
    }
    printf("  1   2   3   4   5   6   7 \n");
}

int ConcheckWin(char player)
{
    for (int i = 0; i < C_ROWS; i++)
    {
        for (int j = 0; j < C_COLS; j++)
        {
            if (board[i][j] == player)
            {
                if (j <= C_COLS - 4)
                {
                    if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3])
                    {
                        return 1;
                    }
                }
                if (i <= C_ROWS - 4)
                {
                    if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j])
                    {
                        return 1;
                    }
                }
                if (i <= C_ROWS - 4 && j <= C_COLS - 4)
                {
                    if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3])
                    {
                        return 1;
                    }
                }
                if (i >= 3 && j <= C_COLS - 4)
                {
                    if (board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] && board[i][j] == board[i - 3][j + 3])
                    {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void ConplayerMove()
{
    int col;
    do
    {
        printf("Player's turn (X). Enter column (1-7): ");
        scanf("%d", &col);
        col--;                                                  // Adjusting to array indexing (0-based)
    } while (col < 0 || col >= C_COLS || board[0][col] != ' '); // Check for valid column and availability
    for (int i = C_ROWS - 1; i >= 0; i--)
    {
        if (board[i][col] == ' ')
        {
            board[i][col] = 'X';
            break;
        }
    }
}

int ConcheckPotentialWin(char player)
{
    for (int j = 0; j < C_COLS; j++)
    {
        if (board[C_ROWS - 1][j] == ' ')
        {
            board[C_ROWS - 1][j] = player; // Simulate placing token at the bottom of the column

            if (board[0][j] != ' ') // If the column is full, move on to the next column
            {
                board[C_ROWS - 1][j] = ' '; // Undo the move
                continue;
            }

            int winRow = C_ROWS - 1;

            while (winRow >= 3)
            {
                if ((board[winRow][j] == player) &&
                    ((board[winRow - 1][j] == player && board[winRow - 2][j] == player && board[winRow - 3][j] == ' ') ||
                     (j >= 3 && board[winRow - 1][j - 1] == player && board[winRow - 2][j - 2] == player && board[winRow - 3][j - 3] == ' ') ||
                     (j <= C_COLS - 4 && board[winRow - 1][j + 1] == player && board[winRow - 2][j + 2] == player && board[winRow - 3][j + 3] == ' ')))
                {
                    board[C_ROWS - 1][j] = ' '; // Undo the move
                    return j;                   // Block the player from winning in this column
                }
                winRow--;
            }

            board[C_ROWS - 1][j] = ' '; // Undo the move
        }
    }
    return -1; // No immediate threat detected
}

void ConcomputerMove()
{
    int playerWinCol = ConcheckPotentialWin('X'); // Check if player can win in next move
    if (playerWinCol != -1)
    {
        for (int i = C_ROWS - 1; i >= 0; i--)
        {
            if (board[i][playerWinCol] == ' ')
            {
                board[i][playerWinCol] = 'O'; // Block the player's winning move
                return;
            }
        }
    }

    int winCol = ConcheckPotentialWin('O'); // Check if computer can win in next move
    if (winCol != -1)
    {
        for (int i = C_ROWS - 1; i >= 0; i--)
        {
            if (board[i][winCol] == ' ')
            {
                board[i][winCol] = 'O'; // Make the winning move
                return;
            }
        }
    }

    // If no immediate win/block is possible, make a random valid move
    srand(time(NULL));
    int col;
    do
    {
        col = rand() % C_COLS;
    } while (board[0][col] != ' ');
    for (int i = C_ROWS - 1; i >= 0; i--)
    {
        if (board[i][col] == ' ')
        {
            board[i][col] = 'O';
            break;
        }
    }
}

/*
int main()
{
    for (int i = 0; i < C_ROWS; i++)
    {
        for (int j = 0; j < C_COLS; j++)
        {
            board[i][j] = ' '; // Change 0 to ' '
        }
    }
    while (1)
    {
        printConBoard();
        if (currentPlayer == 1)
        {
            ConplayerMove();
        }
        else
        {
            ConcomputerMove();
        }
        if (ConcheckWin('X'))
        {
            printConBoard(); // Print final board before declaring winner
            printf("Player (X) wins!\n");
            break;
        }
        else if (ConcheckWin('O'))
        {
            printConBoard(); // Print final board before declaring winner
            printf("Computer (O) wins!\n");
            break;
        }
        currentPlayer = 3 - currentPlayer;
    }
    return 0;
}
*/