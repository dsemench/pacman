//
// Created by Dmitro Semenchuk on 10/4/17.
//

#include "Text.hpp"


Text::Text(SDL_Renderer *renderer) {
	_sans = create_text_style();
	_blue.b = 255;
	_blue.a = _blue.g = _blue.r = 0;
	_score_rect.h = 15;
	_score_rect.w = 70;//50
	_score_rect.y = 20;
	_score_rect.x = 10;

	_rect.h = 15;
	_rect.w = 70;//50
	_rect.y = 560;
	_rect.x = 10;
	_texture = words_text(renderer, _sans, _blue, "Lifes");
	_score = words_text(renderer, _sans, _blue, "Score");
	_keys[0] = words_text(renderer, _sans, _blue, "Manual         ");
	_keys[1] = words_text(renderer, _sans, _blue, "arrow     up   ");
	_keys[2] = words_text(renderer, _sans, _blue, "arrow     down ");
	_keys[3] = words_text(renderer, _sans, _blue, "arrow     left ");
	_keys[4] = words_text(renderer, _sans, _blue, "arrow     right");
	_keys[5] = words_text(renderer, _sans, _blue, "key p     pause");
	_keys[6] = words_text(renderer, _sans, _blue, "key esc   exit ");
	for (int i = 0; i < 7; i++) {
		_keys_rect[i].h = 12;
		_keys_rect[i].w = 140;//140
		_keys_rect[i].y = 210 + (25 * i);
		_keys_rect[i].x = 600;
	}
}
