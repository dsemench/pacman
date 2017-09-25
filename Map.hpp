//
// Created by Dmitro Semenchuk on 9/25/17.
//

#ifndef PACMAN_MAP_HPP
#define PACMAN_MAP_HPP

#include "General_win.hpp"
#include <iostream>////созать хороший хедер!!!!!!!!!!!!

using namespace std;

class Map : public General_win {
private:
	int _map[29];
	SDL_Rect _rect;
	SDL_Renderer	*_renderer;//create render
public:
	Map(SDL_Renderer *renderer);
	SDL_Rect getRect() { return _rect; };
	int *getMap() { return _map; };
	bool getRoad(int y, int x);
};


#endif //PACMAN_MAP_HPP
