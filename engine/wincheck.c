//
// Created by 1918 on 14-Feb-18.
//

#include "defs.h"

extern int isCheckmated(S_BOARD *pos) {
    S_MOVELIST list[1];
    generateAllMoves(pos, list);

    int side = pos->side;
    int i = 0;

    if (!sqAttacked(pos->kingSq[side], side^1, pos)) {
        return FALSE;
    }

    if (list->count == 0) {
        return TRUE;
    } else {
        for (i = 0; i < list->count; i++) {
            if (makeMove(pos, list->moves[i].move)) {
                takeMove(pos);
                return FALSE;
            }
        }
    }
    return TRUE;
}