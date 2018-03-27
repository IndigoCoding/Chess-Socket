#include <stdio.h>
#include "defs.h"

#define PERFTFEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int main() {

    initAll();

    S_BOARD board[1];

    parseFen(START_FEN,board);
//    parseFen(PERFTFEN,board);
    perftTest(5,board);
    char input[6];
    int move = NOMOVE;
//    while (TRUE) {
//        printBoard(board);
//        printf("Enter move: ");
//        fgets(input, 6, stdin);
//        if (input[0] == 'q') {
//            break;
//        } else if (input[0] == 't') {
//            takeMove(board);
//        } else {
//            move = parseMove(input, board);
//            if (move != NOMOVE) {
//                makeMove(board, move);
//                if (isCheckmated(board)) {
//                    printf("CHECKMATED\n");
//                    return 1;
//                }
//            }
//        }
//        fflush(stdin);
//    }
    // TODO huong dan su dung ham:
    // tao 1 list moi
    S_MOVELIST list[1];
    // goi generatePieceMove
    // dung list->count de iterate qua tung move trong list
    generatePieceMoves(board, list, 92);
    printf("SIZE %d", list->count);
//    takeMove(board);
    return 0;

}