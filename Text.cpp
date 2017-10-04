//
// Created by Dmitro Semenchuk on 10/4/17.
//

#include "Text.hpp"


Text::Text(SDL_Renderer *renderer) {
	_sans = create_text_style();
	_blue.b = 255;
	_blue.a = _blue.g = _blue.r = 0;
	_score_rect.h = 15;
	_score_rect.w = 45;
	_score_rect.y = 20;
	_score_rect.x = 10;

	_rect.h = 15;
	_rect.w = 45;
	_rect.y = 560;
	_rect.x = 10;
	_texture = words_text(renderer, _sans, _blue, "Lifes");
	_score = words_text(renderer, _sans, _blue, "Score");
}
