#include "print.h"
#include <stdio.h>
#include "econio.h"
#include <time.h>
#include "datastruct.h"
#include "my_time.h"
#include <stdlib.h>
#include "debugmalloc.h"


void print_out(mainstruct level, int num, clock_t start_time) {
    Time ido = time_now(start_time);

    printf("  ");
    for (int i = 0; i < level.xsize; i++)
        printf("%2d ", i + 1);
    printf("\n");

    for (int i = 0; i < level.ysize; i++) {
        printf("%2d", i + 1);
        econio_textbackground(COL_LIGHTGRAY);
        econio_textcolor(COL_BLACK);
        for (int j = 0; j < level.xsize; j++)
            printf("%2c ", num == 0 ? level.userBoard[i][j] : level.realBoard[i][j]);
        econio_textbackground(COL_RESET);
        econio_textcolor(COL_RESET);
        printf("\n");
    }
    printf("Eltelt ido:%2d:%2d:%2d\n", ido.ora, ido.perc, ido.mperc);
}


// elhelyezi a zaszlot a userBoardon
void place_flag(mainstruct level, koord input) {
    level.userBoard[input.y][input.x] = '#';
}

void place_mine(mainstruct level, koord input) {
    level.userBoard[input.y][input.x] = '*';
}

void place_num(mainstruct level, koord input, char num) {
    level.userBoard[input.y][input.x] = num;
}

void mine_move(mainstruct level, koord in) {
    level.realBoard[in.y][in.x] = '_';
    bool joe = true;
    while (joe) {
        int randy = (rand() % level.ysize);
        int randx = (rand() % level.xsize);
        joe = false;
        if (level.realBoard[randy][randx] == '*')
            joe = true;
        level.realBoard[randy][randx] = '*';
    }
}