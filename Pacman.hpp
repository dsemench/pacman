//
// Created by Dmitro Semenchuk on 9/25/17.
//

#ifndef PACMAN_PACMAN_HPP
#define PACMAN_PACMAN_HPP

#include "General_win.hpp"
#include "headers.hpp"

class Pacman : public General_win {
private:
	int _vect;
	SDL_Texture *_arr_texture[8];
public:
	Pacman(SDL_Renderer *renderer);

	void setvect(int i) { _vect = _vect = i; };

	void action(SDL_Event event);
	void travel(int *map);
	void changePic(int vect);
};


#endif //PACMAN_PACMAN_HPP
