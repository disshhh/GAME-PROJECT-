#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connectgame.h"

char C_board[C_ROWS][C_COLS];

void CONinitializeBoard()
{
    for (int i = 0; i < C_ROWS; ++i)
    {
        for (int j = 0; j < C_COLS; ++j)
        {
            C_board[i][j] = ' ';
        }
    }
}

void CONprintBoard()
{
    for (int i = 0; i < C_ROWS; ++i)
    {
        for (int j = 0; j < C_COLS; ++j)
        {
            printf("| %c ", C_board[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
}

int CONisValidMove(int col)
{
    return (col >= 0 && col < C_COLS && C_board[0][col] == ' ');
}

void CONplayerMove()
{
    int col;
    do
    {
        printf("Enter your move (0-6): ");
        scanf("%d", &col);
    } while (!CONisValidMove(col));

    for (int i = C_ROWS - 1; i >= 0; --i)
    {
        if (C_board[i][col] == ' ')
        {
            C_board[i][col] = 'X';
            break;
        }
    }
}

int CONisBoardFull()
{
    for (int i = 0; i < C_COLS; ++i)
    {
        if (C_board[0][i] == ' ')
        {
            return 0;
        }
    }
    return 1;
}

int CONcheckWin(char player)
{
    // Check for a win in C_rows
    for (int i = 0; i < C_ROWS; ++i)
    {
        for (int j = 0; j <= C_COLS - 4; ++j)
        {
            if (C_board[i][j] == player && C_board[i][j + 1] == player && C_board[i][j + 2] == player && C_board[i][j + 3] == player)
            {
                return 1;
            }
        }
    }

    // Check for a win in columns
    for (int i = 0; i <= C_ROWS - 4; ++i)
    {
        for (int j = 0; j < C_COLS; ++j)
        {
            if (C_board[i][j] == player && C_board[i + 1][j] == player && C_board[i + 2][j] == player && C_board[i + 3][j] == player)
            {
                return 1;
            }
        }
    }

    // Check for a win in diagonals (positive slope)
    for (int i = 0; i <= C_ROWS - 4; ++i)
    {
        for (int j = 0; j <= C_COLS - 4; ++j)
        {
            if (C_board[i][j] == player && C_board[i + 1][j + 1] == player && C_board[i + 2][j + 2] == player && C_board[i + 3][j + 3] == player)
            {
                return 1;
            }
        }
    }

    // Check for a win in diagonals (negative slope)
    for (int i = 0; i <= C_ROWS - 4; ++i)
    {
        for (int j = 3; j < C_COLS; ++j)
        {
            if (C_board[i][j] == player && C_board[i + 1][j - 1] == player && C_board[i + 2][j - 2] == player && C_board[i + 3][j - 3] == player)
            {
                return 1;
            }
        }
    }

    return 0;
}

int CONevaluatePosition()
{
    if (CONcheckWin('X'))
    {
        return -1; // Player wins
    }
    else if (CONcheckWin('O'))
    {
        return 1; // Computer wins
    }
    else
    {
        return 0; // Draw
    }
}

int CONminimax(int depth, int isMaximizing)
{
    if (depth == 0 || CONisBoardFull())
    {
        return CONevaluatePosition();
    }

    if (isMaximizing)
    {
        int maxEval = -1000;
        for (int i = 0; i < C_COLS; ++i)
        {
            if (CONisValidMove(i))
            {
                for (int j = C_ROWS - 1; j >= 0; --j)
                {
                    if (C_board[j][i] == ' ')
                    {
                        C_board[j][i] = 'O';
                        int eval = CONminimax(depth - 1, 0);
                        C_board[j][i] = ' '; // Undo the move
                        maxEval = (eval > maxEval) ? eval : maxEval;
                        break;
                    }
                }
            }
        }
        return maxEval;
    }
    else
    {
        int minEval = 1000;
        for (int i = 0; i < C_COLS; ++i)
        {
            if (CONisValidMove(i))
            {
                for (int j = C_ROWS - 1; j >= 0; --j)
                {
                    if (C_board[j][i] == ' ')
                    {
                        C_board[j][i] = 'X';
                        int eval = CONminimax(depth - 1, 1);
                        C_board[j][i] = ' '; // Undo the move
                        minEval = (eval < minEval) ? eval : minEval;
                        break;
                    }
                }
            }
        }
        return minEval;
    }
}

int CONfindBestMove()
{
    int bestVal = -1000;
    int bestMove = -1;

    for (int i = 0; i < C_COLS; ++i)
    {
        if (CONisValidMove(i))
        {
            for (int j = C_ROWS - 1; j >= 0; --j)
            {
                if (C_board[j][i] == ' ')
                {
                    C_board[j][i] = 'O';
                    int moveVal = CONminimax(4, 0); // Adjust the depth for higher difficulty
                    C_board[j][i] = ' ';            // Undo the move

                    if (moveVal > bestVal)
                    {
                        bestMove = i;
                        bestVal = moveVal;
                    }
                    break;
                }
            }
        }
    }
    return bestMove;
}

/*
int main()
{
    srand(time(NULL));

    CONinitializeBoard();
    CONprintBoard();

    while (1)
    {
        // Player's move
        CONplayerMove();
        CONprintBoard();
        if (CONcheckWin('X'))
        {
            printf("Congratulations! You win!\n");
            break;
        }
        else if (CONisBoardFull())
        {
            printf("It's a draw!\n");
            break;
        }

        // Computer's move
        int computerMoveCol = CONfindBestMove();
        printf("Computer's move: %d\n", computerMoveCol);
        for (int i = C_ROWS - 1; i >= 0; --i)
        {
            if (C_board[i][computerMoveCol] == ' ')
            {
                C_board[i][computerMoveCol] = 'O';
                break;
            }
        }

        CONprintBoard();
        if (CONcheckWin('O'))
        {
            printf("Sorry, you lose. Try again!\n");
            break;
        }
        else if (CONisBoardFull())
        {
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}
*/