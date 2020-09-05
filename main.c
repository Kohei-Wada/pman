#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "define.h"
#include "util.h"

#define STAGE_X 41
#define STAGE_Y 31

enum FIELD_ELEM elem;
_MAN man = {1, 1, 0, 1};
_ENEM enem[5];


int  stage[STAGE_X][STAGE_Y] = {0};
extern int _stage[STAGE_X][STAGE_Y];


int  life = 3;
int  foods = 0;
int  get_food = 0;


void init_stage(void)
{
    srand((unsigned int)time(NULL));
    for(int x = 0; x < STAGE_X; ++x){
        for(int y = 0; y < STAGE_Y; ++y){
            if(_stage[x][y] == FIELD){
                if(x != 0 && x != 40){
                    _stage[x][y] = FOOD;
                    ++foods;
                }
            }
        }
    }

    for(int i = 0; i < sizeof(enem)/sizeof(_ENEM); ++i){
        enem[i].x = 20;
        enem[i].y = 8;
        enem[i].vx = (rand()%2? 1: -1);
        enem[i].vy = 0;
        enem[i].type = 0;
    }

}

void next_manv()
{
    if(kbhit()){
       char ch = getch();
       switch (ch) {
           case 'a': man.vx = -1; man.vy = 0 ; break;
           case 'f': man.vx = 1 ; man.vy = 0 ; break;
           case 'e': man.vx = 0 ; man.vy = -1; break;
           case 'd': man.vx = 0 ; man.vy = 1 ; break;
           case 'q': life = 0; break;
       }
   }
}

void next_man(void)
{
int x, y;
    next_manv();
    x = man.x + man.vx;
    y = man.y + man.vy;
    if(-1 < x && x < STAGE_X){
        if(stage[x][y] == FIELD){
            man.x = x;
            man.y = y;
        }
        else if(stage[x][y] == FOOD){
            _stage[x][y] = FIELD;
            man.x = x;
            man.y = y;
            ++get_food;
        }
        else if(stage[x][y] == ENEMY){
            --life;
        }
    }
    else if(x > STAGE_X-1){
        man.x = 0;
        man.y = (STAGE_Y-1)/2;
    }
    else if(x < 0){
        man.x = STAGE_X-1;
        man.y = (STAGE_Y-1)/2;
    }

}



void next_enemy(int index, int type)
{
int x, y;

    x = enem[index].x + enem[index].vx;
    y = enem[index].y + enem[index].vy;
    if(-1 < x && x < STAGE_X){

        if(stage[x][y] == FIELD || stage[x][y] == FOOD){
            enem[index].x = x;
            enem[index].y = y;
        }
        else if(stage[x][y] == MAN){
            --life;
        }
        else if(stage[x][y] == WALL_H){
            enem[index].vx = (rand()%2 ? 1: -1);
            enem[index].vy = 0;

        }
        else if(stage[x][y] == WALL_V){
            enem[index].vx = 0;
            enem[index].vy = (rand()%2 ? 1: -1);
        }
    }
    else if(x > STAGE_X-1){
        enem[index].x = 0;
        enem[index].y = (STAGE_Y-1)/2;
    }
    else if(x < 0){
        enem[index].x = STAGE_X-1;
        enem[index].y = (STAGE_Y-1)/2;
    }


}


void next_stage(void)
{
    memcpy(stage, _stage, sizeof(_stage));
    next_man();
    stage[man.x][man.y] = MAN;

    for(int i = 0; i < sizeof(enem)/sizeof(_ENEM); ++i){
        next_enemy(i, enem[i].type);
        stage[enem[i].x][enem[i].y] = ENEMY;
    }
}



void display(void)
{
    for(int y = 0; y < STAGE_Y; ++y){
        printf("\t");
        for(int x = 0; x < STAGE_X; ++x){
            switch(stage[x][y]){
                case FIELD   : printf(" "); break;
                case WALL_V  : printf("\e[34m|\e[0m"); break;
                case WALL_H  : printf("\e[34m=\e[0m"); break;
                case MAN     : printf("\e[33m@\e[0m"); break;
                case KEEP_OUT: printf("\e[34m=\e[0m"); break;
                case FOOD    : printf("."); break;
                case ENEMY   : printf("\e[31m@\e[0m"); break;
            }
        }
        printf("\n");
    }
    printf("x = %2d, y = %d, food = %2d, life = %d\n", man.x, man.y, get_food, life);
    printf(" enem 1\n");
    printf("vx = %2d, vy = %d,\n", enem[0].vx, enem[0].vy);
}



int main(void)
{
int time = 1000000 * 0.1;

    init_stage();
    open_termios();

    while(1){
        system("clear");
        next_stage();
        if(!life){
            printf("game over\n");
            break;
        }
        else if(get_food == foods){
            printf("game clear\n");
            break;
        }
        display();
        usleep(time);
    }
    close_termios();
    printf("exit\n");
    return 0;
}
