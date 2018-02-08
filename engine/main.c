#include <stdio.h>
#include "defs.h"

#define PERFTFEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int main() {

    initAll();

    S_BOARD board[1];
    S_MOVELIST list[1];

//    parseFen(START_FEN,board);
    parseFen(PERFTFEN,board);
    perftTest(5,board);
    return 0;
}