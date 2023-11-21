#pragma once

#include "GameState.h"
#include <SDL_MIXER.h>



int initAudio();
void cleanUpAudio();
void shotSound1();
void shotSound2();
void dameSound();
void backgroundMusic();
void shotSound3();
void endMusic();
void opMusic();
void bossMusic();
void winMusic();
void pickup();
void enemydead();