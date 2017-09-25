//
// Created by Dmitro Semenchuk on 9/21/17.
//

#ifndef GENERAL_WIN_HPP
#define GENERAL_WIN_HPP

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
//#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>


class General_win {
protected:
	SDL_Window		*_window;//create window
	SDL_Renderer	*_renderer;//create render
	SDL_Surface		*_picture;
	SDL_Texture		*_texture;
public:
	General_win() {};
	virtual ~General_win();

	static int	makeRand(int);
	void		drawWindow(SDL_Renderer **);
	void		setSurfaceDraw(const char *image,
						SDL_Renderer *_renderer);//draw img in texture

	SDL_Window *getWindow() { return _window; };
	SDL_Texture *getTexture() { return _texture; };
};



#endif
