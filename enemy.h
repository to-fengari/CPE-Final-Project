#pragma once
#include <iostream>
#include <string>
#include <random>
#include <ctime>

using namespace std;
class enemy
{
public: 
	enemy(string _name, char tile, int attack);
	int attack();
	void setPosition(int x, int y);
	void getPosition(int& x, int& y) const;
	string getName() { return _name; }
	char getTile() const { return _tile; };
	char getMove(int playerX, int playerY) const;

private:
	string _name;
	char _tile;
	int _attack;
	int _x = 0;
	int _y = 0;
};

