//
// Created by 1918 on 27-Jan-18.
//

#ifndef CHESS_DEFS_H
#define CHESS_DEFS_H

#include "stdlib.h"

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT (n) \
if(!(n)) { \
printf("%s - Failed", #n); \
printf("On %s ", __DATE__); \
printf("At %s ", __TIME__); \
printf("In File %s ", __FILE__); \
printf("At Line %d\n", __LINE__); \
exit(1);}
#endif

typedef unsigned long long U64;

#define NAME "Chess 1.0"
#define BOARD_SQ_NUM 120

#define MAX_GAME_MOVES 2048

enum {
    EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK
};

enum {
    FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE
};

enum {
    RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE
};

enum {
    WHITE, BLACK, BOTH
};

enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};

enum {
    FALSE, TRUE
};

// represent by 4 bit integer
enum {
    KWCA = 1, WQCA = 2, BKCA = 4, BQCA = 8
};

typedef struct {
    int move;
    int castlePermission;
    int enPas;
    int fiftyMove;
    U64 posKey;
} S_UNDO;

typedef struct {
    int pieces[BOARD_SQ_NUM];
    U64 pawns[3];
    int KingSq[2];
    int side; // current side to move
    int enPas;
    int fiftyMove;
    int play;
    int hisPlay;
    U64 posKey;
    int pieceNum[13];
    int bigPiece[3];
    int majorPiece[3];
    int minorPiece[3];
    int castlePermission;
    S_UNDO history[MAX_GAME_MOVES];
    int pieceList[13][10];
} S_BOARD;

#define FR2SQ(f, r) ( (21 + (f) ) + ( (r) * 10 ) )
#define SQ64(sq120) sq120ToSq64[sq120]
#define POP(b) popBit(b)
#define COUNT(b) countBits(b)

extern int sq120ToSq64[BOARD_SQ_NUM];
extern int sq64ToSq120[64];

/*
 * init.c
 */
extern void initAll();

/*
 * bitboard.c
 */
extern void printBitBoard(U64 bitboard);
extern int popBit(U64 *bb);
extern int countBits(U64 b);

#endif //CHESS_DEFS_H

