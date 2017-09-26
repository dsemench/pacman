//
// Created by Dmitro Semenchuk on 9/26/17.
//

#include "Enemy.hpp"

Enemy::Enemy(int i, SDL_Renderer *renderer) {
	string address_img;//("./images/enemy/");
	_rect.h = 20;
	_rect.w = 20;
	_rect.x = 140 + 180 + (20 * i);
	_rect.y = 20 + 240;
	address_img = "./images/enemy/" + to_string(i) + to_string(1) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[0] = _texture;
	address_img = "./images/enemy/" + to_string(i) + to_string(2) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[1] = _texture;
	address_img = "./images/enemy/" + to_string(i) + to_string(3) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[2] = _texture;
	address_img = "./images/enemy/" + to_string(i) + to_string(4) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[3] = _texture;
	address_img = "./images/enemy/" + to_string(61) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[4] = _texture;
	_texture = _arr_texture[1];
//	setSurfaceDraw("./images/enemy/11.png", renderer);
}