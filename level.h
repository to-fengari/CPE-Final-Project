#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "enemy.h"

using namespace std;

class level{
public:
	level();

	void load(string filename, player &player);
	void print();

	void movePlayer(char input, player& player);
	void updateEnemies(player &player);

	char getTile(int x, int y);
	void setTile(int x, int y, char tile);
	

private: 
	void processEnemyMove(player &player, int enemyIndex, int targetX, int targetY);
	void processPlayerMove(player &player, int targetX, int targetY);
	void encounter(player &player, int targetX, int targetY);
	int  questionPick(int &lineStart, int &lineEnd, int& answerNum);
	int  encounterSubject(char i, int &lineStart, int &lineEnd, int &answerNum);

	vector <string> _levelData;
	vector <enemy> _enemies;


};

