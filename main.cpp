//
// Created by Dmitro Semenchuk on 9/21/17.
//

#include "General_win.hpp"
#include "Balls.hpp"
#include "Map.hpp"
#include "Pacman.hpp"
#include "Enemy.hpp"

using namespace std;

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


void initBall(SDL_Renderer *renderer, vector<Balls*> &ball, int *map) {

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
}

SDL_Point take_SDL_point(SDL_Rect rect) {
	SDL_Point res;
	res.x = rect.x;
	res.y = rect.y;
	return res;
}

int	main() {

	bool exit = false;
//	bool pause = false;
	bool delay = false;
	int can_eat_en = 0;
	SDL_Event event;
	SDL_Renderer *renderer = nullptr;
	General_win *gen_win = new General_win();
	SDL_Rect tmp_rect;
	vector<Balls*> ball;
	vector<Enemy*> en;


	gen_win->drawWindow(&renderer);
	gen_win->setSurfaceDraw("./images/back-ground.jpeg", renderer);


	Map *Mp = new Map(renderer);
	Pacman *Pac = new Pacman(renderer);
	srand(time(0));
	for (int i = 0; i < 4; ++i) {
		Enemy *tmp_en = new Enemy(i + 1, renderer);
		en.push_back(tmp_en);
	}

	initBall(renderer, ball, Mp->getMap());
	while (!exit) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, gen_win->getTexture(), nullptr, nullptr);

		tmp_rect = Mp->getRect();
		SDL_RenderCopy(renderer, Mp->getTexture(), nullptr, &tmp_rect);

		for (size_t i = 0; i < ball.size(); i++){
			tmp_rect = ball[i]->getRect();
			SDL_Rect tmp_rect1 = Pac->getRect();
			if (SDL_RectEquals(&tmp_rect1, &tmp_rect)) {
				if (ball[i]->getBallsize()) {
					can_eat_en += 5000;
					can_eat_en += 5000;
					can_eat_en += 5000;
				}
				ball.erase(ball.begin() + i);
				i--;
			}
			else
				SDL_RenderCopy(renderer, ball[i]->getTexture(), nullptr, &tmp_rect);
		}

		if (delay) {
			Pac->travel(Mp->getMap());
			delay = false;
		}
		else
			delay = true;

		for (size_t i = 0; i < en.size(); i++) {
			SDL_Point tmp_ptr = take_SDL_point(Pac->getRect());
			tmp_rect = en[i]->getRect();
			if (can_eat_en) {
				en[i]->changeimg(false);
				can_eat_en--;
			}
			else
				en[i]->changeimg(true);
			if (!en[i]->getRun() && !SDL_PointInRect(&tmp_ptr, &tmp_rect)) {
				if (delay)
					en[i]->action(Mp->getMap());
			}
			else {
//				cout << "eat-eat i = " << i << "\n";
				if (en[i]->getRun()) {
					//enemy run home
					en[i]->runhome(Mp->getMap());
				}
				else {
					if (en[i]->getHunt()) {
						//problem for pacman
					}
					else {
//						en[i]->changeimg(false, true);
						en[i]->setRun(true);
						en[i]->runhome(Mp->getMap());
					}
				}
			}
			SDL_RenderCopy(renderer, en[i]->getTexture(), nullptr, &tmp_rect);
		}
		if (ball.size() == 0) {
			cout << "you win!\n";
			exit = true;
		}
		tmp_rect = Pac->getRect();
		SDL_RenderCopy(renderer, Pac->getTexture(), nullptr, &tmp_rect);

		SDL_RenderPresent(renderer);//last step draw window

		while (SDL_PollEvent(&event) != 0) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			else
				Pac->action(event);
		}
		for (int j = 0; j < 10000; ++j);
		for (int j = 0; j < 10000; ++j);
		for (int j = 0; j < 10000; ++j);
		for (int j = 0; j < 10000; ++j);
	}
	return 0;
}

//поменяй координаты где появляется окно