//
// Created by Dmitro Semenchuk on 9/25/17.
//

#ifndef PACMAN_HEADERS_HPP
#define PACMAN_HEADERS_HPP

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
//#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
//#include "General_win.hpp"
//#include "Balls.hpp"
//#include "Map.hpp"
//#include "Pacman.hpp"



using namespace std;

class Balls;

bool getRoad(int y, int x, int *map);
void initBall(SDL_Renderer *renderer, vector<Balls*> &ball, int *map);
SDL_Point getSDL_point(SDL_Rect rect);

#endif //PACMAN_HEADERS_HPP
