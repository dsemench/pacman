//
// Created by Dmitro Semenchuk on 9/22/17.
//

#ifndef PACMAN_BALLS_HPP
#define PACMAN_BALLS_HPP

//#include "General_win.hpp"
#include "Hight_cl.hpp"

//class Balls : public General_win {
class Balls : public Hight_cl {
private:
	bool _ball_big;
public:
	Balls(int i, SDL_Renderer *renderer, int m_y, int m_x);
	bool getBallsize() { return _ball_big; };
};


#endif //PACMAN_BALLS_HPP
