//
// Created by Dmitro Semenchuk on 9/26/17.
//

#include "Enemy.hpp"

Enemy::Enemy(int i, SDL_Renderer *renderer) {
	string address_img;//("./images/enemy/");

	count_steps = 0;
	old_vect = 0;
	_vect = 4;
	vect = 4;
	_speed = 1;
	_rect.h = 20;
	_rect.w = 20;
	_rect.x = 140 + (9 * 20) + (20 * i);
//	_rect.y = 20 + (12 * 20);
	_rect.y = 20 + (16 * 20);
	address_img = "./images/enemy/" + to_string(i) + to_string(1) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[3] = _texture;
	address_img = "./images/enemy/" + to_string(i) + to_string(2) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[1] = _texture;
	address_img = "./images/enemy/" + to_string(i) + to_string(3) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[2] = _texture;
	address_img = "./images/enemy/" + to_string(i) + to_string(4) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[0] = _texture;
	address_img = "./images/enemy/" + to_string(61) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[4] = _texture;
	_texture = _arr_texture[1];
	_hunter = true;

}

int Enemy::makeRand(int r) {
	int res;

	res = rand() % r + 1;
//	std::cout << "rand = " << res << "\n";
	return res;
}


void Enemy::action(int *map) {
	int x = _rect.x - 140, y = _rect.y - 20;

	if (_hunter)
		_texture = _arr_texture[vect - 1];
	if (vect != 0 && (_rect.y % 20 != 0 || _rect.x % 20 != 0)) {
		if (vect == 1) {
			_rect.y -= _speed;
		}
		else if (vect == 2) {
			_rect.y += _speed;
		}
		else if (vect == 3) {
			_rect.x -= _speed;
		}
		else if (vect == 4) {
			_rect.x += _speed;
		}
	} else {
		if (_vect == 1 && !getRoad((y - 20) / 20, x / 20, map)) {
			if ((y - 20) >= 0) {
				_rect.y -= _speed;
				vect = _vect;
				count_steps++;
			}
		}
		else if (_vect == 2 && !getRoad((y + 20) / 20, x / 20, map)) {
			if ((y + 20) <= 580) {
				_rect.y += _speed;
				vect = _vect;
				count_steps++;
			}
		}
		else if (_vect == 3 && !getRoad(y / 20, (x - 20) / 20, map)) {
			if ((x - 20) >= 0) {
				_rect.x -= _speed;
				vect = _vect;
				count_steps++;
			}
		}
		else if (_vect == 4 && !getRoad(y / 20, (x + 20) / 20, map)) {
			if ((x + 20) <= 500) {
				_rect.x += _speed;
				vect = _vect;
				count_steps++;
			}
		}
		else {
			if (vect == 1 && !getRoad((y - 20) / 20, x / 20, map)) {
				_rect.y -= _speed;
			}
			else if (vect == 2 && !getRoad((y + 20) / 20, x / 20, map)) {
				_rect.y += _speed;
			}
			else if (vect == 3 && !getRoad(y / 20, (x - 20) / 20, map)) {
				_rect.x -= _speed;
			}
			else if (vect == 4 && !getRoad(y / 20, (x + 20) / 20, map)) {
				_rect.x += _speed;
			}
		}
	}
	if (old_vect != _vect)
		_vect = makeChoice(y, x, map);
}

void Enemy::changeimg(bool condition) {

	if (_hunter == condition)
		return ;
	if (!condition)
		_texture = _arr_texture[4];
	else {
		if (_vect < 5) {
			_texture = _arr_texture[1];
		}
	}
	_hunter = condition;
}

int Enemy::makeChoice(int y, int x, int *map) {
	vector<int> choise;
	int res = 0;

	count_steps = 0;
	if (!getRoad((y - 20) / 20, x / 20, map)) {
		choise.push_back(1);
	}
	if (!getRoad((y + 20) / 20, x / 20, map)) {
		choise.push_back(2);
	}
	if (!getRoad(y / 20, (x - 20) / 20, map)) {
		choise.push_back(3);
	}
	if (!getRoad(y / 20, (x + 20) / 20, map)) {
		choise.push_back(4);
	}

	while (!res) {
		int tmp;
		tmp = makeRand(4);
		for (size_t i = 0; i < choise.size() && !res; i++) {
			if (tmp == choise[i] && tmp != _vect /*&& tmp != old_vect*/)
				res = tmp;
		}
	}
	old_vect = _vect;
	return res;
}
