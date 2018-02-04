//
// Created by 1918 on 04-Feb-18.
//

#include "defs.h"

const int KNIGHT_DIRECTION[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int ROCK_DIRECTION[4] = {-1, -10, 1, 10};
const int BISHOP_DIRECTION[4] = {-9, -11, 11, 9};
const int KING_DIRECTION[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

int SqAttacked(const int sq, const int side, const S_BOARD *pos) {

    int pce, index, t_sq, dir;

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


}