//
// Created by thanhnn on 2/11/2018.
//

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <mem.h>
#include "move.h"
#include "draw.h"
#include "SDL.h"
#include "../engine/defs.h"
#include "init.h"

int squares_status[100] = {0};
int current_row = 0, current_col = 0;
bool selected = false;

void printBoardInfo() {
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            printf("Position: %d - Has: %d\n", i * 10 + j, pieces[i * 10 - 10 + j]);
        }
    }
}

void handleMoveEvent(int x, int y, S_BOARD *board) {
    if (x > BOARD_WIDTH / 10 && x < BOARD_WIDTH * 9 / 10 && y > BOARD_HEIGHT / 10 && y < BOARD_HEIGHT * 9 / 10) {
        int col = x * 10 / BOARD_WIDTH;
        int row = y * 10 / BOARD_HEIGHT;

        if (!selected && pieces[row * 10 + col] != NO_PIECE) {
            squares_status[row * 10 + col] = 1;
            highLightSquare();
        } else {
            squares_status[row * 10 + col] = 0;
            removeHighLightedSquare();
        }
        if (!selected) {
            if (pieces[row * 10 + col] != NO_PIECE) {
                squares_status[row * 10 + col] = 1;
                highLightSquare();
                selected = 1;
                current_row = row;
                current_col = col;
            }
        } else {
            if (row != current_row || col != current_col) {
                int move = parseMove(convertMove(current_col, current_row, col, row), board);
                if (move == NOMOVE) {
                    Mix_PlayChannel(-1, gHigh, 0);
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Move", "Invalid move", gWindow);
                } else {
                    int done = makeMove(board, move);
                    if (done == TRUE) {
                        engineToGUI(board->pieces);
                        printf("Move executed: %s\n", convertMove(current_col, current_row, col, row));

                        Mix_PlayChannel(-1, gLow, 0);

                        //Change turn
                        drawTurn(sideChar[board->side]);
                        SDL_RenderPresent(gRenderer);

                        if (isCheckmated(board)){
                            Mix_PlayChannel(-1, gHigh, 0);
                            if (sideChar[board->side] == 'b'){
                                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "WIN", "WHITE WIN", gWindow);
                            }
                            if (sideChar[board->side] == 'w'){
                                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "WIN", "BLACK WIN", gWindow);
                            }

                        }
                    } else {
                        Mix_PlayChannel(-1, gHigh, 0);
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Move", "Wrong move!", gWindow);
                    }
                }
                drawCurrentBoard();

                squares_status[current_row * 10 + current_col] = 0;
                selected = 0;
                current_row = 0;
                current_col = 0;
            } else {
//                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Move error", "Can't stand still", gWindow);
                squares_status[current_row * 10 + current_col] = 0;
                removeHighLightedSquare();
                selected = 0;
                current_row = 0;
                current_col = 0;
            }
        }
        return;
    } else {
        if (x > SCREEN_WIDTH * 11 / 15 && x < SCREEN_WIDTH * 14 / 15 && y > SCREEN_HEIGHT * 4 / 10 &&
            y < SCREEN_HEIGHT * 5 / 10) {
            printf("CLICKED on undo button\n");
            handleUndoButton(board);
        }
        return;
    }
}

//Handle undo button
void handleUndoButton(S_BOARD *board) {
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(gRenderer, &undo_button);
    SDL_RenderPresent(gRenderer);

    takeMove(board);
    engineToGUI(board->pieces);
    SDL_Delay(1000);

    Mix_PlayChannel(-1, gScratch, 0);

    drawButton(UNDO);
    //Change turn
    drawTurn(sideChar[board->side]);

    drawCurrentBoard();
}

void removeHighLightedSquare() {
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            if (squares_status[i * 10 + j] == 0) {
                if (colors[i * 10 + j] == GRAY_COLOR)
                    SDL_SetRenderDrawColor(gRenderer, 0xCF, 0xCF, 0xCF, 0xFF);
                else
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderDrawRect(gRenderer, &squares[i * 10 + j]);
            }
        }
    }
    SDL_RenderPresent(gRenderer);
}

void highLightSquare() {
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            if (squares_status[i * 10 + j] == 1) {
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderDrawRect(gRenderer, &squares[i * 10 + j]);
            }
        }
    }
    SDL_RenderPresent(gRenderer);
}

char *convertMove(int s_col, int s_row, int d_col, int d_row) {
    char *move = malloc(5);
    sprintf(move, "%c%d%c%d", 96 + s_col, 9 - s_row, 96 + d_col, 9 - d_row);
    return move;
}

void changePieces(int s_col, int s_row, int d_col, int d_row) {
    Piece tempo = pieces[s_row * 10 + s_col];
    pieces[s_row * 10 + s_col] = NO_PIECE;
    pieces[d_row * 10 + d_col] = tempo;
}

void engineToGUI(int b_pieces[]) {
    for (int i = 2; i < 10; i++) {
        for (int j = 1; j < 9; j++) {
            switch (b_pieces[110 - i * 10 + j]) {
                case wP:
                    pieces[i * 10 - 10 + j] = WHITE_PAWN;
                    break;
                case wN:
                    pieces[i * 10 - 10 + j] = WHITE_KNIGHT;
                    break;
                case wR:
                    pieces[i * 10 - 10 + j] = WHITE_ROOK;
                    break;
                case wQ:
                    pieces[i * 10 - 10 + j] = WHITE_QUEEN;
                    break;
                case wK:
                    pieces[i * 10 - 10 + j] = WHITE_KING;
                    break;
                case wB:
                    pieces[i * 10 - 10 + j] = WHITE_BISHOP;
                    break;
                case bP:
                    pieces[i * 10 - 10 + j] = BLACK_PAWN;
                    break;
                case bN:
                    pieces[i * 10 - 10 + j] = BLACK_KNIGHT;
                    break;
                case bR:
                    pieces[i * 10 - 10 + j] = BLACK_ROOK;
                    break;
                case bQ:
                    pieces[i * 10 - 10 + j] = BLACK_QUEEN;
                    break;
                case bK:
                    pieces[i * 10 - 10 + j] = BLACK_KING;
                    break;
                case bB:
                    pieces[i * 10 - 10 + j] = BLACK_BISHOP;
                    break;
                case EMPTY:
                    pieces[i * 10 - 10 + j] = NO_PIECE;
                    break;
                default:
                    break;
            }
        }
    }
}