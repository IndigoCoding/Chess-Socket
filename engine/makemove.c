//
// Created by 1918 on 08-Feb-18.
//

#include <stdio.h>
#include "defs.h"

#define HASH_PIECE(pce, sq) (pos->posKey ^= (pieceKeys[(pce)][(sq)]))
#define HASH_CASTLE (pos->posKey ^= (castleKeys[(pos->castlePermission)]))
#define HASH_SIDE (pos->posKey ^= (sideKey))
#define HASH_ENPAS (pos->posKey ^= (pieceKeys[EMPTY][(pos->enPas)]))

const int castlePermission[120] = {
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 7, 15, 15, 15, 3, 15, 15, 11, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

static void clearPiece(const int sq, S_BOARD *pos) {

    ASSERT(sqOnBoard(sq));

    int pce = pos->pieces[sq];

    ASSERT(pieceValid(pce));

    int col = pieceColor[pce];
    int index = 0;
    int t_pceNum = -1;

    HASH_PIECE(pce, sq);

    pos->pieces[sq] = EMPTY;
    pos->material[col] -= pieceValue[pce];

    if (pieceBig[pce]) {
        pos->bigPiece[col]--;
        if (pieceMajor[pce]) {
            pos->majorPiece[col]--;
        } else {
            pos->minorPiece[col]--;
        }
    } else {
        CLEARBIT(pos->pawns[col], SQ64(sq));
        CLEARBIT(pos->pawns[BOTH], SQ64(sq));
    }

    for (index = 0; index < pos->pieceNum[pce]; ++index) {
        if (pos->pieceList[pce][index] == sq) {
            t_pceNum = index;
            break;
        }
    }

    ASSERT(t_pceNum != -1);

    pos->pieceNum[pce]--;

    pos->pieceList[pce][t_pceNum] = pos->pieceList[pce][pos->pieceNum[pce]];
}

static void addPiece(const int sq, S_BOARD *pos, const int pce) {

    ASSERT(pieceValid(pce));
    ASSERT(sqOnBoard(sq));

    int col = pieceColor[pce];

    HASH_PIECE(pce, sq);

    pos->pieces[sq] = pce;

    if (pieceBig[pce]) {
        pos->bigPiece[col]++;
        if (pieceMajor[pce]) {
            pos->majorPiece[col]++;
        } else {
            pos->minorPiece[col]++;
        }
    } else {
        SETBIT(pos->pawns[col], SQ64(sq));
        SETBIT(pos->pawns[BOTH], SQ64(sq));
    }

    pos->material[col] += pieceValue[pce];
    pos->pieceList[pce][pos->pieceNum[pce]++] = sq;

}

static void movePiece(const int from, const int to, S_BOARD *pos) {

    ASSERT(sqOnBoard(from));
    ASSERT(sqOnBoard(to));

    int index = 0;
    int pce = pos->pieces[from];
    int col = pieceColor[pce];

#ifdef DEBUG
    int t_PieceNum = FALSE;
#endif

    HASH_PIECE(pce, from);
    pos->pieces[from] = EMPTY;

    HASH_PIECE(pce, to);
    pos->pieces[to] = pce;

    if (!pieceBig[pce]) {
        CLEARBIT(pos->pawns[col], SQ64(from));
        CLEARBIT(pos->pawns[BOTH], SQ64(from));
        SETBIT(pos->pawns[col], SQ64(to));
        SETBIT(pos->pawns[BOTH], SQ64(to));
    }

    for (index = 0; index < pos->pieceNum[pce]; ++index) {
        if (pos->pieceList[pce][index] == from) {
            pos->pieceList[pce][index] = to;
#ifdef DEBUG
            t_PieceNum = TRUE;
#endif
            break;
        }
    }
    ASSERT(t_PieceNum);
}


void takeMove(S_BOARD *pos) {

    ASSERT(checkBoard(pos));

    pos->hisPlay--;
    pos->play--;

    int move = pos->history[pos->hisPlay].move;
    int from = FROMSQ(move);
    int to = TOSQ(move);

    ASSERT(sqOnBoard(from));
    ASSERT(sqOnBoard(to));

    if (pos->enPas != NO_SQ) HASH_ENPAS;
    HASH_CASTLE;

    pos->castlePermission = pos->history[pos->hisPlay].castlePermission;
    pos->fiftyMove = pos->history[pos->hisPlay].fiftyMove;
    pos->enPas = pos->history[pos->hisPlay].enPas;

    if (pos->enPas != NO_SQ) HASH_ENPAS;
    HASH_CASTLE;

    pos->side ^= 1;
    HASH_SIDE;

    if (MFLAGEP & move) {
        if (pos->side == WHITE) {
            addPiece(to - 10, pos, bP);
        } else {
            addPiece(to + 10, pos, wP);
        }
    } else if (MFLAGCA & move) {
        switch (to) {
            case C1:
                movePiece(D1, A1, pos);
                break;
            case C8:
                movePiece(D8, A8, pos);
                break;
            case G1:
                movePiece(F1, H1, pos);
                break;
            case G8:
                movePiece(F8, H8, pos);
                break;
            default:
                ASSERT(FALSE);
                break;
        }
    }

    movePiece(to, from, pos);

    if (pieceKing[pos->pieces[from]]) {
        pos->KingSq[pos->side] = from;
    }

    int captured = CAPTURED(move);
    if (captured != EMPTY) {
        ASSERT(pieceValid(captured));
        addPiece(to, pos, captured);
    }

    if (PROMOTED(move) != EMPTY) {
        ASSERT(pieceValid(PROMOTED(move)) && !piecePawn[PROMOTED(move)]);
        clearPiece(from, pos);
        addPiece(from, pos, (pieceColor[PROMOTED(move)] == WHITE ? wP : bP));
    }

    ASSERT(checkBoard(pos));
}

int makeMove(S_BOARD *pos, int move) {

    ASSERT(checkBoard(pos));

    int from = FROMSQ(move);
    int to = TOSQ(move);
    int side = pos->side;

    ASSERT(sqOnBoard(from));
    ASSERT(sqOnBoard(to));
    ASSERT(sideValid(side));
    ASSERT(pieceValid(pos->pieces[from]));

    pos->history[pos->hisPlay].posKey = pos->posKey;

    if (move & MFLAGEP) {
        if (side == WHITE) {
            clearPiece(to - 10, pos);
        } else {
            clearPiece(to + 10, pos);
        }
    } else if (move & MFLAGCA) {
        switch (to) {
            case C1:
                movePiece(A1, D1, pos);
                break;
            case C8:
                movePiece(A8, D8, pos);
                break;
            case G1:
                movePiece(H1, F1, pos);
                break;
            case G8:
                movePiece(H8, F8, pos);
                break;
            default:
                ASSERT(FALSE);
                break;
        }
    }

    if (pos->enPas != NO_SQ) HASH_ENPAS;
    HASH_CASTLE;

    pos->history[pos->hisPlay].move = move;
    pos->history[pos->hisPlay].fiftyMove = pos->fiftyMove;
    pos->history[pos->hisPlay].enPas = pos->enPas;
    pos->history[pos->hisPlay].castlePermission = pos->castlePermission;

    pos->castlePermission &= castlePermission[from];
    pos->castlePermission &= castlePermission[to];
    pos->enPas = NO_SQ;

    HASH_CASTLE;

    int captured = CAPTURED(move);
    pos->fiftyMove++;

    if (captured != EMPTY) {
        ASSERT(pieceValid(captured));
        clearPiece(to, pos);
        pos->fiftyMove = 0;
    }

    pos->hisPlay++;
    pos->play++;

    if (piecePawn[pos->pieces[from]]) {
        pos->fiftyMove = 0;
        if (move & MFLAGPS) {
            if (side == WHITE) {
                pos->enPas = from + 10;
                ASSERT(ranksBoard[pos->enPas] == RANK_3);
            } else {
                pos->enPas = from - 10;
                ASSERT(ranksBoard[pos->enPas] == RANK_6);
            }
            HASH_ENPAS;
        }
    }

    movePiece(from, to, pos);

    int prPce = PROMOTED(move);
    if (prPce != EMPTY) {
        ASSERT(pieceValid(prPce) && !piecePawn[prPce]);
        clearPiece(to, pos);
        addPiece(to, pos, prPce);
    }

    if (pieceKing[pos->pieces[to]]) {
        pos->KingSq[pos->side] = to;
    }

    pos->side ^= 1;
    HASH_SIDE;

    ASSERT(checkBoard(pos));


    if (sqAttacked(pos->KingSq[side], pos->side, pos)) {
        takeMove(pos);
        return FALSE;
    }

    return TRUE;

}