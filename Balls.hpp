//
// Created by Dmitro Semenchuk on 9/22/17.
//

#include "Hight_cl.hpp"

class Balls : public Hight_cl {
private:
	bool	_ball_big;
public:
	Balls(int i, SDL_Renderer *renderer, int m_y, int m_x);

	bool	getBallsize() { return _ball_big; };
};

