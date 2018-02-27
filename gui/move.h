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
void handleMoveEvent(int x, int y, S_BOARD *board);
char *convertMove(int s_col, int s_row, int d_col, int d_row);
void changePieces(int s_col, int s_row, int d_col, int d_row);
void engineToGUI(int b_pieces[]);

//Handle undo button
void handleUndoButton(S_BOARD *board);
#endif //CHESS_MOVE_H
