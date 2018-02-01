#include <stdio.h>
#include "defs.h"

#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"

int main() {

    initAll();

    S_BOARD board[1];

    parseFen(START_FEN, board);
    printBoard(board);

    parseFen(FEN1, board);
    printBoard(board);

    parseFen(FEN2, board);
    printBoard(board);

    parseFen(FEN3, board);
    printBoard(board);

    return 0;
}