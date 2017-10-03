//
// Created by Dmitro Semenchuk on 9/26/17.
//

#ifndef PACMAN_ENEMY_HPP
#define PACMAN_ENEMY_HPP

#include "General_win.hpp"
#include "headers.hpp"

class Enemy : public General_win {
private:
	bool _hunt;
	bool _run;
	bool _home;
	int old_y_x[2];
	int vect;
	int _vect, _speed;
	int _can_eat_em;
	SDL_Texture *_arr_texture[9];

public:
	Enemy(int i, SDL_Renderer *renderer);

	int	makeRand(int r);
	void changeimg(bool condition, bool run = false);
	void action(int *map);
	bool finish_mov_pos();
	void setVect(int i) { _vect = i; };
	int makeChoice(int y, int x, int *map);

	int &get_set_eat() { return _can_eat_em; };

	bool getHunt() { return _hunt; };
	void setHunt(bool condition) { _hunt = condition; };

	bool getRun() { return _run; };
	void setRun(bool condition) { _run = condition; };

	bool getHome() { return _home; };
	void setHome(bool condition) { _home = condition; };

	void go_to_pos(vector<int> choise, int pos_y, int pos_x, int y, int x);
	void makeFirst_step();
	void runhome(int *map);
	void go_out_home(int *map);
	vector<int> createVecChoise(int y, int x, int *map);
};


#endif //PACMAN_ENEMY_HPP
