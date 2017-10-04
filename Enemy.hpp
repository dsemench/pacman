//
// Created by Dmitro Semenchuk on 9/26/17.
//

#ifndef PACMAN_ENEMY_HPP
#define PACMAN_ENEMY_HPP

#include "Hight_cl.hpp"

class Enemy : public Hight_cl {
private:
	bool _hunt, _run, _home;
	int old_y_x[2], vect, _vect, _speed, _can_eat_em;
	SDL_Texture *_arr_texture[9];

public:
	Enemy(int i, SDL_Renderer *renderer);

	int			makeRand(int r);
	void		changeimg(bool condition, bool run = false);
	void		action(int *map);
	bool		finish_mov_pos();
	int			makeChoice(int y, int x, int *map);

	int			&get_set_eat() { return _can_eat_em; };
	bool		getHunt() { return _hunt; };
	bool		getRun() { return _run; };
	void		setRun(bool condition) { _run = condition; };
	void		setVect(int i) { _vect = i; };
	bool		getHome() { return _home; };
	void		setHome(bool condition) { _home = condition; };

	void		go_to_pos(vector<int> choise, int pos_y, int pos_x, int y, int x);
	void		makeFirst_step();
	void		runhome(int *map);
	void		go_out_home(int *map);
	vector<int>	createVecChoise(int y, int x, int *map);
};


#endif
