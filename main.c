#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "debugmalloc.h"
#include "read.h"
#include "generate.h"
#include "print.h"
#include "my_time.h"
#include "logic.h"
#include "econio.h"

bool again(void) {
    int in;
    scanf("%d", &in);
    if (in == 1) return true;
    return false;
}

void free_tomb(mainstruct level) {
    for (int f = 0; f < level.ysize; ++f)
        free(level.userBoard[f]);
    free(level.userBoard);

    for (int f = 0; f < level.ysize; ++f)
        free(level.realBoard[f]);
    free(level.realBoard);
}

bool win(mainstruct level) {
    int count = 0;
    for (int i = 0; i < level.ysize; i++)
        for (int j = 0; j < level.xsize; j++)
            if ((level.userBoard[i][j] == '_') || (level.userBoard[i][j] == '#'))
                count++;

    if (count > level.data.akna_szam)
        return false;
    return true;
}


bool play_again(mainstruct *level, bool run) {

    printf("Szeretned ujra kezdeni?\nNem--> 0\nIgen--> 1");
    run = again();
    if (run) {
        mainstruct ujlevel = read_in();    //TODO: felszabadítjuk a korábbit
        mine_gen(ujlevel);
        set_userBoard(ujlevel);
        clock_t start_time = clock();
        //  print_out(ujlevel, 1, start_time);
        print_out(ujlevel, 0, start_time);
        free_tomb(*level);
        *level = ujlevel;
    }
    return run;
}

void play(void) {
    srand(time(0));
    koord in;
    mainstruct level;
    int count = 0;
    level = read_in();
    mine_gen(level);
    set_userBoard(level);
    clock_t start_time = clock();  //jatek kezdetenek idopontja
    print_out(level, 1, start_time);
    print_out(level, 0, start_time);

    bool run = true;


//a felhasznalo halal/nyeres utan tudja leallitani
    while (run) {
        if (win(level)) {                              //ellenorzi hogy nyert e
            printf("Nyertel :)\n");            //ha igen, akkor megkerdezi,
            run = play_again(&level, run);               // hogy szeretne e meg jatszani es aszerint cselekszik
        }
        if (choose() == flag) {                           //itt valaszt, hogy zaszlot szeretne e rakni
            place_flag(level, data_in());                 //ha zaszlot rak, elhelyezi a palyan
            print_out(level, 0, start_time);
        } else {                                              //ha  mezot nyit fel
            in = data_in();                              //beolvassa, hogy melyik mezot szeretne felnyitni
            clock_t current_time = clock();  // jelenlegi ido
            if ((current_time - start_time) / CLOCKS_PER_SEC > time_in_sec(
                    level)) {   //ha a kezdeti és jelenlegi különbsége nagyobb mint az ido limit, vége a jateknak
                print_out(level, 1, start_time);                    //kirajzolja a palyat a bombaval
                printf("Letelt az ido!\nVesztettel :(\n");        //kiirja hogy vesztett
                run = play_again(&level, run);                        //szeretne e ujra jatszani vagy nem
            }
            count++;
            if (is_mine(level, in.y, in.x)) {                          //ha az a mezo akna
                if (count == 1) {                                    // es ez az elso kattintas
                    mine_move(level, in);                            //atrakja mashova az aknat
                    printf("Bomba volt az elso kattintas, nyiss ujat.\n");
                } else {                                  //ha nem elso kattintas
                    place_mine(level, in);
                    print_out(level, 0, start_time);                    //kirajzolja a palyat a bombaval
                    printf("Vesztettel :(\n");                   //kiirja hogy vesztett
                    run = play_again(&level, run);                        //szeretne e ujra jatszani vagy nem
                }
            } else {                                            // ha a mezo nem akna
                if (mine_count(level, in.y, in.x) == '0') {  //es a mezo 0
                    place_num(level, in, '0');         //elhelyezi a 0-t
                    null_cell(level, in.y, in.x);            //majd a körülötte levoket is
                }

                place_num(level, in, mine_count(level, in.y, in.x)); // ha nem akna és nem is nulla,
                print_out(level, 0,
                          start_time);                            //elhelyezi azt, hogy hany akna van korulotte
            }
        }
    }
    free_tomb(level);
}


int main() {
    setbuf(stdout, 0);
    play();


    return 0;
}