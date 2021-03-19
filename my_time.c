#include "my_time.h"
#include "datastruct.h"
#include <time.h>
#include "debugmalloc.h"

Time time_now(clock_t start_time) {
    clock_t current_time = clock();
    int time_diff = ((current_time - start_time) / CLOCKS_PER_SEC);
    Time ido;
    ido.ora = time_diff / 3600;
    ido.perc = (time_diff % 3600) / 60;
    ido.mperc = ((time_diff % 3600) % 60);
    return ido;
}


int time_in_sec(mainstruct level) {
    int time = level.data.ido.ora * 3600 + level.data.ido.perc * 60 + level.data.ido.mperc;
    return time;
}



