#include <stdio.h>
#include "defs.h"

//
// Created by 1918 on 27-Jan-18.
//

#define RAND_64 (	(U64)rand() | \
					(U64)rand() << 15 | \
					(U64)rand() << 30 | \
					(U64)rand() << 45 | \
					((U64)rand() & 0xf) << 60    )

int sq120ToSq64[BOARD_SQ_NUM];
int sq64ToSq120[64];
U64 setMask[64];
U64 clearMask[64];

U64 pieceKeys[13][120];
U64 sideKey;
U64 castleKeys[16];

int filesBoard[BOARD_SQ_NUM];
int ranksBoard[BOARD_SQ_NUM];

void initFilesRanksBoard() {
    int i = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;

    for (i = 0; i < BOARD_SQ_NUM; i++) {
        filesBoard[i] = OFFBOARD;
        ranksBoard[i] = OFFBOARD;
    }

    for (rank = RANK_1; rank <= RANK_8; rank++) {
        for (file = FILE_A; file <= FILE_H; file++) {
            sq = FR2SQ(file, rank);
            filesBoard[sq] = file;
            ranksBoard[sq] = rank;
        }
    }
}

void initHashKeys() {

    int index = 0;
    int index2 = 0;
    for(index = 0; index < 13; ++index) {
        for(index2 = 0; index2 < 120; ++index2) {
            pieceKeys[index][index2] = RAND_64;
        }
    }
    sideKey = RAND_64;
    for(index = 0; index < 16; ++index) {
        castleKeys[index] = RAND_64;
    }

}

void initBitMask() {
    int index = 0;
    for(index = 0; index < 64; index++) {
        setMask[index] = 0ULL;
        clearMask[index] = 0ULL;
    }

    for(index = 0; index < 64; index++) {
        setMask[index] |= (1ULL << index);
        clearMask[index] = ~setMask[index];
    }
}

void initSq120To64() {
    int i = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;
    for (i = 0; i < BOARD_SQ_NUM; i++) {
        sq120ToSq64[i] = 65;
    }

    for (i = 0; i < 64; i++) {
        sq64ToSq120[i] = 120;
    }

    for (rank = RANK_1; rank <= RANK_8; rank++) {
        for (file = FILE_A; file <= FILE_H; file++) {
            sq = FR2SQ(file, rank);
            sq64ToSq120[sq64] = sq;
            sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }
}

void initAll() {
    initSq120To64();
    initBitMask();
    initHashKeys();
    initFilesRanksBoard();
}