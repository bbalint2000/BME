#include "generate.h"
#include <stdbool.h>
#include <stdlib.h>
#include "debugmalloc.h"

//itt generalodik le a realBoard, a random elhelyezett aknakkal
void mine_gen(mainstruct level) {


    for (int i = 0; i < level.ysize; i++)
        for (int j = 0; j < level.xsize; j++)
            level.realBoard[i][j] = '_';

    for (int i = 0; i < level.data.akna_szam; ++i) {
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
}

//itt "nullazzuk" le a userBoardot
void set_userBoard(mainstruct level) {
    for (int i = 0; i < level.ysize; i++)
        for (int j = 0; j < level.xsize; j++)
            level.userBoard[i][j] = '_';
}