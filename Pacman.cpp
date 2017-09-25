//
// Created by Dmitro Semenchuk on 9/25/17.
//

#include "Pacman.hpp"

Pacman::Pacman(SDL_Renderer *renderer) {
	_vect = 0;
	_rect.h = 20;//hight
	_rect.w = 20;//width
	_rect.x = 140 + (12 * 20) + 10;//horizontal pos
	_rect.y = 20 + (22 * 20);// vertical pos
	setSurfaceDraw("./images/pacman/puc.png", renderer);
	_renderer = renderer;
}


void Pacman::travel(int *map){
	static int vect;

	int min = 1;
	if (vect != 0 && (_rect.y % 20 != 0 || _rect.x % 20 != 0)) {
		if (vect == 1) {
			_rect.y -= min;
		}
		else if (vect == 2) {
			_rect.y += min;
		}
		else if (vect == 3) {
			_rect.x -= min;
		}
		else if (vect == 4) {
			_rect.x += min;
		}
	}
	else {
		int x = _rect.x - 140, y = _rect.y - 20;

		vect = _vect;
		if (_vect == 1) {
			if ((y - 20) >= 0
				&& !getRoad((y - 20) / 20, x / 20, map)) {
				_rect.y -= min;
			}
		}
		else if (_vect == 2) {
			if ((y + 20) <= 580
				&& !getRoad((y + 20) / 20, x / 20, map)) {
				_rect.y += min;
			}

		}
		else if (_vect == 3) {
			if ((x - 20) >= 0
				&& !getRoad(y / 20, (x - 20) / 20, map)) {
				_rect.x -= min;
			}
		}
		else if (_vect == 4) {
			if ((x + 20) <= 500
				&& !getRoad(y / 20, (x + 20) / 20, map)) {
				_rect.x += min;
			}
		}
	}
}

void Pacman::action(SDL_Event event) {
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_UP) {
			_vect = 1;
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			_vect = 2;
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {
			_vect = 3;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			_vect = 4;
		}
	}
}