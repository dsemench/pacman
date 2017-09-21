//
// Created by Dmitro Semenchuk on 9/21/17.
//

#include "General_win.hpp"


int	main() {
	bool exit = false;
//	bool pause = false;
	SDL_Event event;
	SDL_Renderer *renderer = nullptr;//__nullptr
	General_win *gen_win = new General_win();

	gen_win->drawWindow(&renderer);
	gen_win->setSurfaceDraw("./images/back-ground-map.jpg", renderer);

	while (!exit) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, gen_win->getTexture(), nullptr, nullptr);

		SDL_RenderPresent(renderer);//last step draw window

		while (SDL_PollEvent(&event) != 0) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
		}
	}
	return 0;
}