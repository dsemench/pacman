//
// Created by Dmitro Semenchuk on 10/2/17.
//

#ifndef PACMAN_ACTION_HPP
#define PACMAN_ACTION_HPP

#include "headers.hpp"

class Action {
public:
	bool finish_mov_pos(int vect, int speed, SDL_Rect &rect);
};


#endif //PACMAN_ACTION_HPP
