//
// Created by thanhnn on 2/11/2018.
//

#include <SDL_render.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

const int BOARD_WIDTH = 400;
const int BOARD_HEIGHT = 400;

SDL_Rect squares[100];
Piece pieces[100] = {NO_PIECE};
Color colors[100] = {NO_COLOR};
SDL_Rect turn_button;
SDL_Rect undo_button;
SDL_Rect surrender_button;


//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

//Current displayed texture
SDL_Texture *gTexture = NULL;

//LoadTexture
SDL_Texture *loadTexture(char *path) {
    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

//Draw border
void drawBorder() {
    //Draw black top border
    SDL_SetRenderDrawColor(gRenderer, 0xCF, 0xCF, 0xCF, 0xFF);
    SDL_RenderDrawLine(gRenderer, 0, 0, BOARD_WIDTH, 0);

    //Draw black bottom border
    SDL_SetRenderDrawColor(gRenderer, 0xCF, 0xCF, 0xCF, 0xFF);
    SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT, BOARD_WIDTH, SCREEN_HEIGHT);

    //Draw black left border
    SDL_SetRenderDrawColor(gRenderer, 0xCF, 0xCF, 0xCF, 0xFF);
    SDL_RenderDrawLine(gRenderer, 0, 0, 0, SCREEN_HEIGHT);

    //Draw black right border
    SDL_SetRenderDrawColor(gRenderer, 0xCF, 0xCF, 0xCF, 0xFF);
    SDL_RenderDrawLine(gRenderer, BOARD_WIDTH, 0, BOARD_WIDTH, SCREEN_HEIGHT);
}

//Draw border image
void drawBorderImage() {
    SDL_Rect top_rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT / 10};
    SDL_Rect bottom_rect = {0, BOARD_HEIGHT * 9 / 10, BOARD_WIDTH, BOARD_HEIGHT / 10};
    SDL_Rect left_rect = {0, 0, BOARD_WIDTH / 10, BOARD_HEIGHT};
    SDL_Rect right_rect = {BOARD_WIDTH * 9 / 10, 0, BOARD_WIDTH / 10, BOARD_HEIGHT};

    SDL_Texture *x_border = loadTexture("../gui/Assert/x_border.png");
    SDL_RenderCopy(gRenderer, x_border, NULL, &top_rect);
    SDL_RenderCopy(gRenderer, x_border, NULL, &bottom_rect);
    SDL_DestroyTexture(x_border);

    SDL_Texture *y_border = loadTexture("../gui/Assert/y_border.png");
    SDL_RenderCopy(gRenderer, y_border, NULL, &left_rect);
    SDL_RenderCopy(gRenderer, y_border, NULL, &right_rect);
    SDL_DestroyTexture(y_border);
}

//Init pieces to board
void drawInitPieces() {
    int pos1, pos2, q_pos, k_pos, p_pos1, p_pos2;

    pos1 = 8;
    pos2 = 1;
    q_pos = 4;
    k_pos = 5;
    p_pos1 = 7;
    p_pos2 = 2;

    for (int i = 0; i < 10; i++) {
        //Draw rook
        if (i == 1 || i == 8) {
            drawPiece(WHITE_ROOK, pos1, i);
            drawPiece(BLACK_ROOK, pos2, i);

        }
        //Draw knight
        if (i == 2 || i == 7) {
            drawPiece(WHITE_KNIGHT, pos1, i);
            drawPiece(BLACK_KNIGHT, pos2, i);
        }
        //Draw bishop
        if (i == 3 || i == 6) {
            drawPiece(WHITE_BISHOP, pos1, i);
            drawPiece(BLACK_BISHOP, pos2, i);
        }
        //Draw queen
        if (i == q_pos) {
            drawPiece(WHITE_QUEEN, pos1, i);
            drawPiece(BLACK_QUEEN, pos2, i);
        }
        //Draw king
        if (i == k_pos) {
            drawPiece(WHITE_KING, pos1, i);
            drawPiece(BLACK_KING, pos2, i);
        }

        //Draw pawn
        for (int j = 1; j < 9; j++) {
            drawPiece(WHITE_PAWN, p_pos1, j);
            drawPiece(BLACK_PAWN, p_pos2, j);
        }
    }
}

//Draw piece
void drawPiece(Piece piece, int row, int col) {
    SDL_Texture *concrete;
    switch (piece) {
        case NO_PIECE:
            SDL_DestroyTexture(concrete);
            break;
        case BLACK_KING:
            concrete = loadTexture("../gui/Assert/Chess_kdt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = BLACK_KING;
            break;
        case BLACK_QUEEN:
            concrete = loadTexture("../gui/Assert/Chess_qdt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = BLACK_QUEEN;
            break;
        case BLACK_BISHOP:
            concrete = loadTexture("../gui/Assert/Chess_bdt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = BLACK_BISHOP;
            break;
        case BLACK_KNIGHT:
            concrete = loadTexture("../gui/Assert/Chess_ndt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = BLACK_KNIGHT;
            break;
        case BLACK_ROOK:
            concrete = loadTexture("../gui/Assert/Chess_rdt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = BLACK_ROOK;
            break;
        case BLACK_PAWN:
            concrete = loadTexture("../gui/Assert/Chess_pdt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = BLACK_PAWN;
            break;
        case WHITE_KING:
            concrete = loadTexture("../gui/Assert/Chess_klt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = WHITE_KING;
            break;
        case WHITE_QUEEN:
            concrete = loadTexture("../gui/Assert/Chess_qlt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = WHITE_QUEEN;
            break;
        case WHITE_BISHOP:
            concrete = loadTexture("../gui/Assert/Chess_blt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = WHITE_BISHOP;
            break;
        case WHITE_KNIGHT:
            concrete = loadTexture("../gui/Assert/Chess_nlt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = WHITE_KNIGHT;
            break;
        case WHITE_ROOK:
            concrete = loadTexture("../gui/Assert/Chess_rlt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = WHITE_ROOK;
            break;
        case WHITE_PAWN:
            concrete = loadTexture("../gui/Assert/Chess_plt60.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &squares[row * 10 + col]);
            SDL_DestroyTexture(concrete);
            pieces[row * 10 + col] = WHITE_PAWN;
            break;
        default:
            SDL_DestroyTexture(concrete);
            break;
    }
}

//Draw gray-white board
void drawBoard() {
    for (int i = 1; i < 9; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < 10; j++) {
                if (j == 0 || j == 9) {
                    //
                } else if (j % 2 != 0) {
                    SDL_SetRenderDrawColor(gRenderer, 0xCF, 0xCF, 0xCF, 0xFF);
                    SDL_RenderFillRect(gRenderer, &squares[i * 10 + j]);
                    colors[i * 10 + j] = GRAY_COLOR;
                } else {
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderFillRect(gRenderer, &squares[i * 10 + j]);
                    colors[i * 10 + j] = WHITE_COLOR;
                }
            }
        } else {
            for (int j = 0; j < 10; j++) {
                if (j == 0 || j == 9) {
                    //
                } else if (j % 2 == 0) {
                    SDL_SetRenderDrawColor(gRenderer, 0xCF, 0xCF, 0xCF, 0xFF);
                    SDL_RenderFillRect(gRenderer, &squares[i * 10 + j]);
                    colors[i * 10 + j] = GRAY_COLOR;
                } else {
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderFillRect(gRenderer, &squares[i * 10 + j]);
                    colors[i * 10 + j] = WHITE_COLOR;
                }
            }
        }
    }
}

//Init SDL_Rect
void initSDLRect() {
    for (int i = 0; i < BOARD_HEIGHT; i += BOARD_HEIGHT / 10) {
        for (int j = 0; j < BOARD_WIDTH; j += BOARD_WIDTH / 10) {
            int x = i * 10 / BOARD_HEIGHT;
            int y = j * 10 / BOARD_WIDTH;
            squares[x * 10 + y] = (SDL_Rect) {j, i, BOARD_WIDTH / 10, BOARD_HEIGHT / 10};
        }
    }
}

//Init empty board
void initBoard() {
    drawBorderImage();
    drawBoard();
    drawBorder();
}

//Draw current board
void drawCurrentBoard() {
    initBoard();
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            drawPiece(pieces[i * 10 + j], i, j);
        }
    }
    SDL_RenderPresent(gRenderer);
}

//Init right buttons
void initRightButtons() {
    turn_button = (SDL_Rect) {SCREEN_WIDTH * 11 / 15, SCREEN_HEIGHT * 2 / 10, SCREEN_WIDTH * 3 / 15,
                              SCREEN_HEIGHT / 10};
    undo_button = (SDL_Rect) {SCREEN_WIDTH * 11 / 15, SCREEN_HEIGHT * 4 / 10, SCREEN_WIDTH * 3 / 15,
                              SCREEN_HEIGHT / 10};
    surrender_button = (SDL_Rect) {SCREEN_WIDTH * 11 / 15, SCREEN_HEIGHT * 6 / 10, SCREEN_WIDTH * 3 / 15,
                                   SCREEN_HEIGHT / 10};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &turn_button);
    SDL_RenderFillRect(gRenderer, &undo_button);
    SDL_RenderFillRect(gRenderer, &surrender_button);
}

//Draw buttons
void drawButton(Button_type button_type) {
    SDL_Texture *concrete;
    switch (button_type) {
        case WHITE_TURN:
            concrete = loadTexture("../gui/Assert/w_turn.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &turn_button);
            SDL_DestroyTexture(concrete);
            break;
        case BLACK_TURN:
            concrete = loadTexture("../gui/Assert/b_turn.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &turn_button);
            SDL_DestroyTexture(concrete);
            break;
        case UNDO:
            concrete = loadTexture("../gui/Assert/u_button.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &undo_button);
            SDL_DestroyTexture(concrete);
            break;
        case SURRENDER:
            concrete = loadTexture("../gui/Assert/sur_button.png");
            SDL_RenderCopy(gRenderer, concrete, NULL, &surrender_button);
            SDL_DestroyTexture(concrete);
            break;
        default:
            SDL_DestroyTexture(concrete);
            break;
    }
}

//Init right panel
void initRightPanel() {
    initRightButtons();
    drawButton(WHITE_TURN);
    drawButton(UNDO);
    drawButton(SURRENDER);
}

//Draw turn button
void drawTurn(int side) {
    switch (side) {
        case 'w':
            drawButton(WHITE_TURN);
            break;
        case 'b':
            drawButton(BLACK_TURN);
            break;
        default:
            break;
    }
}