//
// Created by Dmitro Semenchuk on 9/21/17.
//

//#include "General_win.hpp"
#include "Hight_cl.hpp"

#include "Balls.hpp"
#include "Map.hpp"
#include "Pacman.hpp"
#include "Enemy.hpp"

/*void error_SDL(int i, SDL_Renderer *renderer, SDL_Window *window) {
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

void DrawWindow(SDL_Renderer *renderer, SDL_Window *window) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		throw 1;
	}
	window = SDL_CreateWindow("Pacman",
							800, 500, 800, 620, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		throw 2;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == nullptr){
		throw 3;
	}
}

SDL_Texture *SetSurfaceDraw(const char *image, SDL_Renderer *renderer) {
	SDL_Surface		*picture;
	SDL_Texture		*tmp_texture;

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

void Destroy_Win(SDL_Renderer *renderer,
				 SDL_Window *window, SDL_Texture *texture) {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}*/

int	main() {
	/** For window **/
	SDL_Window		*window = nullptr;
	SDL_Texture		*texture = nullptr;
	SDL_Renderer	*renderer = nullptr;

	/** --------- **/
	bool exit, pause, delay, delay1, try_again;
	exit = delay = delay1 = try_again = false;
	pause = true;
	SDL_Event event;
//	General_win gen_win = General_win();
	SDL_Rect tmp_rect;
	vector<Balls*> ball, life;
	vector<Enemy*> en;
	/** init part **/
/*
	gen_win.drawWindow(&renderer);
	gen_win.setSurfaceDraw("./images/back-ground.jpeg", renderer);

	Map *Mp = new Map(renderer);
	Pacman *Pac = new Pacman(renderer);
//	Map Mp = Map(renderer);
//	Pacman Pac = Pacman(renderer);
	initBall(renderer, ball, life, en, Mp->getMap());
*/
	/** init part with changes **/
	Map *Mp = nullptr;
	Pacman *Pac = nullptr;
	cout << "00\n";
	try {
		cout << "0\n";
		DrawWindow(&renderer, window);
		cout << "1\n";
		texture = SetSurfaceDraw("./images/back-ground.jpeg", renderer);
		cout << "2\n";

		Mp = new Map(renderer);
		Pac = new Pacman(renderer);
		initBall(renderer, ball, life, en, Mp->getMap());
	}
	catch (int i) {
		error_SDL(i, renderer, window);
	}
	/** --------- **/
	srand(time(0));
	while (!exit) {
		SDL_RenderClear(renderer);
//		SDL_RenderCopy(renderer, gen_win.getTexture(), nullptr, nullptr);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);

		tmp_rect = Mp->getRect();
		SDL_RenderCopy(renderer, Mp->getTexture(), nullptr, &tmp_rect);


		if (try_again) {
			try_again = to_start_pos(en, *Pac);
			pause = true;
		}
		for (size_t i = 0; i < life.size(); i++) {
			tmp_rect = life[i]->getRect();
			SDL_RenderCopy(renderer, life[i]->getTexture(), nullptr, &tmp_rect);
		}
		for (size_t i = 0; i < ball.size(); i++){
			tmp_rect = ball[i]->getRect();
			SDL_Rect tmp_rect1 = Pac->getRect();
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
			Pac->travel(Mp->getMap());
			delay = false;
		}
				else
			delay = true;
		delay1 ? delay1 = false : delay1 = true;

		for (size_t i = 0; i < en.size(); i++) {
			SDL_Point tmp_ptr = take_SDL_point(Pac->getRect());
			tmp_rect = en[i]->getRect();
			if (en[i]->get_set_eat()) {
				en[i]->get_set_eat()--;
			}
			if (!en[i]->getRun() && !SDL_PointInRect(&tmp_ptr, &tmp_rect)) {
				if (Mp->door_status())
					Mp->close_door();
				if (delay) {
					if (en[i]->getHome()) {
						if (!Mp->door_status())
							Mp->open_door();
						en[i]->go_out_home(Mp->getMap());
					}
					else if (en[i]->get_set_eat()) {
							if(delay1) {
//								cout << "enemy = " << i << "\n";
								en[i]->action(Mp->getMap());
							}
							en[i]->changeimg(false);
					}
					else {
						en[i]->action(Mp->getMap());
						en[i]->changeimg(true);
					}
				}
			}
			else {
				if (!Mp->door_status())
					Mp->open_door();
				if (en[i]->getRun()) {
					en[i]->runhome(Mp->getMap());
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

		while (SDL_PollEvent(&event) != 0 && event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					exit = true;
				else if (event.key.keysym.sym == SDLK_p)
					pause = true;
				else
					Pac->action(event);
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