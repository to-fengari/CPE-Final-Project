#include "enemy.h"

enemy::enemy(string name, char tile, int attack) {
	_name = name;
	_tile = tile;
	_attack = attack;
}

void enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void enemy::getPosition(int& x, int& y) const {
	x = _x;
	y = _y;

}

char enemy::getMove(int playerX, int playerY) const {

	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0.0, 6.0);


	int distance;
	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx);
	int ady = abs(dy);
	distance = adx + ady;


	if (distance <= 5) {

		if (adx > ady) {
			if (dx > 0) {
				return 'a';
			}
			else {
				return 'd';
			}
		}
		else { 
			if (dy > 0) {
				return 'w';
			}
			else {
				return 's';
			}
		}
	}

	int randomMove = moveRoll(randomEngine);

	switch (randomMove) {
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return ' ';
	}
}

int enemy::attack() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);
	return attackRoll(randomEngine);
}
