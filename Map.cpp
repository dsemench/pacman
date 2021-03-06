//
// Created by Dmitro Semenchuk on 9/25/17.
//

#include "Map.hpp"

Map::Map(SDL_Renderer *renderer) {
	_map[0] = 12288;
	_map[1] = 32487390;
	_map[2] = 32487390;
	_map[3] = 32487390;
	_map[4] = 0;
	_map[5] = 32374494;
	_map[6] = 32374494;
	_map[7] = 798912;
	_map[8] = 66041823;
	_map[9] = 66041823;
	_map[10] = 65798367;
	_map[11] = 65916639;
	_map[12] = 65864415;
	_map[13] = 65077791;
	_map[14] = 65864415;
	_map[15] = 65928927;
	_map[16] = 65798367;
	_map[17] = 65928927;
	_map[18] = 65928927;
	_map[19] = 12288;
	_map[20] = 32487390;
	_map[21] = 32487390;
	_map[22] = 6291480;
	_map[23] = 57540315;
	_map[24] = 57540315;
	_map[25] = 798912;
	_map[26] = 33535998;
	_map[27] = 33535998;
	_map[28] = 0;

	_texture = SetSurfaceDraw("./images/map.png", renderer);

	_rect.h = 620;
	_rect.w = 560;
	_rect.y = 0;
	_rect.x = 120;
};
