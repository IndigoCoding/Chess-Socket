//
// Created by 1918 on 31-Jan-18.
//

#include "defs.h"

void updateListsMaterial(S_BOARD *pos) {

    int piece, sq, index, colour;

    for (index = 0; index < BOARD_SQ_NUM; ++index) {
        sq = index;
        piece = pos->pieces[index];
        if (piece != OFFBOARD && piece != EMPTY) {
            colour = pieceColor[piece];

            if (pieceBig[piece] == TRUE) pos->bigPiece[colour]++;
            if (pieceMinor[piece] == TRUE) pos->minorPiece[colour]++;
            if (pieceMajor[piece] == TRUE) pos->majorPiece[colour]++;

            pos->material[colour] += pieceValue[piece];

            // piece list
            // pList[wP][0] = a1;
            // pList[wP][1] = a2;

            pos->pieceList[piece][pos->pieceNum[piece]] = sq;
            pos->pieceNum[piece]++;

            if (piece == wK) pos->KingSq[WHITE] = sq;
            if (piece == bK) pos->KingSq[BLACK] = sq;
        }
    }

}

int parseFen(char *fen, S_BOARD *pos) {

    ASSERT(fen != NULL);
    ASSERT(pos != NULL);

    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;
    int count = 0;
    int i = 0;
    int sq64 = 0;
    int sq120 = 0;

    resetBoard(pos);

    while ((rank >= RANK_1) && *fen) {
        count = 1;
        switch (*fen) {
            case 'p':
                piece = bP;
                break;
            case 'r':
                piece = bR;
                break;
            case 'n':
                piece = bN;
                break;
            case 'b':
                piece = bB;
                break;
            case 'k':
                piece = bK;
                break;
            case 'q':
                piece = bQ;
                break;
            case 'P':
                piece = wP;
                break;
            case 'R':
                piece = wR;
                break;
            case 'N':
                piece = wN;
                break;
            case 'B':
                piece = wB;
                break;
            case 'K':
                piece = wK;
                break;
            case 'Q':
                piece = wQ;
                break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return -1;
        }

        for (i = 0; i < count; i++) {
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }
            file++;
        }
        fen++;
    }

    ASSERT(*fen == 'w' || *fen == 'b');

    pos->side = (*fen == 'w') ? WHITE : BLACK;
    fen += 2;

    for (i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
        switch (*fen) {
            case 'K':
                pos->castlePermission |= WKCA;
                break;
            case 'Q':
                pos->castlePermission |= WQCA;
                break;
            case 'k':
                pos->castlePermission |= BKCA;
                break;
            case 'q':
                pos->castlePermission |= BQCA;
                break;
            default:
                break;
        }
        fen++;
    }
    fen++;

    ASSERT(pos->castlePermission >= 0 && pos->castlePermission <= 15);

    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file >= FILE_A && file <= FILE_H);
        ASSERT(rank >= RANK_1 && rank <= RANK_8);

        pos->enPas = FR2SQ(file, rank);
    }

    pos->posKey = generatePosKey(pos);

    return 0;
}

void resetBoard(S_BOARD *pos) {

    int index = 0;

    for (index = 0; index < BOARD_SQ_NUM; ++index) {
        pos->pieces[index] = OFFBOARD;
    }

    for (index = 0; index < 64; ++index) {
        pos->pieces[SQ120(index)] = EMPTY;
    }

    for (index = 0; index < 3; ++index) {
        pos->bigPiece[index] = 0;
        pos->majorPiece[index] = 0;
        pos->minorPiece[index] = 0;
        pos->pawns[index] = 0ULL;
    }

    for (index = 0; index < 13; ++index) {
        pos->pieceNum[index] = 0;
    }

    pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

    pos->side = BOTH;
    pos->enPas = NO_SQ;
    pos->fiftyMove = 0;

    pos->play = 0;
    pos->hisPlay = 0;

    pos->castlePermission = 0;

    pos->posKey = 0ULL;

}

void printBoard(const S_BOARD *pos) {

    int sq, file, rank, piece;

    printf("\nGame Board:\n\n");

    for (rank = RANK_8; rank >= RANK_1; rank--) {
        printf("%d  ", rank + 1);
        for (file = FILE_A; file <= FILE_H; file++) {
            sq = FR2SQ(file, rank);
            piece = pos->pieces[sq];
            printf("%3c", pieceChar[piece]);
        }
        printf("\n");
    }

    printf("\n   ");
    for (file = FILE_A; file <= FILE_H; file++) {
        printf("%3c", 'a' + file);
    }
    printf("\n");
    printf("side:%c\n", sideChar[pos->side]);
    printf("enPas:%d\n", pos->enPas);
    printf("castle:%c%c%c%c\n",
           pos->castlePermission & WKCA ? 'K' : '-',
           pos->castlePermission & WQCA ? 'Q' : '-',
           pos->castlePermission & BKCA ? 'k' : '-',
           pos->castlePermission & BQCA ? 'q' : '-'
    );
    printf("PosKey:%llX\n", pos->posKey);
}