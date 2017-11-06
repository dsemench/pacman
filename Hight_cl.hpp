//
// Created by Dmitro Semenchuk on 10/4/17.
//

#ifndef HIGHT_CL_HPP
#define HIGHT_CL_HPP

#include "headers.hpp"

class Hight_cl {
protected:
	SDL_Rect		_rect;
	SDL_Texture		*_texture;
public:
	SDL_Rect		getRect() { return _rect; };
	void			setRect(SDL_Rect rect) { _rect = rect; };
	SDL_Texture		*getTexture() { return _texture; };
};

#endif
