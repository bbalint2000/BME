#ifndef NHF_PRINT_H
#define NHF_PRINT_H

#include <time.h>
#include "datastruct.h"

void print_out(mainstruct level, int num, clock_t start_time);

void place_flag(mainstruct level, koord input);

void place_mine(mainstruct level, koord input);

void place_num(mainstruct level, koord input, char num);

void mine_move(mainstruct level, koord in);

#endif //NHF_PRINT_H
