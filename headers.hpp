//
// Created by Dmitro Semenchuk on 9/25/17.
//

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"

/*
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
*/


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
class Text;

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

bool 		you_win(SDL_Renderer *renderer);
bool		game_over(SDL_Renderer *renderer);
void		game_pause(bool &pause);

SDL_Texture	*words_text(SDL_Renderer *renderer, TTF_Font *Sans, SDL_Color Blue, const char *str);
void 		write_text(SDL_Renderer *renderer, Text &tx, size_t num_score);
TTF_Font	*create_text_style();
