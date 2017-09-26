//
// Created by Dmitro Semenchuk on 9/26/17.
//

#ifndef PACMAN_ENEMY_HPP
#define PACMAN_ENEMY_HPP

#include "General_win.hpp"
#include "headers.hpp"

class Enemy : public General_win {
private:
//	int _vect;
	SDL_Texture *_arr_texture[5];
public:
	Enemy(int i, SDL_Renderer *renderer);

	void changeimg(int i) { _texture = _arr_texture[i]; };

};


#endif //PACMAN_ENEMY_HPP
