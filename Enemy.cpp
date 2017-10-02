//
// Created by Dmitro Semenchuk on 9/26/17.
//

#include "Enemy.hpp"

Enemy::Enemy(int i, SDL_Renderer *renderer) {
	string address_img;//("./images/enemy/");

	old_y_x[0] = old_y_x[1] = 0;
	_vect = 4;
	vect = 4;
	_can_eat_em = 0;
	_run = false;
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
//	address_img = "./images/enemy/" + to_string(b) + to_string(1) + ".png";
	address_img = "./images/balls_cherry/b1.png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[5] = _texture;
//	address_img = "./images/enemy/" + to_string(i) + to_string(2) + ".png";
	address_img = "./images/balls_cherry/b1.png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[6] = _texture;
//	address_img = "./images/enemy/" + to_string(i) + to_string(3) + ".png";
	address_img = "./images/balls_cherry/b1.png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[7] = _texture;
//	address_img = "./images/enemy/" + to_string(i) + to_string(4) + ".png";
	address_img = "./images/balls_cherry/b1.png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[8] = _texture;

	address_img = "./images/enemy/" + to_string(61) + ".png";
	setSurfaceDraw(address_img.c_str(), renderer);
	_arr_texture[4] = _texture;
	_texture = _arr_texture[1];
	_hunt = true;

}

int Enemy::makeRand(int r) {
	int res;

	res = rand() % r + 1;
//	std::cout << "rand = " << res << "\n";
	return res;
}


void Enemy::action(int *map) {
	int x = _rect.x - 140, y = _rect.y - 20;
	bool check = false;

	if (_hunt)
		_texture = _arr_texture[vect - 1];
	if (vect != 0 && (_rect.y % 20 != 0 || _rect.x % 20 != 0)) {//make virtual for two classes
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

bool Enemy::finish_mov_pos() {
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

void Enemy::changeimg(bool condition, bool run) {
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

int Enemy::makeChoice(int y, int x, int *map) {
	vector<int> choise;
	int res = 0;

	if (_vect != 2 && !getRoad((y - 20) / 20, x / 20, map)
		&& ((y - 20) != old_y_x[0])) {
		choise.push_back(1);
	}
	if (_vect != 1 && !getRoad((y + 20) / 20, x / 20, map)
		&& ((y + 20) != old_y_x[0])) {
		choise.push_back(2);
	}
	if (_vect != 4 && !getRoad(y / 20, (x - 20) / 20, map)
		&& ((x - 20) != old_y_x[1])) {
		choise.push_back(3);
	}
	if (_vect != 3 && !getRoad(y / 20, (x + 20) / 20, map)
		&& ((x + 20) != old_y_x[1])) {
		choise.push_back(4);
	}
//	for (size_t i = 0; i < choise.size() && !res; i++) {
//		cout << choise[i] << " ";
//	}
//	cout << "\n";
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

void Enemy::runhome(int *map) {
	vector<int> choise;
	int x = _rect.x - 140, y = _rect.y - 20;//current position

	if (finish_mov_pos()) {
		pair<int, int> res(100, 100);

		if (!getRoad((y - 20) / 20, x / 20, map)
			&& ((y - 20) != old_y_x[0])) {
			choise.push_back(1);
		}
		if (!getRoad((y + 20) / 20, x / 20, map)
			&& ((y + 20) != old_y_x[0])) {
			choise.push_back(2);
		}
		if (!getRoad(y / 20, (x - 20) / 20, map)
			&& ((x - 20) != old_y_x[1])) {
			choise.push_back(3);
		}
		if (!getRoad(y / 20, (x + 20) / 20, map)
			&& ((x + 20) != old_y_x[1])) {
			choise.push_back(4);
		}
//	for (size_t i = 0; i < choise.size(); i++) {
//		cout << choise[i] << " ";
//	}
//	cout << "\n";
		if (find(choise.begin(), choise.end(), 1) != choise.end()
			&& res.second > (13 - ((y - 20) / 20))) {
			res.first = 1;
			res.second = 13 - ((y - 20) / 20);
		}
		if (find(choise.begin(), choise.end(), 2) != choise.end()
			&& res.second > (((y + 20) / 20) - 13)) {
			res.first = 2;
			res.second = ((y + 20) / 20) - 13;
		}
		if (find(choise.begin(), choise.end(), 3) != choise.end()
			&& res.second > (13 - ((x - 20) / 20))) {
			res.first = 3;
			res.second = 13 - ((x - 20) / 20);
		}
		if (find(choise.begin(), choise.end(), 4) != choise.end()
			&& res.second > (((x + 20) / 20) - 13)) {
			res.first = 4;
			res.second = ((x + 20) / 20) - 13;
		}
		_vect = res.first;
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
		old_y_x[0] = y;
		old_y_x[1] = x;
		SDL_Point tmp_ptr;
		tmp_ptr.x = 260 + 140;
		tmp_ptr.y = 260 + 20;
		if (SDL_PointInRect(&tmp_ptr, &_rect)) {
			cout << "change\n";
			_run = false;
			_can_eat_em = 0;
		}
		else
			changeimg(false, true);
	}
}

