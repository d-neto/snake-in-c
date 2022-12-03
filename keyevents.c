#define UP_KEY 259
#define DOWN_KEY 258
#define RIGHT_KEY 261
#define LEFT_KEY 260

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
        switch(ch){
            case UP_KEY:
                if(DIR != 2) DIR = 0;
                break;
            case RIGHT_KEY:
                if(DIR != 3) DIR = 1;
                break;
            case DOWN_KEY:
                if(DIR != 0) DIR = 2;
                break;
            case LEFT_KEY:
                if(DIR != 1) DIR = 3;
                break;
        }
        //mvprintw(17, 2, "Key Pressed: %d", ch);
    }
}