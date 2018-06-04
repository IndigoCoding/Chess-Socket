#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "draw.h"
#include "move.h"
#include "../engine/defs.h"
#include "init.h"

int main(int argc, char *args[]) {
    //Integrate engine
    initAll();
    S_BOARD board[1];
    S_MOVELIST list[1];

    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            initRightPanel();

            //Test board
            parseFen(START_FEN, board);
            engineToGUI(board->pieces);
            drawCurrentBoard();

            //Update screen
            SDL_RenderPresent(gRenderer);

            char *moveEvent;

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int x,y;
                        SDL_GetMouseState(&x, &y);
//                        printf("Position: %d-%d\n", x, y);
//                        handleMoveEvent(x, y, board);
//                        strcpy(moveEvent, handleMoveEvent(x, y, board));
//                        printf("moveEvent: %s\n", moveEvent);
                        moveEvent = handleMoveEvent(x, y, board);
                        printf("handle: %s\n", moveEvent);
                        free(moveEvent);
                    }
                }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}