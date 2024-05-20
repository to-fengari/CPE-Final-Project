#include "player.h"

player::player() {
	_x = 0;
	_y = 0;

}

void player::init(int health) {
	_health = health;
}

void player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void player::getPosition(int& x, int& y) const {
	x = _x;
	y = _y;
}

int player::takeDamage(int attack) {
	if (attack > 0) {
		_health -= attack;
		if (_health <= 0) {
			return 1;
		}
	}
	return 0;
}