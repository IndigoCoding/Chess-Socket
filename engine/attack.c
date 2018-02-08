//
// Created by 1918 on 04-Feb-18.
//

#include <stdio.h>
#include "defs.h"

const int KNIGHT_DIRECTION[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int ROOK_DIRECTION[4] = {-1, -10, 1, 10};
const int BISHOP_DIRECTION[4] = {-9, -11, 11, 9};
const int KING_DIRECTION[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

int sqAttacked(const int sq, const int side, const S_BOARD *pos) {

    int pce, index, t_sq, dir;

    ASSERT(sqOnBoard(sq));
    ASSERT(sideValid(side));
    ASSERT(checkBoard(pos));

    // pawns
    if (side == WHITE) {
        if (pos->pieces[sq - 11] == wP || pos->pieces[sq - 9] == wP) {
            return TRUE;
        }
    } else {
        if (pos->pieces[sq + 11] == bP || pos->pieces[sq + 9] == bP) {
            return TRUE;
        }
    }

    // knights
    for (index = 0; index < 8; ++index) {
        pce = pos->pieces[sq + KNIGHT_DIRECTION[index]];
        if (pce != OFFBOARD && IsKn(pce) && pieceColor[pce] == side) {
            return TRUE;
        }
    }

    // rooks, queens
    for (index = 0; index < 4; ++index) {
        dir = ROOK_DIRECTION[index];
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];
        while (pce != OFFBOARD) {
            if (pce != EMPTY) {
                if (IsRQ(pce) && pieceColor[pce] == side) {
                    return TRUE;
                }
                break;
            }
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    // bishops, queens
    for (index = 0; index < 4; ++index) {
        dir = BISHOP_DIRECTION[index];
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];
        while (pce != OFFBOARD) {
            if (pce != EMPTY) {
                if (IsBQ(pce) && pieceColor[pce] == side) {
                    return TRUE;
                }
                break;
            }
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    // kings
    for (index = 0; index < 8; ++index) {
        pce = pos->pieces[sq + KING_DIRECTION[index]];
        if (pce != OFFBOARD && IsKi(pce) && pieceColor[pce] == side) {
            return TRUE;
        }
    }

    return FALSE;
}