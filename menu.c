int CHOICE = 0;
int DIFFICULTY = 0;
int SPEED = 25;
/*
DIFFICULTY 0 -> EASY
DIFFICULTY 1 -> MEDIUM
DIFFICULTY 2 -> HARD
*/

void PrintMenu(){
                        

	mvprintw(0, 0, " _____            _           _____                  ");
	mvprintw(1, 0, "|   __| ___  ___ | |_  ___   |   __| ___  _____  ___ ");
	mvprintw(2, 0, "|__   ||   || .'|| '_|| -_|  |  |  || .'||     || -_|");
	mvprintw(3, 0, "|_____||_|_||__,||_,_||___|  |_____||__,||_|_|_||___|");
	
	mvprintw(5, 2, "1 - Play");
	mvprintw(6, 2, "2 - Ranking");
	mvprintw(7, 2, "3 - Quit");
	
	mvprintw(9, 2, "Enter your choice: ");

	if(CHOICE == 0) scanw("%d", &CHOICE);
	else mvprintw(9, 2, "Enter your choice: %d", CHOICE);

	switch(CHOICE){
		case 1:
			mvprintw(11, 2, "1 - EASY");
			mvprintw(12, 2, "2 - MEDIUM");
			mvprintw(13, 2, "3 - HARD");
			mvprintw(15, 2, "Choose the difficulty: ");
			scanw("%d", &DIFFICULTY);

			switch(DIFFICULTY){
				case 1:
					SPEED = 16;
					MENU = 0;
					break;
				case 2:
					SPEED = 10;
					MENU = 0;
					break;
				case 3:
					SPEED = 5;
					MENU = 0;
					break;
			}
			clear();
			break;
		case 2:
			
			break;
		case 3:
			nodelay(stdscr, TRUE);
			END = 1;
			break;
	}
}