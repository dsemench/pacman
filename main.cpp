//
// Created by Dmitro Semenchuk on 9/21/17.
//

#include "General_win.hpp"
#include "Balls.hpp"
#include "Map.hpp"

using namespace std;

void initBall(SDL_Renderer *renderer, vector<Balls*> &ball, Map *Mp) {

	for (int y = 0; y < 29; y++) {
		for (int x = 0; x < 26; x++) {
			if (!(y > 7 && y < 19 && x > 5 && x < 20) && !Mp->getRoad(y, x)) {
				Balls *tmp;
				if ((y == 2 && x == 0) || (y == 2 && x == 25)
					|| (y == 22 && x == 0) || (y == 22 && x == 25)) {
					tmp = new Balls(1, renderer, y, x);
				}
				else
					tmp = new Balls(0, renderer, y, x);
				ball.push_back(tmp);
			}
		}
	}
}

int	main() {

	bool exit = false;
//	bool pause = false;
	SDL_Event event;
	SDL_Renderer *renderer = nullptr;//__nullptr
	General_win *gen_win = new General_win();
	SDL_Rect tmp_rect;
	vector<Balls*> ball;


	gen_win->drawWindow(&renderer);
	gen_win->setSurfaceDraw("./images/back-ground.jpeg", renderer);

	Map *Mp = new Map(renderer);


	initBall(renderer, ball, Mp);
	while (!exit) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, gen_win->getTexture(), nullptr, nullptr);

		tmp_rect = Mp->getRect();
		SDL_RenderCopy(renderer, Mp->getTexture(), nullptr, &tmp_rect);

		for (size_t i = 0; i < ball.size(); i++){
			tmp_rect = ball[i]->getRect();
			SDL_RenderCopy(renderer, ball[i]->getTexture(), nullptr, &tmp_rect);
		}
		SDL_RenderPresent(renderer);//last step draw window

		while (SDL_PollEvent(&event) != 0) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
		}
	}
	return 0;
}

//поменяй координаты где появляется окно