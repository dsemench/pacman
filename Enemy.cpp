//
// Created by Dmitro Semenchuk on 9/26/17.
//

#include "Enemy.hpp"
#include <algorithm>

Enemy::Enemy(int i, SDL_Renderer *renderer) {
	string address_img;

	old_y_x[0] = old_y_x[1] = 0;
	_vect = vect = 4;
	_can_eat_em = 0;
	_run = false;
	_home = true;
	_speed = 1;
	_rect.h = 20;
	_rect.w = 20;
	_rect.x = 140 + (9 * 20) + (20 * i);
	_rect.y = 20 + (12 * 20);

	address_img = "./images/enemy/" + to_string(i) + to_string(1) + ".png";
	_arr_texture[3] = SetSurfaceDraw(address_img.c_str(), renderer);
	address_img = "./images/enemy/" + to_string(i) + to_string(2) + ".png";
	_arr_texture[1] = SetSurfaceDraw(address_img.c_str(), renderer);
	address_img = "./images/enemy/" + to_string(i) + to_string(3) + ".png";
	_arr_texture[2] = SetSurfaceDraw(address_img.c_str(), renderer);
	address_img = "./images/enemy/" + to_string(i) + to_string(4) + ".png";
	_arr_texture[0] = SetSurfaceDraw(address_img.c_str(), renderer);
	address_img = "./images/enemy/G1.png";
	_arr_texture[5] = SetSurfaceDraw(address_img.c_str(), renderer);
	address_img = "./images/enemy/G3.png";
	_arr_texture[6] = SetSurfaceDraw(address_img.c_str(), renderer);
	address_img = "./images/enemy/G2.png";
	_arr_texture[7] = SetSurfaceDraw(address_img.c_str(), renderer);
	address_img = "./images/enemy/G4.png";
	_arr_texture[8] = SetSurfaceDraw(address_img.c_str(), renderer);
	address_img = "./images/enemy/" + to_string(61) + ".png";
	_arr_texture[4] = SetSurfaceDraw(address_img.c_str(), renderer);
	_texture = _arr_texture[1];
	_hunt = true;
}

int			Enemy::makeRand(int r) {
	int res;

	res = rand() % r + 1;
	return res;
}


void		Enemy::action(int *map) {
	int x = _rect.x - 140, y = _rect.y - 20;
	bool check = false;

	if (_hunt)
		_texture = _arr_texture[vect - 1];
	if (vect != 0 && (_rect.y % 20 != 0 || _rect.x % 20 != 0)) {
		finish_mov_pos();
		if (_rect.y % 20 == 0 && _rect.x % 20 == 0)
			check = true;
	}
	else {
		_vect = makeChoice(y, x, map);
		if (_vect == 1 && !getRoad((y - 20) / 20, x / 20, map) && (y - 20) >= 0) {
			_rect.y -= _speed;
		}
		else if (_vect == 2 && !getRoad((y + 20) / 20, x / 20, map) && (y + 20) <= 580) {
			_rect.y += _speed;
		}
		else if (_vect == 3 && !getRoad(y / 20, (x - 20) / 20, map) && (x - 20) >= 0) {
			_rect.x -= _speed;
		}
		else if (_vect == 4 && !getRoad(y / 20, (x + 20) / 20, map) && (x + 20) <= 500) {
			_rect.x += _speed;
		}
		vect = _vect;
		old_y_x[0] = y;
		old_y_x[1] = x;
	}
	if (check)
		_vect = makeChoice(y, x, map);
}

bool		Enemy::finish_mov_pos() {
	if (_rect.y % 20 != 0 || _rect.x % 20 != 0) {
		if (vect == 1) {
			_rect.y -= _speed;
			return false;
		}
		else if (vect == 2) {
			_rect.y += _speed;
			return false;
		}
		else if (vect == 3) {
			_rect.x -= _speed;
			return false;
		}
		else if (vect == 4) {
			_rect.x += _speed;
			return false;
		}
	}
	return true;
}

void		Enemy::changeimg(bool condition, bool run) {
	if (!run) {
		if (_hunt == condition)
			return;
		if (!condition)
			_texture = _arr_texture[4];
		else {
			if (_vect < 5) {
				_texture = _arr_texture[1];
			}
		}
		_hunt = condition;
	}
	else
		_texture = _arr_texture[_vect + 4];
}

int			Enemy::makeChoice(int y, int x, int *map) {
	vector<int>	choise;
	int			res = 0;

	choise = createVecChoise(y, x, map);
	if (choise.size() > 1) {
		while (!res) {
			int tmp;
			tmp = makeRand(4);
			for (size_t i = 0; i < choise.size() && !res; i++) {
				if (tmp == choise[i] && tmp != _vect)
					res = tmp;
			}
		}
	}
	else
		return choise[0];
	return res;
}

void		Enemy::go_to_pos(vector<int> choise,
						int pos_y, int pos_x, int y, int x) {
	pair<int, int> res(100, 100);

	if (find(choise.begin(), choise.end(), 1) != choise.end()
		&& res.second > (pos_y - ((y - 20) / 20))) {
		res.first = 1;
		res.second = pos_y - ((y - 20) / 20);
	}
	if (find(choise.begin(), choise.end(), 2) != choise.end()
		&& res.second > (((y + 20) / 20) - pos_y)) {
		res.first = 2;
		res.second = ((y + 20) / 20) - pos_y;
	}
	if (find(choise.begin(), choise.end(), 3) != choise.end()
		&& res.second > (pos_x - ((x - 20) / 20))) {
		res.first = 3;
		res.second = pos_x - ((x - 20) / 20);
	}
	if (find(choise.begin(), choise.end(), 4) != choise.end()
		&& res.second > (((x + 20) / 20) - pos_x)) {
		res.first = 4;
		res.second = ((x + 20) / 20) - pos_x;
	}
	_vect = res.first;
}

void		Enemy::makeFirst_step() {
	if (_vect == 1) {
		_rect.y -= _speed;
	}
	else if (_vect == 2) {
		_rect.y += _speed;
	}
	else if (_vect == 3) {
		_rect.x -= _speed;
	}
	else if (_vect == 4) {
		_rect.x += _speed;
	}
	vect = _vect;
}

void		Enemy::runhome(int *map) {
	vector<int>	choise;
	int			x = _rect.x - 140, y = _rect.y - 20;

	if (finish_mov_pos()) {
		choise = createVecChoise(y, x, map);
		go_to_pos(choise, 13, 13, y, x);
		makeFirst_step();
		old_y_x[0] = y;
		old_y_x[1] = x;
		SDL_Point tmp_ptr;
		tmp_ptr.x = 260 + 140;
		tmp_ptr.y = 260 + 20;
		if (SDL_PointInRect(&tmp_ptr, &_rect)) {
			_run = false;
			_home = true;
			_can_eat_em = 0;
			changeimg(true);
		}
		else
			changeimg(false, true);
	}
}

void		Enemy::go_out_home(int *map) {
	int x = _rect.x - 140, y = _rect.y - 20;

	if (finish_mov_pos()) {
		go_to_pos(createVecChoise(y, x, map), 9, 14, y, x);
		makeFirst_step();
		old_y_x[0] = y;
		old_y_x[1] = x;
		SDL_Point tmp_ptr;
		tmp_ptr.x = 220 + 140;
		tmp_ptr.y = 200 + 20;
		if (SDL_PointInRect(&tmp_ptr, &_rect)) {
			_home = false;
		}
	}
}

vector<int>	Enemy::createVecChoise(int y, int x, int *map) {
	vector<int> res;

	if (_vect != 2 && !getRoad((y - 20) / 20, x / 20, map)
		&& ((y - 20) != old_y_x[0])) {
		res.push_back(1);
	}
	if (_vect != 1 && !getRoad((y + 20) / 20, x / 20, map)
		&& ((y + 20) != old_y_x[0])) {
		res.push_back(2);
	}
	if (_vect != 4 && !getRoad(y / 20, (x - 20) / 20, map)
		&& ((x - 20) != old_y_x[1])) {
		res.push_back(3);
	}
	if (_vect != 3 && !getRoad(y / 20, (x + 20) / 20, map)
		&& ((x + 20) != old_y_x[1])) {
		res.push_back(4);
	}
	return res;
}
