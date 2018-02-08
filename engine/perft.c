//
// Created by 1918 on 08-Feb-18.
//

#include <stdio.h>
#include "defs.h"

long leafNodes;

void perft(int depth, S_BOARD *pos) {

    ASSERT(CheckBoard(pos));

    if (depth == 0) {
        leafNodes++;
        return;
    }

    S_MOVELIST list[1];
    generateAllMoves(pos, list);

    int moveNum = 0;
    for (moveNum = 0; moveNum < list->count; ++moveNum) {

        if (!makeMove(pos, list->moves[moveNum].move)) {
            continue;
        }
        perft(depth - 1, pos);
        takeMove(pos);
    }

    return;
}


void perftTest(int depth, S_BOARD *pos) {

    ASSERT(CheckBoard(pos));

    printBoard(pos);
    printf("\nStarting Test To Depth:%d\n", depth);
    leafNodes = 0;

    S_MOVELIST list[1];
    generateAllMoves(pos, list);

    int move;
    int moveNum = 0;
    for (moveNum = 0; moveNum < list->count; ++moveNum) {
        move = list->moves[moveNum].move;
        if (!makeMove(pos, move)) {
            continue;
        }
        long cumNodes = leafNodes;
        perft(depth - 1, pos);
        takeMove(pos);
        long oldNodes = leafNodes - cumNodes;
        printf("move %d : %s : %ld\n", moveNum + 1, printMove(move), oldNodes);
    }

    printf("\nTest Complete : %ld nodes visited\n", leafNodes);

    return;
}