//
// Created by Dmitro Semenchuk on 9/22/17.
//

#include "Balls.hpp"

Balls::Balls(int i, SDL_Renderer *renderer, int m_y, int m_x) {
	_rect.h = 20;
	_rect.w = 20;
	_rect.y = 20 + (20 * m_y);
	_rect.x = 140 + (20 * m_x);


/*
	if (i == 0) {
		setSurfaceDraw("./images/balls_cherry/t1.png", renderer);
		_ball_big = false;
	}
	else if (i == 1) {
		setSurfaceDraw("./images/balls_cherry/t2.png", renderer);
		_ball_big = true;
	}
	else {
		setSurfaceDraw("./images/pacman/pro.png", renderer);
*/
	if (i == 0) {
		_texture = SetSurfaceDraw("./images/balls_cherry/t1.png", renderer);
		_ball_big = false;
	}
	else if (i == 1) {
		_texture = SetSurfaceDraw("./images/balls_cherry/t2.png", renderer);
		_ball_big = true;
	}
	else {
		_texture = SetSurfaceDraw("./images/pacman/pro.png", renderer);

//		_rect.y = 20 + (20 * m_y);
		_rect.y = 580;
		switch (m_x) {
			case 0:
				_rect.x = 10;
				break ;
			case 1:
				_rect.x = 50;
				break ;
			case 2:
				_rect.x = 90;
				break ;
		}
	}
}