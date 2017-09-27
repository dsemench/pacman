//
// Created by Dmitro Semenchuk on 9/26/17.
//

#ifndef PACMAN_ENEMY_HPP
#define PACMAN_ENEMY_HPP

#include "General_win.hpp"
#include "headers.hpp"

class Enemy : public General_win {
private:
	bool _hunter;
	int count_steps;
	int vect;
	int old_vect;
	int _vect, _speed;
	SDL_Texture *_arr_texture[5];

public:
	Enemy(int i, SDL_Renderer *renderer);

	int	makeRand(int r);
	void changeimg(bool condition);
	void action(int *map);
	void setVect(int i) { _vect = i; };
	int makeChoice(int y, int x,int *map);
};


#endif //PACMAN_ENEMY_HPP
