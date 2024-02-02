#ifndef TICTACTOE_H
#define TICTACTOE_H

#define T_SIZE 3
#define T_MAX 1000
#define T_MIN -1000

extern char T_board[T_SIZE][T_SIZE];
extern char T_humanPlayer;
extern char T_computerPlayer;

int T_isValidMove(int row, int col);
int T_isGameOver();
int T_evaluate();
int T_miniT_max(int depth, int isT_Max);
void T_computerMove();
void printT_Board();
#endif