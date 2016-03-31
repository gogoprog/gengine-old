#pragma once

#ifdef EMSCRIPTEN
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#else
#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif
