//
// Created by Dmitro Semenchuk on 9/25/17.
//

#include "Hight_cl.hpp"

class Pacman : public Hight_cl {
private:
	int			_vect;
	SDL_Texture	*_arr_texture[8];
public:
	Pacman(SDL_Renderer *renderer);

	void setvect(int i) { _vect = _vect = i; };

	void action(SDL_Event event);
	void travel(int *map);
	void changePic(int vect);
};
