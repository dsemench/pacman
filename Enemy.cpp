//
// Created by Dmitro Semenchuk on 9/26/17.
//

#include "Enemy.hpp"

Enemy::Enemy(int i, SDL_Renderer *renderer) {
	string address_img;//("./images/enemy/");

	_num_en = i;
	old_y_x[0] = old_y_x[1] = old_y_x[2] = old_y_x[3] = 0;
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
	bool check = false;

	if (_hunter)
		_texture = _arr_texture[vect - 1];
	if (vect != 0 && (_rect.y % 20 != 0 || _rect.x % 20 != 0)) {//make virtual for two classes
		cout << "if\n";
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
		old_y_x[2] = y;
		old_y_x[3] = x;
		if (_rect.y % 20 == 0 && _rect.x % 20 == 0)
		check = true;
	//		cout << "y = " << _rect.y << " x = " << _rect.x << "\n";
	}
	else {
		cout << "else\n";
//		check = true;
		_vect = makeChoice(y, x, map);
		if (_vect == 1 && !getRoad((y - 20) / 20, x / 20, map)) {
			if ((y - 20) >= 0) {
				cout << "1\n";
				_rect.y -= _speed;
				vect = _vect;
				old_y_x[0] = y;
//				old_y_x[0] = y - 20;
				old_y_x[1] = x;
			}
		}
		else if (_vect == 2 && !getRoad((y + 20) / 20, x / 20, map)) {
			if ((y + 20) <= 580) {
				cout << "2\n";
				_rect.y += _speed;
				vect = _vect;
				old_y_x[0] = y;
//				old_y_x[0] = y + 20;
				old_y_x[1] = x;
			}
		}
		else if (_vect == 3 && !getRoad(y / 20, (x - 20) / 20, map)) {
			if ((x - 20) >= 0) {
				cout << "3\n";
				_rect.x -= _speed;
				vect = _vect;
				old_y_x[0] = y;
				old_y_x[1] = x;
//				old_y_x[1] = x - 20;
			}
		}
		else if (_vect == 4 && !getRoad(y / 20, (x + 20) / 20, map)) {
			cout << "4.0\n";
			if ((x + 20) <= 500) {
				cout << "4\n";
				_rect.x += _speed;
				vect = _vect;
				old_y_x[0] = y;
				old_y_x[1] = x;
//				old_y_x[1] = x + 20;
			}
		}
	}
	if (check)
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

	if (!getRoad((y - 20) / 20, x / 20, map) && _vect != 2
		&& ((y - 20) != old_y_x[0]) && ((y - 20) != old_y_x[2])) {
		choise.push_back(1);
	}
	if (!getRoad((y + 20) / 20, x / 20, map) && _vect != 1
		&& ((y + 20) != old_y_x[0]) && ((y + 20) != old_y_x[2])) {
		choise.push_back(2);
	}
	if (!getRoad(y / 20, (x - 20) / 20, map) && _vect != 4
		&& ((x - 20) != old_y_x[1]) && ((x - 20) != old_y_x[3])) {
		choise.push_back(3);
	}
	if (!getRoad(y / 20, (x + 20) / 20, map) && _vect != 3
		&& ((x + 20) != old_y_x[1]) && ((x - 20) != old_y_x[3])) {
		choise.push_back(4);
	}
	for (size_t i = 0; i < choise.size() && !res; i++) {
		cout << choise[i] << " ";
	}
	cout << "\n";
	if (choise.size() > 1) {
		while (!res) {
			int tmp;
			tmp = makeRand(4);
			for (size_t i = 0; i < choise.size() && !res; i++) {
				if (tmp == choise[i] && tmp != _vect)
					res = tmp;
			}
//		}
		}
	}
	else
		return choise[0];
	old_vect = _vect;
	return res;
}
