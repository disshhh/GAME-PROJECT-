#ifndef CONNECTGAME_H
#define C_ROWS 6
#define C_COLS 7

extern char C_board[C_ROWS][C_COLS];

void CONinitializeBoard();
void CONprintBoard();
int CONisValidMove(int col);
void CONplayerMove();
int CONisBoardFull();
int CONcheckWin(char player);
int CONevaluatePosition();
int CONminimax(int depth, int isMaximizing);
int CONfindBestMove();

#endif