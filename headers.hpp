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



using namespace std;

class Balls;
class Enemy;
class Pacman;

bool		getRoad(int y, int x, int *map);
void		initBall(SDL_Renderer *renderer, vector<Balls*> &ball,
					vector<Balls*> &life, vector<Enemy*> &en, int *map);
SDL_Point	take_SDL_point(SDL_Rect rect);
bool		to_start_pos(vector<Enemy*> &en, Pacman &Pac);


void		DrawWindow(SDL_Renderer **renderer, SDL_Window *window);
SDL_Texture	*SetSurfaceDraw(const char *image, SDL_Renderer *renderer);
void		Destroy_Win(SDL_Renderer *renderer,
				 SDL_Window *window, SDL_Texture *texture);

void		error_SDL(int i, SDL_Renderer *renderer, SDL_Window *window);
#endif //PACMAN_HEADERS_HPP
