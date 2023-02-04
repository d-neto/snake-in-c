/*
    DIR 0 = UP
    DIR 1 = RIGHT
    DIR 2 = DOWN
    DIR 3 = LEFT
    */

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}
void KeyEvents(){
    if(kbhit()){
        int ch = getch();

        int i = 0;
        for(i; i < PLAYERS_SIZE; i++){

            if(players[i].is_dead) continue;

            if(ch == players[i].control.UP)
                if(players[i].direction != 2) players[i].direction = 0;

            if(ch == players[i].control.RIGHT)
                if(players[i].direction != 3) players[i].direction = 1;

            if(ch == players[i].control.DOWN)
                if(players[i].direction != 0) players[i].direction = 2;

            if(ch == players[i].control.LEFT)
                if(players[i].direction != 1) players[i].direction = 3;

        }

        /* 
            LOG KEYS 
        mvprintw(17, 2, "Key Pressed: %d", ch); */
    }
}