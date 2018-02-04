//
// Created by 1918 on 31-Jan-18.
//

#include "defs.h"

int checkBoard(const S_BOARD *pos) {

    int t_pceNum[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int t_bigPce[2] = {0, 0};
    int t_majPce[2] = {0, 0};
    int t_minPce[2] = {0, 0};
    int t_material[2] = {0, 0};

    int sq64, t_piece, t_pce_num, sq120, colour, pcount;

    U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

    t_pawns[WHITE] = pos->pawns[WHITE];
    t_pawns[BLACK] = pos->pawns[BLACK];
    t_pawns[BOTH] = pos->pawns[BOTH];

    // check piece lists
    for (t_piece = wP; t_piece <= bK; ++t_piece) {
        for (t_pce_num = 0; t_pce_num < pos->pieceNum[t_piece]; ++t_pce_num) {
            sq120 = pos->pieceList[t_piece][t_pce_num];
            ASSERT(pos->pieces[sq120] == t_piece);
        }
    }

    // check piece count and other counters
    for (sq64 = 0; sq64 < 64; ++sq64) {
        sq120 = SQ120(sq64);
        t_piece = pos->pieces[sq120];
        t_pceNum[t_piece]++;
        colour = pieceColor[t_piece];
        if (pieceBig[t_piece] == TRUE) t_bigPce[colour]++;
        if (pieceMinor[t_piece] == TRUE) t_minPce[colour]++;
        if (pieceMajor[t_piece] == TRUE) t_majPce[colour]++;

        t_material[colour] += pieceValue[t_piece];
    }

    for (t_piece = wP; t_piece <= bK; ++t_piece) {
        ASSERT(t_pceNum[t_piece] == pos->pieceNum[t_piece]);
    }

    // check bitboards count
    pcount = COUNT(t_pawns[WHITE]);
    ASSERT(pcount == pos->pieceNum[wP]);
    pcount = COUNT(t_pawns[BLACK]);
    ASSERT(pcount == pos->pieceNum[bP]);
    pcount = COUNT(t_pawns[BOTH]);
    ASSERT(pcount == (pos->pieceNum[bP] + pos->pieceNum[wP]));

    // check bitboards squares
    while (t_pawns[WHITE]) {
        sq64 = POP(&t_pawns[WHITE]);
        ASSERT(pos->pieces[SQ120(sq64)] == wP);
    }

    while (t_pawns[BLACK]) {
        sq64 = POP(&t_pawns[BLACK]);
        ASSERT(pos->pieces[SQ120(sq64)] == bP);
    }

    while (t_pawns[BOTH]) {
        sq64 = POP(&t_pawns[BOTH]);
        ASSERT((pos->pieces[SQ120(sq64)] == bP) || (pos->pieces[SQ120(sq64)] == wP));
    }

    ASSERT(t_material[WHITE] == pos->material[WHITE] && t_material[BLACK] == pos->material[BLACK]);
    ASSERT(t_minPce[WHITE] == pos->minorPiece[WHITE] && t_minPce[BLACK] == pos->minorPiece[BLACK]);
    ASSERT(t_majPce[WHITE] == pos->majorPiece[WHITE] && t_majPce[BLACK] == pos->majorPiece[BLACK]);
    ASSERT(t_bigPce[WHITE] == pos->bigPiece[WHITE] && t_bigPce[BLACK] == pos->bigPiece[BLACK]);

    ASSERT(pos->side == WHITE || pos->side == BLACK);
    ASSERT(generatePosKey(pos) == pos->posKey);

    ASSERT(pos->enPas == NO_SQ || (ranksBoard[pos->enPas] == RANK_6 && pos->side == WHITE)
           || (ranksBoard[pos->enPas] == RANK_3 && pos->side == BLACK));

    ASSERT(pos->pieces[pos->KingSq[WHITE]] == wK);
    ASSERT(pos->pieces[pos->KingSq[BLACK]] == bK);

    return TRUE;
}

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

            pos->pieceList[piece][pos->pieceNum[piece]] = sq;
            pos->pieceNum[piece]++;

            if (piece == wK) pos->KingSq[WHITE] = sq;
            if (piece == bK) pos->KingSq[BLACK] = sq;

            if (piece == wP) {
                SETBIT(pos->pawns[WHITE], SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            } else if (piece == bP) {
                SETBIT(pos->pawns[BLACK], SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            }
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

    updateListsMaterial(pos);

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