//
// Created by Dmitro Semenchuk on 9/21/17.
//

#include "General_win.hpp"
#include "Balls.hpp"
#include "Map.hpp"
#include "Pacman.hpp"
#include "Enemy.hpp"


int	main() {
	bool exit, pause, delay, delay1, try_again;
	exit = delay = delay1 = try_again = false;
	pause = true;
	SDL_Event event;
	SDL_Renderer *renderer = nullptr;
	General_win gen_win = General_win();
	SDL_Rect tmp_rect;
	vector<Balls*> ball, life;
	vector<Enemy*> en;

	gen_win.drawWindow(&renderer);
	gen_win.setSurfaceDraw("./images/back-ground.jpeg", renderer);

	Map Mp = Map(renderer);
	Pacman Pac = Pacman(renderer);
	srand(time(0));
	initBall(renderer, ball, life, en, Mp.getMap());
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