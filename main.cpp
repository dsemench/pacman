//
// Created by Dmitro Semenchuk on 9/21/17.
//

#include "General_win.hpp"
#include "Balls.hpp"


int	main() {
	bool exit = false;
//	bool pause = false;
	SDL_Event event;
	SDL_Renderer *renderer = nullptr;//__nullptr
	General_win *gen_win = new General_win();
	SDL_Rect tmp_rect;

	gen_win->drawWindow(&renderer);
	gen_win->setSurfaceDraw("./images/back-ground.jpeg", renderer);

//	Balls *little_ball = new Balls(0, renderer);
//	Balls *big_ball = new Balls(1, renderer);
	Balls *w_map = new Balls(2, renderer);
	Balls *cube = new Balls(3, renderer);

	while (!exit) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, gen_win->getTexture(), nullptr, nullptr);

		tmp_rect = w_map->getRect();
		SDL_RenderCopy(renderer, w_map->getTexture(), nullptr, &tmp_rect);

//		tmp_rect = little_ball->getRect();
//		SDL_RenderCopy(renderer, little_ball->getTexture(), nullptr, &tmp_rect);
//
//		tmp_rect = big_ball->getRect();
//		SDL_RenderCopy(renderer, big_ball->getTexture(), nullptr, &tmp_rect);
//
		tmp_rect = cube->getRect();
		SDL_RenderCopy(renderer, cube->getTexture(), nullptr, &tmp_rect);
		SDL_RenderPresent(renderer);//last step draw window

		while (SDL_PollEvent(&event) != 0) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
		}
	}
	return 0;
}