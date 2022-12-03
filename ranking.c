
typedef struct Ranking{
    char nome[128];
    int score;
    char difficulty[128];
}Ranking;


int GetRankingSize(){
    FILE * f_ranking;
    f_ranking = fopen("./data/ranking.data", "r");

    int line = 0;
    char buffer[256];
    while(fgets(buffer, 256, f_ranking)){
        line++;
    }
    fclose(f_ranking);

    return line;
}
void GetRanking(int x, int y){
    FILE * f_ranking;
    f_ranking = fopen("./data/ranking.data", "r");

    attron(A_BOLD);
    attron(COLOR_PAIR(8));
    mvprintw(y, x, "+=====    Ranking    =====+\n");
    attroff(A_BOLD);

    Ranking RANKING_RAW[GetRankingSize()];
    char nome[128];
    int score;
    char difficulty[128];

    for(int i = 0; i < GetRankingSize(); i++){
        fscanf(f_ranking, "%s %d %s", nome, &score, difficulty);

        RANKING_RAW[i].score = score;
        sprintf(RANKING_RAW[i].nome, "%s", nome);
        sprintf(RANKING_RAW[i].difficulty, "%s", difficulty);

        //mvprintw(++y, x, "%s: %d - %s", nome, score, difficulty);
        refresh();
    }

    Ranking RANKING[GetRankingSize()];
    RANKING[0].score = 0;
    for(int i = 0; i < GetRankingSize(); i++){
        RANKING[i] = RANKING_RAW[i];
        for(int k = 0; k < GetRankingSize(); k++)
            if(RANKING_RAW[k].score > RANKING[i].score){
                RANKING[i] = RANKING_RAW[k];
                RANKING_RAW[k].score = -1000;
            }

        if(i < 3) attron(COLOR_PAIR(9));
        else attron(COLOR_PAIR(10));
        if(RANKING[i].score >= 0)
            mvprintw(++y, x + 1, "%dº %s: %d - %s", (i+1), RANKING[i].nome, RANKING[i].score, RANKING[i].difficulty);
        refresh();
    }

    fclose(f_ranking);
}
void AddInRanking(int x, int y, int score, int d){

    char nome[128];
    char difficulty[128];
    sprintf(nome, "%s", "");

    switch(d){
        case 1: sprintf(difficulty, "%s", "EASY");
        break;
        case 2: sprintf(difficulty, "%s", "MEDIUM");
        break;
        case 3: sprintf(difficulty, "%s", "HARD");
        break;
    }

    attron(COLOR_PAIR(11));
    echo();
    nodelay(stdscr, FALSE);
    curs_set(1);
    mvprintw(y, x, "INSERT YOUR NAME: ");
    
    while(nome[0] == 0){
        move(y, x + 18);
        scanw("%s\n", &nome);
    }


    FILE * f_ranking;
    f_ranking = fopen("./data/ranking.data", "a");
    fprintf(f_ranking, "%s %d %s\n", nome, score, difficulty);

    fclose(f_ranking);
    curs_set(0);
}