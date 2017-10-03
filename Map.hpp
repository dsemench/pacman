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
	bool door_status() { return (_map[11] == 65916639) ? true : false; };
	void open_door() {_map[11] = 65916639;};
	void close_door() {_map[11] = 65928927;};
	//functions to open and close door for enemies
};


#endif //PACMAN_MAP_HPP
