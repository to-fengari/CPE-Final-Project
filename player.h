#pragma once
#include <random>
#include <ctime>
using namespace std;

class player
{
public:
	player();
	void init(int health);
	int takeDamage(int attack);
	void setPosition(int x, int y);
	void getPosition(int &x, int &y) const;

private: 
	int _health;
	int _x;
	int _y;
};


