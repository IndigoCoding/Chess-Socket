//
// Created by 1918 on 31-Jan-18.
//

#include <stdio.h>
#include "defs.h"

U64 generatePosKey(const S_BOARD *pos) {

    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    // pieces
    for (sq = 0; sq < BOARD_SQ_NUM; ++sq) {
        piece = pos->pieces[sq];
        if (piece != NO_SQ && piece != EMPTY && piece != OFFBOARD) {
            ASSERT(piece >= wP && piece <= bK);
            finalKey ^= pieceKeys[piece][sq];
        }
    }

    if (pos->side == WHITE) {
        finalKey ^= sideKey;
    }

    if (pos->enPas != NO_SQ) {
        ASSERT(pos->enPas >= 0 && pos->enPas < BOARD_SQ_NUM);
        finalKey ^= pieceKeys[EMPTY][pos->enPas];
    }

    ASSERT(pos->castlePermission >= 0 && pos->castlePermission <= 15);
    finalKey ^= castleKeys[pos->castlePermission];

    return finalKey;
}