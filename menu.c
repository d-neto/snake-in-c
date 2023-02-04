
/*
	DIFFICULTY 0 -> EASY
	DIFFICULTY 1 -> MEDIUM
	DIFFICULTY 2 -> HARD
	*/
int DIFFICULTY = 0;
int CHOICE = 0;

void Alert(int x, int y, char * text){
	attron(COLOR_PAIR(2));
	attron(A_BOLD);
	mvprintw(y, x, "%s", text);
	attroff(A_BOLD);
	attroff(COLOR_PAIR(11));
}

int PrintMenu(){
    clear();     
	cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(FALSE);

	attron(A_BOLD);
	attron(COLOR_PAIR(9));
	mvprintw(0, 1, " _____            _           _____                  ");
	mvprintw(1, 1, "|   __| ___  ___ | |_  ___   |   __| ___  _____  ___ ");
	mvprintw(2, 1, "|__   ||   || .'|| '_|| -_|  |  |  || .'||     || -_|");
	mvprintw(3, 1, "|_____||_|_||__,||_,_||___|  |_____||__,||_|_|_||___| v1.1");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(9));

	attron(COLOR_PAIR(8));
	attron(A_BOLD);
	mvprintw(5, 2, ">>");
	
	mvprintw(5, 6, "Play");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(8));

	mvprintw(6, 6, "Quit");
	
	// mvprintw(9, 2, "Enter your choice: \n");
	// mvprintw(9, 21, "");

	// if(CHOICE == 0) scanw("%d", &CHOICE);
	// else mvprintw(9, 2, "Enter your choice: %d", CHOICE);


	int max_choices = 2;
	int ch = getch();

	if(ch == 258)
		CHOICE++;
	if(ch == 259)
		CHOICE--;

	if(CHOICE < 0) CHOICE = 1;
		if(CHOICE > max_choices - 1) CHOICE = 0;

	switch(CHOICE){
		case 0:
			attron(COLOR_PAIR(8));
			attron(A_BOLD);
			mvprintw(5, 2, ">>");
			
			mvprintw(5, 6, "Play");
			attroff(A_BOLD);
			attroff(COLOR_PAIR(8));

			mvprintw(6, 0, "\n");
			mvprintw(6, 6, "Quit");
			break;
		case 1:
			attron(COLOR_PAIR(8));
			attron(A_BOLD);
			mvprintw(6, 2, ">>");

			mvprintw(6, 6, "Quit");

			attroff(A_BOLD);
			attroff(COLOR_PAIR(8));
			
			mvprintw(5, 0, "\n");
			mvprintw(5, 6, "Play");
			break;
	}



	while(ch != 10){
		ch = getch();
		if(ch == 258)
			CHOICE++;
		if(ch == 259)
			CHOICE--;

		if(CHOICE < 0) CHOICE = max_choices - 1;
		if(CHOICE > max_choices - 1) CHOICE = 0;

		switch(CHOICE){
			case 0:
				attron(COLOR_PAIR(8));
				attron(A_BOLD);
				mvprintw(5, 2, ">>");
				
				mvprintw(5, 6, "Play");
				attroff(A_BOLD);
				attroff(COLOR_PAIR(8));

				mvprintw(6, 0, "\n");
				mvprintw(6, 6, "Quit");
				break;
			case 1:
				attron(COLOR_PAIR(8));
				attron(A_BOLD);
				mvprintw(6, 2, ">>");

				mvprintw(6, 6, "Quit");

				attroff(A_BOLD);
				attroff(COLOR_PAIR(8));
				
				mvprintw(5, 0, "\n");
				mvprintw(5, 6, "Play");
				break;
		}

	}


	
	if(CHOICE == 1){
		END = TRUE;
		MENU = FALSE;
		return 0;
	}

	max_choices = 3;
	DIFFICULTY = 0;
	mvprintw(5, 0, "\n");
	mvprintw(6, 0, "\n");
	mvprintw(5, 2, "Choose the difficulty: ");

	attron(COLOR_PAIR(8));
	attron(A_BOLD);
	mvprintw(7, 2, ">>");
	
	mvprintw(7, 6, "EASY");
	
	attroff(A_BOLD);
	attroff(COLOR_PAIR(8));

	mvprintw(8, 6, "NORMAL");
	mvprintw(9, 6, "HARD");

	ch = getch();
	if(ch == 258)
		DIFFICULTY++;
	if(ch == 259)
		DIFFICULTY--;

	if(DIFFICULTY < 0) DIFFICULTY = max_choices - 1;
	if(DIFFICULTY > max_choices - 1) DIFFICULTY = 0;


	switch(DIFFICULTY){
		case 0:
			attron(COLOR_PAIR(8));
			attron(A_BOLD);
			mvprintw(7, 2, ">>");
			
			mvprintw(7, 6, "EASY");
			
			attroff(A_BOLD);
			attroff(COLOR_PAIR(8));

			mvprintw(8, 0, "\n");
			mvprintw(9, 0, "\n");
			mvprintw(8, 6, "NORMAL");
			mvprintw(9, 6, "HARD");
			break;
		case 1:
			attron(COLOR_PAIR(8));
			attron(A_BOLD);
			mvprintw(8, 2, ">>");
			
			mvprintw(8, 6, "NORMAL");
			
			attroff(A_BOLD);
			attroff(COLOR_PAIR(8));

			mvprintw(7, 0, "\n");
			mvprintw(9, 0, "\n");
			mvprintw(7, 6, "EASY");
			mvprintw(9, 6, "HARD");
			break;
		case 2:
			attron(COLOR_PAIR(8));
			attron(A_BOLD);
			mvprintw(9, 2, ">>");
			
			mvprintw(9, 6, "HARD");
			
			attroff(A_BOLD);
			attroff(COLOR_PAIR(8));

			mvprintw(7, 0, "\n");
			mvprintw(8, 0, "\n");
			mvprintw(7, 6, "EASY");
			mvprintw(8, 6, "NORMAL");
			break;
	}

	max_choices = 3;
	while(ch != 10){
		ch = getch();
		if(ch == 258)
			DIFFICULTY++;
		if(ch == 259)
			DIFFICULTY--;

		if(DIFFICULTY < 0) DIFFICULTY = max_choices - 1;
		if(DIFFICULTY > max_choices - 1) DIFFICULTY = 0;

		switch(DIFFICULTY){
			case 0:
				attron(COLOR_PAIR(8));
				attron(A_BOLD);
				mvprintw(7, 2, ">>");
				
				mvprintw(7, 6, "EASY");
				
				attroff(A_BOLD);
				attroff(COLOR_PAIR(8));

				mvprintw(8, 0, "\n");
				mvprintw(9, 0, "\n");
				mvprintw(8, 6, "NORMAL");
				mvprintw(9, 6, "HARD");
				break;
			case 1:
				attron(COLOR_PAIR(8));
				attron(A_BOLD);
				mvprintw(8, 2, ">>");
				
				mvprintw(8, 6, "NORMAL");
				
				attroff(A_BOLD);
				attroff(COLOR_PAIR(8));

				mvprintw(7, 0, "\n");
				mvprintw(9, 0, "\n");
				mvprintw(7, 6, "EASY");
				mvprintw(9, 6, "HARD");
				break;
			case 2:
				attron(COLOR_PAIR(8));
				attron(A_BOLD);
				mvprintw(9, 2, ">>");
				
				mvprintw(9, 6, "HARD");
				
				attroff(A_BOLD);
				attroff(COLOR_PAIR(8));

				mvprintw(7, 0, "\n");
				mvprintw(8, 0, "\n");
				mvprintw(7, 6, "EASY");
				mvprintw(8, 6, "NORMAL");
				break;
		}

	}


	mvprintw(5, 0, "\n");
	mvprintw(6, 0, "\n");
	mvprintw(7, 0, "\n");
	mvprintw(8, 0, "\n");
	mvprintw(9, 0, "\n");

	switch(DIFFICULTY){
		case 0:
			CURRENT_SPEED = 16;
			break;
		case 1:
			CURRENT_SPEED = 10;
			break;
		case 2:
			CURRENT_SPEED = 5;
			break;
	}

	max_choices = 2;
	players_in_game = 1;

	attron(COLOR_PAIR(8));
	attron(A_BOLD);
	mvprintw(5, 2, ">>");
	
	mvprintw(5, 6, "1 Player");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(8));

	mvprintw(6, 0, "\n");
	mvprintw(6, 6, "2 Players");

	ch = getch();
	if(ch == 258)
		players_in_game++;
	if(ch == 259)
		players_in_game--;

	if(players_in_game < 1) players_in_game = max_choices;
	if(players_in_game > max_choices) players_in_game = 1;

	switch(players_in_game){
		case 1:
			attron(COLOR_PAIR(8));
			attron(A_BOLD);
			mvprintw(5, 2, ">>");
			
			mvprintw(5, 6, "1 Player");
			attroff(A_BOLD);
			attroff(COLOR_PAIR(8));

			mvprintw(6, 0, "\n");
			mvprintw(6, 6, "2 Players");
			break;
		case 2:
			attron(COLOR_PAIR(8));
			attron(A_BOLD);
			mvprintw(6, 2, ">>");

			mvprintw(6, 6, "2 Players");

			attroff(A_BOLD);
			attroff(COLOR_PAIR(8));
			
			mvprintw(5, 0, "\n");
			mvprintw(5, 6, "1 Player");
			break;
	}

	while(ch != 10){
		ch = getch();
		if(ch == 258)
			players_in_game++;
		if(ch == 259)
			players_in_game--;

		if(players_in_game < 1) players_in_game = max_choices;
		if(players_in_game > max_choices) players_in_game = 1;

		switch(players_in_game){
			case 1:
				attron(COLOR_PAIR(8));
				attron(A_BOLD);
				mvprintw(5, 2, ">>");
				
				mvprintw(5, 6, "1 Player");
				attroff(A_BOLD);
				attroff(COLOR_PAIR(8));

				mvprintw(6, 0, "\n");
				mvprintw(6, 6, "2 Players");
				break;
			case 2:
				attron(COLOR_PAIR(8));
				attron(A_BOLD);
				mvprintw(6, 2, ">>");

				mvprintw(6, 6, "2 Players");

				attroff(A_BOLD);
				attroff(COLOR_PAIR(8));
				
				mvprintw(5, 0, "\n");
				mvprintw(5, 6, "1 Player");
				break;
		}

	}

	clear();
	MENU = FALSE;
}