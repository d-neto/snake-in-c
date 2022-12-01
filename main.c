#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_LENGTH WIDTH * HEIGHT

typedef struct{
    int X;
    int Y;
} Position;

int MENU = 1;
int DRAWNEDBG = 0;
int GAME_OVER = -1;
int END = 0;
int SCORE = 0;
/*
DIR 0 = UP
DIR 1 = RIGHT
DIR 2 = DOWN
DIR 3 = LEFT
*/
int DIR = 1;
float CURRENT_SPEED = 10;

int pX = 5, pY = 3;
int snake_size = 1;
Position snake_body[MAX_LENGTH];

Position foodPosition = {WIDTH/2, HEIGHT/2};
int FOOD_TYPE = 0;
/*
FOOD_TYPE = 0 -> +1 snake_length & score
FOOD_TYPE = 1 -> +3 snake_length & score
FOOD_TYPE = 2 -> +1 score only
*/

#include "./keyevents.c"
#include "./menu.c"

void DrawScene(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(i == 0 || i == HEIGHT - 1) mvprintw(i, j, "=");
            if(j == 0 || j == WIDTH - 1) mvprintw(i, j, "|");
        }
    }
    mvprintw(0, 0, "+");
    mvprintw(0, WIDTH - 1, "+");
    mvprintw(HEIGHT - 1, 0, "+");
    mvprintw(HEIGHT - 1, WIDTH - 1, "+");
}
void DrawPlayer(){
    if(DIR == 0) mvprintw(pY, pX, "^");
    if(DIR == 1) mvprintw(pY, pX, ">");
    if(DIR == 2) mvprintw(pY, pX, "v");
    if(DIR == 3) mvprintw(pY, pX, "<");
    for(int i = 0; i < snake_size; i++)
        if(snake_body[i].X != 0 && snake_body[i].Y != 0)
            mvprintw(snake_body[i].Y, snake_body[i].X, "*");
}
void MovePlayer(){
    mvprintw(pY, pX, " ");
    switch(DIR){
        case 0:
            pY -= 1;
            break;
        case 1:
            pX += 1;
            break;
        case 2:
            pY += 1;
            break;
        case 3:
            pX -= 1;
            break;
    }

    if(DIR == 0 || DIR == 2) CURRENT_SPEED = SPEED*1.5;
    else CURRENT_SPEED = SPEED;
}
int DetectCollison(){
    if(pY == 0 || pY == HEIGHT - 1) return 1;
    if(pX == 0 || pX == WIDTH - 1) return 1;

    for(int i = 0; i < snake_size; i++)
        if(snake_body[i].Y == pY && snake_body[i].X == pX)
            return 1;

    if(pX == foodPosition.X && pY == foodPosition.Y){
        switch(FOOD_TYPE){
            case 0:
                snake_size += 1;
                SCORE += 1;
                break;
            case 1:
                snake_size += 3;
                SCORE += 3;
                break;
            case 2:
                SCORE += 2;
                break;
        }
        //rand() % (max + 1 - min)) + min;
        foodPosition.X = rand() % ((WIDTH - 3) + 1 - 3) + 3;
        foodPosition.Y = rand() % ((HEIGHT - 3) + 1 - 3) + 3;

        int random_number = rand() % 100;
        if(random_number < 50) FOOD_TYPE = 0;
        if(random_number >= 50 && random_number < 70) FOOD_TYPE = 1;
        if(random_number >= 70 && random_number < 100) FOOD_TYPE = 2;
        beep();
    }

    return 0;
}

void DrawFood(int x, int y){
    mvprintw(y, x, "0");
}

void BG(){
    attron(COLOR_PAIR(1));
    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
            mvprintw(i, j, " ");
}

void DrawScore(int x, int y){
    mvprintw(y, x, "+=== Score: %d ===+", SCORE);
}

int main(){
    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    init_pair(4, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_GREEN, COLOR_WHITE);
    init_pair(7, COLOR_YELLOW, COLOR_WHITE);


    while(!END){

		if(MENU){
			nodelay(stdscr, FALSE);
			curs_set(1);
			echo();
			PrintMenu();
			refresh();
			DRAWNEDBG = 0;
		}else{

			if(!DRAWNEDBG){
				nodelay(stdscr, TRUE);
				curs_set(0);
				noecho();
				BG();
			    refresh();
			    attron(COLOR_PAIR(2));
			    DrawScene();
			    refresh();
				DRAWNEDBG = 1;
			}
	
	        if(GAME_OVER != 1){
	
	            if(GAME_OVER == -1) attron(COLOR_PAIR(3));
	            else attron(COLOR_PAIR(5));
	            DrawPlayer();
	            DrawScore(0, HEIGHT);
	            refresh();
	
	            switch(FOOD_TYPE){
	                case 0:
	                    attron(COLOR_PAIR(6));
	                    break;
	                case 1:
	                    attron(COLOR_PAIR(7));
	                    break;
	                case 2:
	                    attron(COLOR_PAIR(2));
	                    break;
	            }
	            DrawFood(foodPosition.X, foodPosition.Y);
	            refresh();
	
	            Position p;
	            p.X = pX;
	            p.Y = pY;
	            for(int i = 0; i < snake_size; i++) 
	                if(snake_body[i].X != 0 && snake_body[i].Y != 0)
	                    mvprintw(snake_body[i].Y, snake_body[i].X, " ");
	            for(int i = snake_size - 1; i > 0; i--){
	                Position p2;
	                p2 = snake_body[i];
	
	                snake_body[i] = p;
	
	                p = p2;
	            }
	        }
	
	        usleep(CURRENT_SPEED * 10000L);
	        
	        if(GAME_OVER == -1){
	            KeyEvents();
	            MovePlayer();
	        }
	        
	        if(DetectCollison() && GAME_OVER < 1) GAME_OVER++;
		}
    }

    endwin();

    return 0;
}