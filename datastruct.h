//
// Created by Balint on 2019. 11. 28..
//

#ifndef NHF_DATASTRUCT_H
#define NHF_DATASTRUCT_H
typedef struct Time {
    int ora, perc, mperc;
} Time;

typedef struct data {
    int akna_szam;
    Time ido;
} data;

typedef struct mainstruct {
    char **userBoard;
    char **realBoard;
    int xsize;
    int ysize;
    data data;
} mainstruct;


typedef struct koord {
    int x, y;
} koord;

typedef enum type {
    flag,
    open
} type;
#endif //NHF_DATASTRUCT_H
