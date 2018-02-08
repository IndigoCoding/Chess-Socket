//
// Created by 1918 on 05-Feb-18.
//

#include "defs.h"

int sqOnBoard(const int sq) {
    return filesBoard[sq] == OFFBOARD ? 0 : 1;
}

int sideValid(const int side) {
    return (side == WHITE || side == BLACK) ? 1 : 0;
}

int fileRankValid(const int fr) {
    return (fr >= 0 && fr <= 7) ? 1 : 0;
}

int pieceValidEmpty(const int pce) {
    return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

int pieceValid(const int pce) {
    return (pce >= wP && pce <= bK) ? 1 : 0;
}