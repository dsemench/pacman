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


void initBall(SDL_Renderer *renderer, vector<Balls*> &ball, vector<Balls*> &life, int *map) {

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
		Balls *tmp = nullptr;
		tmp = new Balls(2, renderer, 0, i);
		life.push_back(tmp);
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
	}
	tmp_rect.y = 20 + (22 * 20);
	tmp_rect.x = 140 + (12 * 20) + 10;
	Pac.setRect(tmp_rect);
	Pac.setvect(1);

	return false;
}

int	main() {

	bool exit = false;
	bool pause = false;
	bool delay = false;
	bool delay1 = false;
	bool try_again = false;
	SDL_Event event;
	SDL_Renderer *renderer = nullptr;
	General_win gen_win = General_win();
	SDL_Rect tmp_rect;
	vector<Balls*> ball;
	vector<Enemy*> en;
	vector<Balls*> life;


	gen_win.drawWindow(&renderer);
	gen_win.setSurfaceDraw("./images/back-ground.jpeg", renderer);


	Map Mp = Map(renderer);
	Pacman Pac = Pacman(renderer);
	srand(time(0));
	for (int i = 0; i < 2; ++i) {
		Enemy *tmp_en = new Enemy(i + 1, renderer);
		en.push_back(tmp_en);
	}

	initBall(renderer, ball, life, Mp.getMap());
	while (!exit) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, gen_win.getTexture(), nullptr, nullptr);

		tmp_rect = Mp.getRect();
		SDL_RenderCopy(renderer, Mp.getTexture(), nullptr, &tmp_rect);


		if (try_again) {
			try_again = to_start_pos(en, Pac);
			pause = true;
		}
		for (size_t i = 0; i < life.size(); i++) {
			tmp_rect = life[i]->getRect();
			SDL_RenderCopy(renderer, life[i]->getTexture(), nullptr, &tmp_rect);
		}
		for (size_t i = 0; i < ball.size(); i++){
			tmp_rect = ball[i]->getRect();
			SDL_Rect tmp_rect1 = Pac.getRect();
			if (SDL_RectEquals(&tmp_rect1, &tmp_rect)) {
				if (ball[i]->getBallsize()) {
					for (size_t i = 0; i < en.size(); i++) {
						en[i]->get_set_eat() += 20000;
					}
				}
				ball.erase(ball.begin() + i);
				i--;
			}
			else
				SDL_RenderCopy(renderer, ball[i]->getTexture(), nullptr, &tmp_rect);
		}

		if (delay) {
			Pac.travel(Mp.getMap());
			delay = false;
		}
				else
			delay = true;
		delay1 ? delay1 = false : delay1 = true;

		for (size_t i = 0; i < en.size(); i++) {
			SDL_Point tmp_ptr = take_SDL_point(Pac.getRect());
			tmp_rect = en[i]->getRect();
			if (en[i]->get_set_eat()) {
				en[i]->get_set_eat()--;
			}
			if (!en[i]->getRun() && !SDL_PointInRect(&tmp_ptr, &tmp_rect)) {
				if (Mp.door_status())
					Mp.close_door();
				if (delay) {
					if (en[i]->getHome()) {
						if (!Mp.door_status())
							Mp.open_door();
						en[i]->go_out_home(Mp.getMap());
					}
					else if (en[i]->get_set_eat()) {
							if(delay1) {
//								cout << "enemy = " << i << "\n";
								en[i]->action(Mp.getMap());
							}
							en[i]->changeimg(false);
					}
					else {
						en[i]->action(Mp.getMap());
						en[i]->changeimg(true);
					}
				}
			}
			else {
				if (!Mp.door_status())
					Mp.open_door();
				if (en[i]->getRun()) {
					en[i]->runhome(Mp.getMap());
				}
				else {
					if (en[i]->getHunt()) {
						if (life.size()) {
							cout << "pacman dead!\n";
							life.erase(life.end() - 1);
//							Pac.change_life()--;
							try_again = true;
							continue ;
						}
						else {
							exit = true;
						}
					}
					else {
						en[i]->setRun(true);
						en[i]->runhome(Mp.getMap());
					}
				}
			}
			SDL_RenderCopy(renderer, en[i]->getTexture(), nullptr, &tmp_rect);
		}
		if (ball.size() == 0) {
			cout << "you win!\n";
			exit = true;
		}
		tmp_rect = Pac.getRect();
		SDL_RenderCopy(renderer, Pac.getTexture(), nullptr, &tmp_rect);

		SDL_RenderPresent(renderer);//last step draw window

		while (SDL_PollEvent(&event) != 0 && event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					exit = true;
				else if (event.key.keysym.sym == SDLK_p)
					pause = true;
				else
					Pac.action(event);
		}
		while (pause) {
			while (SDL_PollEvent(&event) != 0 && event.type == SDL_KEYUP) {
				pause = false;
			}
		}
	}
	return 0;
}

//поменяй координаты где появляется окно