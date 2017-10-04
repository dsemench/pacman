//
// Created by Dmitro Semenchuk on 10/3/17.
//

#include "headers.hpp"
#include "Balls.hpp"
#include "Enemy.hpp"
#include "Pacman.hpp"


bool		getRoad(int y, int x, int *map) {

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

void		initBall(SDL_Renderer *renderer, vector<Balls*> &ball,
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

SDL_Point	take_SDL_point(SDL_Rect rect) {
	SDL_Point res;
	res.x = rect.x;
	res.y = rect.y;
	return res;
}

bool		to_start_pos(vector<Enemy*> &en, Pacman &Pac) {
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

void		error_SDL(int i, SDL_Renderer *renderer, SDL_Window *window) {
	switch (i) {
		case 1:
			cout << "SDL_Init Error: "
				 << SDL_GetError() << std::endl;
			break ;
		case 2:
			cout << "SDL_CreateWindow Error: "
				 << SDL_GetError() << std::endl;
			break ;
		case 3:
			SDL_DestroyWindow(window);
			cout << "SDL_CreateRenderer Error: "
				 << SDL_GetError() << std::endl;
			break ;
		case 4:
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			cout << "SDL_Load Error: "
				 << SDL_GetError() << std::endl;
			break ;
		case 5:
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			cout << "SDL_CreateTextureFromSurface Error: "
				 << SDL_GetError() << std::endl;
			break ;
	}
	SDL_Quit();
	exit(1);
}

void		DrawWindow(SDL_Renderer **renderer, SDL_Window *window) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		throw 1;
	}
	window = SDL_CreateWindow("Pacman",
							  800, 500, 800, 620, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		throw 2;
	}
	*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (*renderer == nullptr){
		throw 3;
	}
}

SDL_Texture	*SetSurfaceDraw(const char *image, SDL_Renderer *renderer) {
	SDL_Surface		*picture;
	SDL_Texture		*tmp_texture = nullptr;

	picture = IMG_Load(image);
	if (picture == nullptr){
		throw 4;
	}
	tmp_texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (tmp_texture == nullptr){
		throw 5;
	}
	return tmp_texture;
}

void		Destroy_Win(SDL_Renderer *renderer,
				 SDL_Window *window, SDL_Texture *texture) {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool 		you_win(SDL_Renderer *renderer) {
	SDL_Rect tmp_rect;

	tmp_rect.h = 620;
	tmp_rect.w = 560;
	tmp_rect.y = 0;
	tmp_rect.x = 120;

	SDL_RenderCopy(renderer, SetSurfaceDraw("./images/YouWin.png", renderer), nullptr, &tmp_rect);
	SDL_RenderPresent(renderer);
	return true;
}
