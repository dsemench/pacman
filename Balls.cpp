//
// Created by Dmitro Semenchuk on 9/22/17.
//

#include "Balls.hpp"

Balls::Balls(int i, SDL_Renderer *renderer) {

	if (i == 0) {
/*
		_rect.h = 50;
		_rect.w = 50;
		_rect.x = 20;
		_rect.y = 13;
*/
		setSurfaceDraw("./images/Little-ball2.png", renderer);
		_rect.h = 25;
		_rect.w = 25;
		_rect.x = 50;
		_rect.y = 30;
	}
	else if (i == 1) {
		setSurfaceDraw("./images/Big_ball.png", renderer);
		_rect.h = 50;
		_rect.w = 50;
		_rect.x = 20;
		_rect.y = 13;
	}
	else if (i == 2){
		setSurfaceDraw("./images/map.png", renderer);
		_rect.h = 620;//hight
		_rect.w = 560;//width
		_rect.x = 120;//horizontal pos
		_rect.y = 0;//vertical pos
	}
	else {
		setSurfaceDraw("./images/White-cube.png", renderer);
		_rect.h = 580;//588;//hight
		_rect.w = 520;//528;//width
		_rect.x = 140;//horizontal pos
		_rect.y = 20;//vertical pos
	}

	_renderer = renderer;
}