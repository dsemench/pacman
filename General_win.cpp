//
// Created by Dmitro Semenchuk on 9/21/17.
//

#include "General_win.hpp"

General_win::~General_win() {
	SDL_DestroyTexture(_texture);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

int General_win::makeRand(int r) {
	int res;

	res = rand() % r + 1;
	std::cout << "rand = " << res << "\n";
	return res;
}

void General_win::drawWindow(SDL_Renderer **renderer) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){//init sdl process
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	_window = SDL_CreateWindow("Pacman",
							   0, 0, 800, 600, SDL_WINDOW_SHOWN);//create window by
	if (_window == __nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	*renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
	if (*renderer == __nullptr){
		SDL_DestroyWindow(_window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
}
void General_win::setSurfaceDraw(const char *image, SDL_Renderer *renderer) {
	_picture = IMG_Load(image);
	if (_picture == __nullptr){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(_window);
		std::cout << "SDL_Load Error: " << SDL_GetError()
				  << std::endl;
		SDL_Quit();
		exit(1);
	}
	_texture = SDL_CreateTextureFromSurface(renderer, _picture);
	SDL_FreeSurface(_picture);
	if (_texture == __nullptr){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(_window);
		std::cout << "SDL_CreateTextureFromSurface Error: "
				  << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
}
