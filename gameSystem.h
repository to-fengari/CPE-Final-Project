#pragma once
#include "Player.h"
#include <string>
#include "Level.h"
#include <iostream>

using namespace std;


class gameSystem
{
public:
	gameSystem(string levelFileName);
	void playGame();
	void playerMove();

private: 
	level _level;
	player _player;
};

