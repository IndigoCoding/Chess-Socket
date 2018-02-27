//
// Created by thanhnn on 2/11/2018.
//

#ifndef CHESS_DRAW_H
#define CHESS_DRAW_H

#include "SDL.h"
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int BOARD_WIDTH;
extern const int BOARD_HEIGHT;

typedef enum {
    NO_PIECE,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_BISHOP,
    BLACK_KNIGHT,
    BLACK_ROOK,
    BLACK_PAWN,
    WHITE_KING,
    WHITE_QUEEN,
    WHITE_BISHOP,
    WHITE_KNIGHT,
    WHITE_ROOK,
    WHITE_PAWN
} Piece;

typedef enum {
    WHITE_TURN,
    BLACK_TURN,
    UNDO,
    SURRENDER
} Button_type;

typedef enum {
    NO_COLOR,
    WHITE_COLOR,
    GRAY_COLOR,
} Color;

extern SDL_Rect squares[];
extern Piece pieces[];
extern Color colors[];

extern SDL_Rect turn_button;
extern SDL_Rect undo_button;
extern SDL_Rect surrender_button;

//The window we'll be rendering to
extern SDL_Window *gWindow;

//The window renderer
extern SDL_Renderer *gRenderer;

//Loads individual image as texture
SDL_Texture *loadTexture(char *path);

//Draw border images
void drawBorderImage();

//Draw border lines
void drawBorder();

//Draw board
void drawBoard();

//Draw init pieces
void drawInitPieces();

//Init empty Board();
void initBoard();

//Init SDL Rectangle
void initSDLRect();

//Draw single piece
void drawPiece(Piece piece, int row, int col);

//Draw current board
void drawCurrentBoard();

//Init right buttons
void initRightButtons();

//Draw buttons
void drawButton(Button_type button_type);

//Init right panel
void initRightPanel();

//Draw turn button
void drawTurn(int side);
#endif //CHESS_DRAW_H
