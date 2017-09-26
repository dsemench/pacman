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
	_map[11] = 65928927;//open room 65916639 close 65928927
	_map[12] = 65864415;//enemy room
	_map[13] = 65077791;//enemy room
	_map[14] = 65864415;//enemy room
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

	setSurfaceDraw("./images/map.png", renderer);

	_rect.h = 620;//hight
	_rect.w = 560;//width
	_rect.x = 120;//horizontal pos
	_rect.y = 0;//vertical pos
//	_renderer = renderer;
};

////_rect.h = 580;//588;//hight
////_rect.w = 520;//528;//width
////_rect.x = 140;//horizontal pos
////_rect.y = 20;//vertical pos


//bool Map::getRoad(int y, int x) {
//	x = (x * -1) + 25;
//	if ((_map[y] >> x) % 2 == 1)
//		return true;
//	else
//		return false;
//}
