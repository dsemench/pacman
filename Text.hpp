//
// Created by Dmitro Semenchuk on 10/4/17.
//

#ifndef PACMAN_TEXT_HPP
#define PACMAN_TEXT_HPP

#include "Hight_cl.hpp"

class Text : public Hight_cl {
private:
	TTF_Font	*_sans;
	SDL_Color	_blue;
	SDL_Texture	*_score;
	SDL_Rect	_score_rect;
	SDL_Texture	*_keys[7];
	SDL_Rect	_keys_rect[7];

public:
	Text(SDL_Renderer *renderer);
	SDL_Texture	*getScoreTexture() { return _score; };
	SDL_Rect getScore_rect() { return _score_rect; };
	SDL_Texture	*getKeysTexture(int i) { return _keys[i]; };
	SDL_Rect getkeys_rect(int i) { return _keys_rect[i]; };
};


#endif //PACMAN_TEXT_HPP
