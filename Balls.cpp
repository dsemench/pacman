//
// Created by Dmitro Semenchuk on 9/22/17.
//

#include "Balls.hpp"

Balls::Balls(int i, SDL_Renderer *renderer, int m_y, int m_x) {
	_rect.h = 20;
	_rect.w = 20;
	_rect.x = 140 + (20 * m_x);
	_rect.y = 20 + (20 * m_y);

	if (i == 0) {
		setSurfaceDraw("./images/balls_cherry/t1.png", renderer);
	}
	else if (i == 1) {
		setSurfaceDraw("./images/balls_cherry/t2.png", renderer);
	}

	_renderer = renderer;
}