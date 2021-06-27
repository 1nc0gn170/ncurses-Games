#include <ncurses.h>
#include "game.h"

void initCurses() {

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

}

void drawBanner(int x,int y,char *banner){

	mvprintw(y, x, banner);
}

void announceStatus(char *msg){
	
	mvprintw(6, 12, msg);
	refresh();
	getch();	
	move(6, 0);
	clrtoeol();
	clearBoard();
}

void clearBoard(){

	int y,x;

	for (y = INIT_Y; y < END_Y; y+=JUMP_Y)
	{
		for (x = INIT_X; x < END_X; x+=JUMP_X)
		{
			mvaddch(y, x, ' ');
		}
	} 
	move(INIT_Y,INIT_X);
	refresh();
}

void drawBoard() {

	int y,x;

	for ( y = START_Y; y <= END_Y ; y++ ) {

		if ( y%4 == 0 ) {

			for ( x = START_X; x <= END_X; x++) {

				mvaddch(y, x, '-');
			}
		}

		else {
			mvaddch(y, 8, '|');
			mvaddch(y, 16, '|');
			mvaddch(y, 24, '|');
			mvaddch(y, 32,'|');
		}

	}

	move(INIT_Y,INIT_X);
	refresh();
}


void initBoard(char (*board)[3]) {

	int x,y;

	for(x=0; x<=2;x++){

		for(y=0; y<=2;y++){
			
			board[x][y] = '-';
		}	
	}

}

int startGame() {
	
	int input, temp_position, abs_x, abs_y, player = 1, moves = 0,restart = 0, lock = 0;
	char board[3][3];
	int position_X = INIT_X;
	int position_Y = INIT_Y;


	initBoard(board);

	while (input != END){
		
		input = getch();

		if (input == ' '){

			abs_x = (position_X / 8) - 1;
			abs_y = (position_Y == 10) ? 0 : ((position_Y == 14) ? 1 : 2);

			if (checkVacant(board,abs_x, abs_y)){


				if (player == 1){

					mvaddch(position_Y,position_X, 'X');
					board[abs_x][abs_y] = 'X';

					if (checkWin(board,'X')){
						announceStatus("Player 1 Won(X) !!!");
						restart = TRUE;
						lock = 1;
					}
					player = 2;
				}

				else{

					mvaddch(position_Y,position_X, 'O');
					board[abs_x][abs_y] = 'O';

					if (checkWin(board,'O')){
						announceStatus("Player 2 Won(O) !!!");
						restart = TRUE;
						lock = 1;
					}
					player = 1;
				}

				refresh();
				moves++;

				if (moves == MAX_MOVES || restart){

					if (moves == MAX_MOVES && !lock)
						announceStatus("Hehe.. Game Tie !!!");

					initBoard(board);
					player = 1;
					moves = restart = lock = 0;
					position_X = INIT_X;
					position_Y = INIT_Y;

				}


			}
			else {
				continue;
			}

		}

		else{

			switch (input){

				case KEY_DOWN:
					temp_position = position_Y + JUMP_Y;
					if (temp_position >= START_Y && temp_position < END_Y) 
						move(position_Y += JUMP_Y, position_X);
					break;

				case KEY_UP:
					temp_position = position_Y - JUMP_Y;
					if (temp_position >= START_Y && temp_position <= END_Y) 
						move(position_Y -= JUMP_Y, position_X);
					break;

				case KEY_LEFT:
					temp_position = position_X - JUMP_X;
					if (temp_position >= START_X && temp_position <= END_X) 
						move(position_Y, position_X -= JUMP_X);
					break;

				case KEY_RIGHT:
					temp_position = position_X + JUMP_X;
					if (temp_position >= START_X && temp_position <= END_X) 
						move(position_Y, position_X += JUMP_X);
					break;
			
			}

		}

	}

	endwin();
	return FALSE;
}

int checkVacant(char (*board)[3], int x, int y){

	if (board[x][y] == '-')
		return TRUE;

	return FALSE;
}

int checkWin(char (*board)[3], char label){

	int i;

	for (i = 0; i < 3; ++i)
	{
		if (board[i][0] == label && board[i][1] == label && board[i][2] == label){
			return TRUE;
		}

		else if (board[0][i] == label && board[1][i] == label && board[2][i] == label){
			return TRUE;
		}
	}

	if ((board[0][0] == label && board[2][2] == label) || (board[0][2] == label && board[2][0] == label)){
		if (board[1][1] == label)
			return TRUE;
	}

	return FALSE;

}



int tiktactoe(){

	char* banner = "  _____ _ _      _____            _____          \n |_   _(_) | __ |_   _|_ _  ___  |_   _|__   ___ \n   | | | | |/ /   | |/ _` |/ __|   | |/ _ \\ / _ \\\n   | | | |   <    | | (_| | (__    | | (_) |  __/\n   |_| |_|_|\\_\\   |_|\\__,_|\\___|   |_|\\___/ \\___|\n                                                 \n                                                  ";

	do {

		initCurses();
		drawBanner(0,0,banner);
		drawBoard();

	} while (startGame());

	printf("Thanks for playing!!!\n");

	endwin();
	return 0;
}
	