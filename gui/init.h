//
// Created by thanhnn on 2/14/2018.
//

#ifndef CHESS_AUDIO_H
#define CHESS_AUDIO_H

#include <SDL_mixer.h>

//#define START_FEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
//#define START_FEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"


//The music that will be played
extern Mix_Music *gMusic;

//The sound effects that will be used
extern Mix_Chunk *gScratch;
extern Mix_Chunk *gHigh;
extern Mix_Chunk *gMedium;
extern Mix_Chunk *gLow;


//Init SDL
bool init();

//Init window
bool initWindow();

//Init media
bool loadMedia();

//Release resources
void closeGUI();

#endif //CHESS_AUDIO_H
