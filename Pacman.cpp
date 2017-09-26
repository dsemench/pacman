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

void Pacman::changePic(int vect, SDL_Renderer *renderer) {
	static int old_pic;

	if (old_pic == 0)
		old_pic = vect * 10;
	switch (old_pic / 10) {
		case 1:
			if ((old_pic % 10) == 0) {
				setSurfaceDraw("./images/pacman/puc.png", renderer);
				_renderer = renderer;
			}
			else {
				setSurfaceDraw("./images/pacman/puo.png", renderer);
				_renderer = renderer;
			}
			break;
		case 2:
			if ((old_pic % 20) == 0) {
				setSurfaceDraw("./images/pacman/pdc.png", renderer);
				_renderer = renderer;
			}
			else {
				setSurfaceDraw("./images/pacman/pdo.png", renderer);
				_renderer = renderer;
			}
			break;
		case 3:
			if ((old_pic % 30) == 0) {
				setSurfaceDraw("./images/pacman/plc.png", renderer);
				_renderer = renderer;
			}
			else {
				setSurfaceDraw("./images/pacman/plo.png", renderer);
				_renderer = renderer;
			}
			break;
		case 4:
			if ((old_pic % 40) == 0) {
				setSurfaceDraw("./images/pacman/prc.png", renderer);
				_renderer = renderer;
			}
			else {
				setSurfaceDraw("./images/pacman/pro.png", renderer);
				_renderer = renderer;
			}
			break;
		default:
			break;
	}
	if (old_pic % (vect * 10) == 1)
		old_pic = vect * 10;
	else
		old_pic = (vect * 10) + 1;
}

void Pacman::travel(int *map, SDL_Renderer *renderer){
	static int vect;
	int x = _rect.x - 140, y = _rect.y - 20;
	int min = 1;

	if (vect != 0 && _rect.x != 390 && (_rect.y % 20 != 0 || _rect.x % 20 != 0)) {
		if (vect == 1) {
			_rect.y -= min;
			changePic(vect, renderer);
		}
		else if (vect == 2) {
			_rect.y += min;
			changePic(vect, renderer);
		}
		else if (vect == 3) {
			_rect.x -= min;
			changePic(vect, renderer);
		}
		else if (vect == 4) {
			_rect.x += min;
			changePic(vect, renderer);
		}
	}
	else {
		if (_vect == 1 && !getRoad((y - 20) / 20, x / 20, map)) {
			if ((y - 20) >= 0) {
				_rect.y -= min;
				vect = _vect;
				changePic(vect, renderer);
			}
		}
		else if (_vect == 2 && !getRoad((y + 20) / 20, x / 20, map)) {
			if ((y + 20) <= 580) {
				_rect.y += min;
				vect = _vect;
				changePic(vect, renderer);
			}

		}
		else if (_vect == 3 && !getRoad(y / 20, (x - 20) / 20, map)) {
			if ((x - 20) >= 0) {
				_rect.x -= min;
				vect = _vect;
				changePic(vect, renderer);
			}
		}
		else if (_vect == 4 && !getRoad(y / 20, (x + 20) / 20, map)) {
			if ((x + 20) <= 500) {
				_rect.x += min;
				vect = _vect;
				changePic(vect, renderer);
			}
		}
		else {
			if (vect == 1 && !getRoad((y - 20) / 20, x / 20, map)) {
				_rect.y -= min;
				changePic(vect, renderer);
			}
			else if (vect == 2 && !getRoad((y + 20) / 20, x / 20, map)) {
				_rect.y += min;
				changePic(vect, renderer);
			}
			else if (vect == 3 && !getRoad(y / 20, (x - 20) / 20, map)) {
				_rect.x -= min;
				changePic(vect, renderer);
			}
			else if (vect == 4 && !getRoad(y / 20, (x + 20) / 20, map)) {
				_rect.x += min;
				changePic(vect, renderer);
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