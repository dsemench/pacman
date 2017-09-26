//
// Created by Dmitro Semenchuk on 9/25/17.
//

#ifndef PACMAN_MAP_HPP
#define PACMAN_MAP_HPP

#include "General_win.hpp"

class Map : public General_win {
private:
	int _map[29];
public:
	Map(SDL_Renderer *renderer);
	int *getMap() { return _map; };
//	bool getRoad(int y, int x);
};


#endif //PACMAN_MAP_HPP