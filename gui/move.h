//
// Created by thanhnn on 2/11/2018.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "../engine/defs.h"

extern int squares_status[];
void printBoardInfo();

void highLightSquare();
void removeHighLightedSquare();
//void handleMoveEvent(int x, int y, S_BOARD *board);
char* handleMoveEvent(int x, int y, S_BOARD *board);
void convertMove(int s_col, int s_row, int d_col, int d_row, char* move);
void changePieces(int s_col, int s_row, int d_col, int d_row);
void engineToGUI(int b_pieces[]);
int handleSurrenderButton(int x, int y);

//Handle undo button
void handleUndoButton(S_BOARD *board);
#endif //CHESS_MOVE_H
