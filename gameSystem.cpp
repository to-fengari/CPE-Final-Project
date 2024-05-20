 #include "gameSystem.h"
#include <iostream>
#include <conio.h>



gameSystem::gameSystem(string levelFileName){
	_player.init(5);
	_level.load(levelFileName, _player);
	_level.print();

}

void gameSystem::playGame() {
	
	bool isDone = false;
	while (isDone != true) {
		_level.print();
		playerMove();
		_level.updateEnemies(_player);
	}
}

void gameSystem::playerMove() {
	char input;
	cout << "Enter a move command (w/s/a/d):";
	input = _getch();

	_level.movePlayer(input, _player);
}