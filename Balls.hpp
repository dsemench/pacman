//
// Created by Dmitro Semenchuk on 9/22/17.
//

#ifndef PACMAN_BALLS_HPP
#define PACMAN_BALLS_HPP

#include "General_win.hpp"

class Balls : public General_win {
private:
	SDL_Rect _rect;
public:
	Balls(int i, SDL_Renderer *renderer, int m_y, int m_x);
	SDL_Rect getRect() { return _rect; };

};


#endif //PACMAN_BALLS_HPP
