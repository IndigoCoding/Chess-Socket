//
// Created by 1918 on 27-Jan-18.
//

#ifndef CHESS_DEFS_H
#define CHESS_DEFS_H

#include "stdlib.h"
#include <windows.h>
//#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

typedef unsigned long long U64;

#define NAME "Chess 1.0"
#define BOARD_SQ_NUM 120

#define MAX_GAME_MOVES 2048
#define MAX_POSITION_MOVES 256

#define START_FEN  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

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
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

//enum {
//    FALSE, TRUE
//};

// represent by 4 bit integer
enum {
    WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8
};

typedef struct {
    int move;
    int score;
} S_MOVE;

typedef struct {
    S_MOVE moves[MAX_POSITION_MOVES];
    int count;
} S_MOVELIST;

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
    int kingSq[2];
    int side; // current side to move
    int enPas;
    int fiftyMove;
    int play;
    int hisPlay;
    U64 posKey;
    int pieceNum[13];
    int bigPiece[2];
    int majorPiece[2];
    int minorPiece[2];
    int material[2];
    int castlePermission;
    S_UNDO history[MAX_GAME_MOVES];
    int pieceList[13][10];
} S_BOARD;

//game move
/*
0000 0000 0000 0000 0000 0111 1111 -> From 0x7F
0000 0000 0000 0011 1111 1000 0000 -> To >> 7, 0x7F
0000 0000 0011 1100 0000 0000 0000 -> Captured >> 14, 0xF
0000 0000 0100 0000 0000 0000 0000 -> EP 0x40000
0000 0000 1000 0000 0000 0000 0000 -> Pawn Start 0x80000
0000 1111 0000 0000 0000 0000 0000 -> Promoted Piece >> 20, 0xF
0001 0000 0000 0000 0000 0000 0000 -> Castle 0x1000000
*/

#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m)>>20) & 0xF)

#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7C000
#define MFLAGPROM 0xF00000

#define NOMOVE 0

// MACRO
#define FR2SQ(f, r) ( (21 + (f) ) + ( (r) * 10 ) )
#define SQ64(sq120) (sq120ToSq64[(sq120)])
#define SQ120(sq64) (sq64ToSq120[(sq64)])
#define POP(b) popBit(b)
#define COUNT(b) countBits(b)
#define CLEARBIT(bb,sq) ((bb) &= clearMask[(sq)])
#define SETBIT(bb,sq) ((bb) |= setMask[(sq)])
#define IsBQ(p) (pieceBishopQueen[(p)])
#define IsRQ(p) (pieceRookQueen[(p)])
#define IsKn(p) (pieceKnight[(p)])
#define IsKi(p) (pieceKing[(p)])


extern int sq120ToSq64[BOARD_SQ_NUM];
extern int sq64ToSq120[64];
extern U64 setMask[64];
extern U64 clearMask[64];
extern U64 pieceKeys[13][120];
extern U64 sideKey;
extern U64 castleKeys[16];
extern char pieceChar[];
extern char sideChar[];
extern char rankChar[];
extern char fileChar[];

extern int pieceBig[13];
extern int pieceMajor[13];
extern int pieceMinor[13];
extern int pieceValue[13];
extern int pieceColor[13];

extern int filesBoard[BOARD_SQ_NUM];
extern int ranksBoard[BOARD_SQ_NUM];

extern int pieceKnight[13];
extern int pieceKing[13];
extern int pieceRookQueen[13];
extern int pieceBishopQueen[13];
extern int pieceSlides[13];
extern int piecePawn[13];

// init.c
extern void initAll();
extern void initFilesRanksBoard();

// bitboard.c
extern void printBitBoard(U64 bb);
extern int popBit(U64 *bb);
extern int countBits(U64 b);

// hashkeys.c
extern U64 generatePosKey(const S_BOARD *pos);
#endif //CHESS_DEFS_H

// board.c
extern void resetBoard(S_BOARD *pos);
extern int parseFen(char *fen, S_BOARD *pos);
extern void printBoard(const S_BOARD *pos);
extern void updateListsMaterial(S_BOARD *pos);
extern int checkBoard(const S_BOARD *pos);

// attack.c
extern int sqAttacked(const int sq, const int side, const S_BOARD *pos);

// io.c
extern char *printSquare(const int sq);
extern char *printMove(const int move);
extern int parseMove(char* ptrChar, S_BOARD *pos);

// validate.c
extern int sqOnBoard(const int sq);
extern int sideValid(const int side);
extern int fileRankValid(const int fr);
extern int pieceValidEmpty(const int pce);
extern int pieceValid(const int pce);

// movegen.c
extern void generateAllMoves(const S_BOARD *pos, S_MOVELIST *list);
extern S_MOVELIST generatePieceMoves(S_BOARD *pos, const int piecePos);

// makemove.c
extern int makeMove(S_BOARD *pos, int move);
extern int takeMove(S_BOARD *pos);

// perft.c
extern void perftTest(int depth, S_BOARD *pos);

// wincheck.c
extern int isCheckmated(S_BOARD *pos);