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
int _stage[STAGE_X][STAGE_Y] = {
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 2, 0, 2, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 1, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 0, 0, 2, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 0, 2, 0, 1, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 1, 0, 1, 1, 0, 2, 2, 2, 0, 2, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2},
    {2, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 2, 2, 0, 1, 1, 2, 0, 2, 0, 2},
    {2, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 2, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 0, 2, 0, 2},
    {2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2, 2, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 2},
    {2, 0, 2, 2, 0, 1, 1, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 2, 0, 0, 0, 2, 0, 2, 2, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 2, 0, 1, 1, 1, 0, 2},
    {2, 0, 2, 2, 0, 1, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 0, 2, 2, 2, 0, 2},
    {2, 0, 1, 1, 0, 2, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 2, 0, 1, 1, 1, 0, 2},
    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3, 3, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2, 3, 3, 3, 3, 3, 2, 0, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2},
/**/{2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2, 3, 3, 3, 3, 3, 2, 0, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2},
    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3, 3, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 1, 1, 0, 2, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 2, 0, 1, 1, 1, 0, 2},
    {2, 0, 2, 2, 0, 1, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 0, 2, 2, 2, 0, 2},
    {2, 0, 2, 2, 0, 0, 0, 2, 0, 2, 2, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 2, 0, 1, 1, 1, 0, 2},
    {2, 0, 2, 2, 0, 1, 1, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2, 2, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 2},
    {2, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 2, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 2, 2, 0, 1, 1, 2, 0, 2, 0, 2},
    {2, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 1, 0, 1, 1, 0, 2, 2, 2, 0, 2, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 2, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 0, 2, 0, 0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 1, 0, 2, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 0, 2},
    {2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2},
    {2, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 2, 0, 2, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},                                          //
};



int  die = 0;
int  foods = 0;
int  get_food = 0;


void init_stage(void)
{
    srand((unsigned int)time(NULL));
    for(int x = 0; x < STAGE_X; ++x){
        for(int y = 0; y < STAGE_Y; ++y){
            if(_stage[x][y] == FIELD){
                _stage[x][y] = FOOD;
                ++foods;
            }
        }
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
           case 'q': die = 1; break;
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


void next_stage(void)
{
    memcpy(stage, _stage, sizeof(_stage));
    next_man();
    stage[man.x][man.y] = MAN;
}



void display(void)
{
    for(int y = 0; y < STAGE_Y; ++y){
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
    printf("x = %d, y = %d, food = %d, allfood = %d\n", man.x, man.y, get_food, foods);
}




int main(void)
{
int time = 1000000 * 0.1;

    init_stage();
    open_termios();

    while(1){
        system("clear");
        next_stage();
        if(die){
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