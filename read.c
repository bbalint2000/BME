#include "read.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

//itt irja be a user a koordinatat ahova "kattintani" szeretne
koord data_in(void) {
    koord in;
    printf("Add meg a koordinatat, ahova 'kattintani' szeretnel! (oszlop,sor)\n");
    scanf("%d,%d", &in.y, &in.x);
    in.x--;
    in.y--;
    return in;
}

//itt donti el a user, hogy megszeretne e jelolni a beirt koordinatat, vagy kinyitni szeretne a mezot
type choose(void) {
    int what;
    printf("Valaszd ki mit szeretnel tenni: koordinatat megjelolni ( 0 ) vagy kinyitni ( 1 )\n");
    scanf("%d", &what);

    switch (what) {
        case 0:
            return flag;
        case 1:
            return open;
        default:
            printf("Rossz szamot irtal be, ilyet nem lehet valasztani.\n");
            choose();

    }
}

char *txt_name_scan(void) {
    char *str = malloc(sizeof(char));  //TODO: free
    str[0] = '\0';
    char c;
    while (scanf("%c", &c) != EOF && c != '\n') {
        int hossz = strlen(str);
        str = realloc(str, (hossz + 2) * sizeof(char));
        str[hossz] = c;
        str[hossz + 1] = '\0';
    }
    return str;
}

//itt olvassa be a program a kulso fajlokbol az adatokat, ami alapjan majd a palyat lehet letrehozni
mainstruct read_in(void) {
    mainstruct level;
    int input;
    FILE *fp = NULL;
    printf("Valaszd ki a nehezseget!\nKonnyu --> 1\nNormal --> 2\nNehez  --> 3\nCustom --> 4\n");
    scanf("%d%*c", &input);
    switch (input) {
        case 1:
            fp = fopen("konnyu.txt", "rt");
            break;
        case 2:
            fp = fopen("kozepes.txt", "rt");
            break;
        case 3:
            fp = fopen("nehez.txt", "rt");
            break;
        case 4:
            printf("Add meg a fajl nevet:\n");
            char *custom;
            custom = txt_name_scan();
            fp = fopen(custom, "rt");
            free(custom);
            break;
    }

    if (fp == NULL) {
        printf("Helytelen nehezseget adtal meg.\n");
        level.xsize = level.ysize = level.data.akna_szam = level.data.ido.ora = level.data.ido.perc = level.data.ido.mperc = 0;
        return level;
    }

    fscanf(fp, "%dx%d %d %d:%d:%d", &(level.xsize), &(level.ysize), &(level.data.akna_szam), &(level.data.ido.ora),
           &(level.data.ido.perc), &(level.data.ido.mperc));

    level.realBoard = malloc(sizeof(data) * level.ysize);  //TODO: free
    for (int i = 0; i < level.ysize; i++)
        level.realBoard[i] = malloc(sizeof(data) * level.xsize);          //TODO: free

    level.userBoard = malloc(sizeof(data) * level.ysize);       //TODO: free
    for (int i = 0; i < level.ysize; i++)
        level.userBoard[i] = malloc(sizeof(data) * level.xsize);          //TODO: free



    fclose(fp);
    return level;
}
