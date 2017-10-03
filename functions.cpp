//
// Created by Dmitro Semenchuk on 10/3/17.
//

#include "headers.hpp"
#include "Balls.hpp"
#include "Enemy.hpp"
#include "Pacman.hpp"




bool getRoad(int y, int x, int *map) {

//	if (y < 12 || y > 17 || x < 11 || x > 16) {
//		cout << "pos x = " << x << "\n";
//		cout << "pos y = " << y << "\n";
//	}
	if (y < 0 || y > 28 || x < 0 || x > 25)
		return true;
	x = (x * -1) + 25;
	if ((map[y] >> x) % 2 == 1)
		return true;
	else
		return false;
}

void initBall(SDL_Renderer *renderer, vector<Balls*> &ball,
			vector<Balls*> &life, vector<Enemy*> &en, int *map) {

	for (int y = 0; y < 29; y++) {
		for (int x = 0; x < 26; x++) {
			if (!(y > 7 && y < 19 && x > 5 && x < 20) && !getRoad(y, x, map)) {
				Balls *tmp = nullptr;
				if ((y == 2 && x == 0) || (y == 2 && x == 25)
					|| (y == 22 && x == 0) || (y == 22 && x == 25)) {
					tmp = new Balls(1, renderer, y, x);
				}
				else {
					if (!(y == 22 && (x == 12 || x == 13)))
						tmp = new Balls(0, renderer, y, x);
				}
				if (tmp != nullptr)
					ball.push_back(tmp);
			}
		}
	}
	for (int i = 0; i < 3; ++i) {
		Balls *tmp = new Balls(2, renderer, 0, i);
		life.push_back(tmp);
	}
	for (int i = 0; i < 4; ++i) {
		Enemy *tmp_en = new Enemy(i + 1, renderer);
		en.push_back(tmp_en);
	}
}

SDL_Point take_SDL_point(SDL_Rect rect) {
	SDL_Point res;
	res.x = rect.x;
	res.y = rect.y;
	return res;
}

bool to_start_pos(vector<Enemy*> &en, Pacman &Pac) {
	SDL_Rect tmp_rect;

	for (size_t i = 0; i < en.size(); i++) {
		tmp_rect = en[i]->getRect();
		tmp_rect.y = 20 + (12 * 20);
		tmp_rect.x = 140 + (9 * 20) + (20 * ((int)i + 1));
		en[i]->get_set_eat() = 0;
		en[i]->setRect(tmp_rect);
		en[i]->setHome(true);
		en[i]->setVect(-3);
		en[i]->changeimg(false, true);
	}
	tmp_rect.y = 20 + (22 * 20);
	tmp_rect.x = 140 + (12 * 20) + 10;
	Pac.setRect(tmp_rect);
	Pac.setvect(1);

	return false;
}
