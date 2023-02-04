#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_LENGTH WIDTH * HEIGHT

#define TRUE 1
#define FALSE 0

typedef struct position{
    int x;
    int y;
} Position;

typedef struct controls{
    int UP;
    int RIGHT;
    int DOWN;
    int LEFT;
} Control;

typedef struct snake{
    char * name;
    int length;
    int direction;
    Control control;
    Position body[MAX_LENGTH];
    int is_dead;
    int render;
    int score;
} Snake;

int MENU = 1;
int DRAWNEDBG = 0;
int END = 0;
int SCORE = 0;

float CURRENT_SPEED = 10;

Position foodPosition = {WIDTH/2, HEIGHT/2};

/*
    FOOD_TYPE = 0 -> +1 snake_length & score
    FOOD_TYPE = 1 -> +3 snake_length & score
    FOOD_TYPE = 2 -> +1 score only
    */
int FOOD_TYPE = 0;


Snake AddPlayer(char * name, int length, int direction, Control keys, int x, int y, int dead){
    Snake player;

    player.name = name;
    player.length = length;
    player.direction = direction;

    player.control = keys;

    player.body->x = x;
    player.body->y = y;

    player.is_dead = dead;
    player.render = TRUE;
    player.score = 0;

    return player;
}

#define PLAYERS_SIZE 2
Snake players[PLAYERS_SIZE];
int players_in_game = 0;

void SetUpPlayers(){

    //ARROW KEYS MAP
    Control keys_1 = {259, 261, 258, 260};

    //WASD KEYS MAP
    Control keys_2 = {119, 100, 115, 97};

    int player_2_set = (players_in_game == 1);

    players[0] = AddPlayer("Player 1", 3, 1, keys_1, 5, 3, FALSE);
    players[1] = AddPlayer("Player 2", 3, 1, keys_2, 5, HEIGHT - 4, player_2_set);
}

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

void RenderPlayers(){

    int i = 0;
    for(i; i < players_in_game; i++){

        if(!players[i].render) continue;

        attron(COLOR_PAIR(3));
        attron(A_BOLD);

        if(players[i].is_dead){
            attron(COLOR_PAIR(5));
            attroff(A_BOLD);
        }

        if(players[i].direction == 0) mvprintw(players[i].body[0].y, players[i].body[0].x, "^");
        if(players[i].direction == 1) mvprintw(players[i].body[0].y, players[i].body[0].x, ">");
        if(players[i].direction == 2) mvprintw(players[i].body[0].y, players[i].body[0].x, "v");
        if(players[i].direction == 3) mvprintw(players[i].body[0].y, players[i].body[0].x, "<");

        int j = 1;
        for(j; j < players[i].length; j++)
            if(players[i].body[j].x != 0 && players[i].body[j].y != 0)
                mvprintw(players[i].body[j].y, players[i].body[j].x, "*");

        if(players[i].is_dead) players[i].render = FALSE;

        attroff(COLOR_PAIR(3));
        attroff(COLOR_PAIR(5));
        attroff(A_BOLD);
    }

}

void GenerateSnakeBody(Snake * player){
    Position p;
    p.x = player->body[0].x;
    p.y = player->body[0].y;

    for(int i = 0; i < player->length; i++) 
        if(player->body[i].x != 0 && player->body[i].y != 0)
            mvprintw(player->body[i].y, player->body[i].x, " ");

    for(int i = player->length - 1; i > 0; i--){
        Position p2;
        p2 = player->body[i];

        player->body[i] = p;

        p = p2;
    }
}

void MovePlayers(){

    int i = 0;
    for(i; i < players_in_game; i++){

        if(players[i].is_dead) continue;

        GenerateSnakeBody(&players[i]);

        mvprintw(players[i].body[0].y, players[i].body[0].x, " ");


        switch(players[i].direction){
            case 0:
                players[i].body[0].y -= 1;
                break;
            case 1:
                players[i].body[0].x += 1;
                break;
            case 2:
                players[i].body[0].y += 1;
                break;
            case 3:
                players[i].body[0].x -= 1;
                break;
        }

    }

}

int DetectCollisonAll(){

    int i = 0;
    for(i; i < players_in_game; i++){
        
        if(players[i].is_dead) continue;

        int k = 1;
        for(k; k < players[i].length; k++){
            if(players[i].is_dead) break;

            if(players[i].body[k].x != 0 && players[i].body[k].y != 0){
                int j = 0;
                for(j; j < players_in_game; j++){

                    if(players[i].is_dead) continue;
                    if(players[j].is_dead) continue;

                    if(players[i].body[k].x == players[j].body[0].x && players[i].body[k].y == players[j].body[0].y){
                        players[j].is_dead = TRUE;
                        beep();
                        continue;
                    }
                }
            }

        }


        if(players[i].body[0].x == 0 || players[i].body[0].x == WIDTH - 1){
            players[i].is_dead = TRUE;
            beep();
            continue;
        }
        
        if(players[i].body[0].y == 0 || players[i].body[0].y == HEIGHT - 1){
            players[i].is_dead = TRUE;
            beep();
            continue;
        }



        if(players[i].body[0].x == foodPosition.x && players[i].body[0].y == foodPosition.y){
            switch(FOOD_TYPE){
                case 0:
                    players[i].length += 1;
                    players[i].score += 1;
                    break;
                case 1:
                    players[i].length += 3;
                    players[i].score += 3;
                    break;
                case 2:
                    players[i].score += 2;
                    break;
            }


            int j = 0;
            for(j; j < players_in_game; j++){
                //rand() % (max + 1 - min)) + min;
                foodPosition.x = rand() % ((WIDTH - 3) + 1 - 3) + 3;
                foodPosition.y = rand() % ((HEIGHT - 3) + 1 - 3) + 3;

                int k = 1;
                for(k; k < players[j].length; k++){
                    if(foodPosition.x == players[j].body[k].x && foodPosition.x == players[j].body[k].x){
                        j--;
                        break;
                    }
                }
            }

            int random_number = rand() % 100;
            if(random_number < 50) FOOD_TYPE = 0;
            if(random_number >= 50 && random_number < 70) FOOD_TYPE = 1;
            if(random_number >= 70 && random_number < 100) FOOD_TYPE = 2;
            beep();
        }
    }

    return 0;
}

int GameOver(){
    int i = 0;
    int dead_players = 0;
    for(i; i < PLAYERS_SIZE; i++){
        if(players[i].is_dead) dead_players++;
    }

    if(dead_players == PLAYERS_SIZE) return TRUE;
    else return FALSE;
}

void DrawFood(int x, int y){
    mvprintw(y, x, "@");
}

void BG(){
    attron(COLOR_PAIR(1));
    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
            mvprintw(i, j, " ");
}

void DrawScore(int x, int y){

	attron(COLOR_PAIR(6));
    mvprintw(y, x, "+===== Score =====+");
	attroff(COLOR_PAIR(6));

    int i = 0;

    for(i; i < players_in_game; i++){
        attron(A_BOLD);
        if(!players[i].is_dead){
            attron(COLOR_PAIR(9));
            attron(A_BOLD);
            mvprintw(y+i+1, x, "%s - %d pts.\n", players[i].name, players[i].score);
            attroff(A_BOLD);
	        attroff(COLOR_PAIR(9));
        }
        else{
	        attron(COLOR_PAIR(13));
            mvprintw(y+i+1, x, "%s - DEAD.\n", players[i].name);
	        attroff(COLOR_PAIR(13));
        }
        attroff(A_BOLD);

    }
}

void ResetGame(){
    SetUpPlayers();
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
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);
    init_pair(9, COLOR_GREEN, COLOR_BLACK);
    init_pair(10, COLOR_BLUE, COLOR_BLACK);
    init_pair(11, COLOR_BLACK, COLOR_WHITE);
    init_pair(12, COLOR_WHITE, COLOR_RED);
    init_pair(13, COLOR_RED, COLOR_BLACK);

    while(!END){

		if(MENU){
			nodelay(stdscr, FALSE);
			curs_set(1);
			echo();
			PrintMenu();
			refresh();
			DRAWNEDBG = FALSE;
		}else{

			if(!DRAWNEDBG){
				nodelay(stdscr, TRUE);
                ResetGame();
				curs_set(0);
				noecho();
				BG();
			    refresh();
                attron(A_BOLD);
			    attron(COLOR_PAIR(2));
			    DrawScene();
                attroff(A_BOLD);
			    refresh();
				DRAWNEDBG = TRUE;
			}
	
	        if(!GameOver()){
	
	            attron(COLOR_PAIR(3));
                attron(A_BOLD);
	            RenderPlayers();
                attroff(A_BOLD);

	            DrawScore(WIDTH + 2, 0);
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
	            DrawFood(foodPosition.x, foodPosition.y);
	            refresh();
	        }
	
	        usleep(CURRENT_SPEED * 10000L);
	        
	        if(!GameOver()){
	            KeyEvents();
	            MovePlayers();
	        }
	        
	        DetectCollisonAll();

            if(GameOver()){
                attron(COLOR_PAIR(5));
	            RenderPlayers();

                attron(A_BOLD);
                attron(COLOR_PAIR(12));
                mvprintw(HEIGHT/2, (WIDTH/2) - 6, " GAME OVER! ");
                attroff(A_BOLD);
                attroff(COLOR_PAIR(12));

                attron(COLOR_PAIR(1));
                mvprintw(HEIGHT/2 + 2, (WIDTH/2) - 12, " Press ENTER to return ");
                attroff(COLOR_PAIR(1));

                refresh();
                usleep(100 * 10000L);

			    nodelay(stdscr, FALSE);
                while(getchar() != 13);
                MENU = TRUE;
                CHOICE = 0;
                clear();
            }
		}
    }

    endwin();

    return 0;
}