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

int parseMove(char *ptrChar, S_BOARD *pos) {
    if (ptrChar[1] > '8' || ptrChar[1] < '1') return NOMOVE;
    if (ptrChar[3] > '8' || ptrChar[3] < '1') return NOMOVE;
    if (ptrChar[0] > 'h' || ptrChar[0] < 'a') return NOMOVE;
    if (ptrChar[2] > 'h' || ptrChar[2] < 'a') return NOMOVE;

    int from = FR2SQ(ptrChar[0] - 'a', ptrChar[1] - '1');
    int to = FR2SQ(ptrChar[2] - 'a', ptrChar[3] - '1');

    printf("ptrChar: %s from: %d to:%d\n", ptrChar, from, to);
    ASSERT(sqOnBoard(from) && sqOnBoard(to));

    S_MOVELIST list[1];
    generateAllMoves(pos, list);
    int moveNum = 0;
    int move = 0;
    int promPiece = EMPTY;

    for (moveNum = 0; moveNum < list->count; moveNum++) {
        move = list->moves[moveNum].move;
        if (FROMSQ(move) == from && TOSQ(move) == to) {
            promPiece = PROMOTED(move);
            if (promPiece != EMPTY) {
                if (IsRQ(promPiece) && !IsBQ(promPiece) && ptrChar[4] == 'r') {
                    return move;
                } else if (!IsRQ(promPiece) && IsBQ(promPiece) && ptrChar[4] == 'b') {
                    return move;
                } else if (IsRQ(promPiece) && IsBQ(promPiece) && ptrChar[4] == 'q') {
                    return move;
                } else if (IsKn(promPiece) && ptrChar[4] == 'n') {
                    return move;
                }
                continue;
            }
            return move;
        }
    }
    return NOMOVE;
}