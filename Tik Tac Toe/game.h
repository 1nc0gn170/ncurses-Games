#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define MAX_MOVES 9

#define START_X 8
#define END_X 32

#define START_Y 8
#define END_Y 20

#define INIT_X 12
#define INIT_Y 10

#define JUMP_X  8
#define JUMP_Y  4

#define END 27


int startGame();
int tiktactoe();
void drawBoard();
void initCurses();
void clearBoard();
void initBoard(char boardData[3][3]);
void drawBanner(int x,int y,char *banner);
int checkWin(char (*board)[3], char label);
int checkVacant(char (*board)[3], int x, int y);