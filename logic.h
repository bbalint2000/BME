#ifndef NHF_LOGIC_H
#define NHF_LOGIC_H

#include "datastruct.h"
#include <stdbool.h>


bool valid(int y, int x, mainstruct level);

bool is_mine(mainstruct level, int y, int x);

char mine_count(mainstruct level, int y, int x);

void null_cell(mainstruct level, int y, int x);


#endif //NHF_LOGIC_H
