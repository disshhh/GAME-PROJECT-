#ifndef CONNECT_H
#define CONNECT_H

#define C_ROWS 6
#define C_COLS 7

extern char board[C_ROWS][C_COLS];
extern int currentPlayer;

int ConcheckWin(char player);
void ConplayerMove();
int ConcheckPotentialWin(char player);
void ConcomputerMove();
#endif