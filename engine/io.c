//
// Created by 1918 on 05-Feb-18.
//

#include <stdio.h>
#include "defs.h"

char *printSquare(const int sq) {

    static char SqStr[3];

    int file = filesBoard[sq];
    int rank = ranksBoard[sq];

    sprintf(SqStr, "%c%c", ('a' + file), ('1' + rank));
    return SqStr;
}

char *printMove(const int move) {

    static char MvStr[6];

    int ff = filesBoard[FROMSQ(move)];
    int rf = ranksBoard[FROMSQ(move)];
    int ft = filesBoard[TOSQ(move)];
    int rt = ranksBoard[TOSQ(move)];

    int promoted = PROMOTED(move);

    if (promoted) {
        char pchar = 'q';
        if (IsKn(promoted)) {
            pchar = 'n';
        } else if (IsRQ(promoted) && !IsBQ(promoted)) {
            pchar = 'r';
        } else if (!IsRQ(promoted) && IsBQ(promoted)) {
            pchar = 'b';
        }
        sprintf(MvStr, "%c%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt), pchar);
    } else {
        sprintf(MvStr, "%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt));
    }

    return MvStr;
}

void printMoveList(const S_MOVELIST *list) {
    int index = 0;
    int score = 0;
    int move = 0;
    printf("MoveList:\n", list->count);

    for (index = 0; index < list->count; ++index) {

        move = list->moves[index].move;
        score = list->moves[index].score;

        printf("Move:%d > %s (score:%d)\n", index + 1, printMove(move), score);
    }
    printf("MoveList Total %d Moves:\n\n", list->count);
}