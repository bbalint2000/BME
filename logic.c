#include "logic.h"
#include "datastruct.h"
#include <stdbool.h>
#include "debugmalloc.h"

//helyes e az input koordinat
bool valid(int y, int x, mainstruct level) {
    return (0 <= y && y < level.ysize &&
            0 <= x && x < level.xsize);
}

bool is_mine(mainstruct level, int y, int x) {
    return (level.realBoard[y][x] == '*');
}

bool mine_nextto(mainstruct level, int y, int x) {
    if (valid(y, x, level))
        if (is_mine(level, y, x))
            return true;
    return false;
}


//megszamolja, hogy a beirt koordinata korul hany akna van, majd ezt atirja a userBoardba
char mine_count(mainstruct level, int y, int x) {
    int count = 0;

    if (mine_nextto(level, y - 1, x - 1))
        count++;

    if (mine_nextto(level, y, x - 1))
        count++;

    if (mine_nextto(level, y + 1, x - 1))
        count++;

    if (mine_nextto(level, y + 1, x))
        count++;

    if (mine_nextto(level, y + 1, x + 1))
        count++;

    if (mine_nextto(level, y, x + 1))
        count++;

    if (mine_nextto(level, y - 1, x + 1))
        count++;

    if (mine_nextto(level, y - 1, x))
        count++;

    return (count + '0');
}

bool triple_if(mainstruct level, int y, int x) {
    if (valid(y, x, level) && (level.userBoard[y][x] == '_') && (mine_count(level, y, x) != '*'))
        return true;
    return false;

}

void null_cell(mainstruct level, int y, int x) {
    if (!valid(y, x, level))
        return;

    if (triple_if(level, y, x - 1)) {
        level.userBoard[y][x - 1] = mine_count(level, y, x - 1);
        if (mine_count(level, y, x - 1) == '0')
            null_cell(level, y, x - 1);
    }

    if (triple_if(level, y, x + 1)) {
        level.userBoard[y][x + 1] = mine_count(level, y, x + 1);
        if (mine_count(level, y, x + 1) == '0')
            null_cell(level, y, x + 1);
    }

    if (triple_if(level, y - 1, x)) {
        level.userBoard[y - 1][x] = mine_count(level, y - 1, x);
        if (mine_count(level, y - 1, x) == '0')
            null_cell(level, y - 1, x);
    }

    if (triple_if(level, y + 1, x)) {
        level.userBoard[y + 1][x] = mine_count(level, y + 1, x);
        if (mine_count(level, y + 1, x) == '0')
            null_cell(level, y + 1, x);
    }
}

