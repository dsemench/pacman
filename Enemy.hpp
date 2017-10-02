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
	bool _run;
	int old_y_x[2];
	int vect;
	int _vect, _speed;
	SDL_Texture *_arr_texture[9];

public:
	Enemy(int i, SDL_Renderer *renderer);

	int	makeRand(int r);
	void changeimg(bool condition, bool run = false);
	void action(int *map);
	void setVect(int i) { _vect = i; };
	int makeChoice(int y, int x,int *map);

	bool getHunt() { return _hunter; };
	void setHunt(bool condition) { _run = condition; };
	bool getRun() { return _run; };
	void setRun(bool condition) { _run = condition; };

	void runhome();// when enemy
};


#endif //PACMAN_ENEMY_HPP
