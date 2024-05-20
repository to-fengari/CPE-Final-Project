#include "level.h"
#include<fstream>
#include<iostream>
#include<cstdio>

using namespace std;

level::level() {
 }

void level::load(string fileName,player &player) {

	ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		exit(1);
	}
	
	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);
	}
	file.close();

	char tile;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@':
				player.setPosition(j, i);
				break;
			case 'M':
				_enemies.push_back(enemy("Math", tile, 10));
				_enemies.back().setPosition(j, i);
				break;
			case 'S':
				_enemies.push_back(enemy("Science", tile,5));
				_enemies.back().setPosition(j, i);
				break;
			case 'P':
				_enemies.push_back(enemy("Programming", tile,10));
				_enemies.back().setPosition(j, i);
				break;
			case 'R':
				_enemies.push_back(enemy("Rizal", tile,5));
				_enemies.back().setPosition(j, i);
				break;
			case 'E':
				_enemies.push_back(enemy("English", tile,5));
				_enemies.back().setPosition(j, i);
				break;
			case 'C':
				_enemies.push_back(enemy("Contemporary World", tile, 5));
				_enemies.back().setPosition(j, i);
				break;
			case 'U':
				_enemies.push_back(enemy("Understanding the Self", tile, 5));
				_enemies.back().setPosition(j, i);
				break;
			}
		}
	}
}

void level::print() {

	cout << string(100, '\n');
	cout << "Welcome to Academic Adventures: Quest for Knowledge" << endl;
	for (int i = 0; i < _levelData.size(); i++) {
		cout << _levelData[i] <<endl;
	}
	cout << endl;
}

void level::movePlayer(char input,player &player) {
	
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);

	switch (input) {
	case'w':
	case'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case'S':
	case's':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case'a':
	case'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case'd':
	case'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("Invalid Input\n");
		system("pause");
	}
}

void level::updateEnemies(player& player) {
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;


	player.getPosition(playerX, playerY);
	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (aiMove) {
		case 'w':
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's':
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a':
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd':
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;

		}
	}
}

char level::getTile(int x, int y){
		return _levelData[y][x];
}

void level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;
}

void level::processPlayerMove(player& player, int targetX, int targetY) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case ' ':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, ' ');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	case '=':
		cout << endl << "Congratulations... You have obtained the book of Knowledge..." << endl
			<< "exiting the game" << endl;
		system("pause");
		exit(0);
	default:
		encounter(player, targetX, targetY);

	}
}

void level::processEnemyMove(player& player, int enemyIndex, int targetX, int targetY) {
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case ' ':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, ' ');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		encounter(player, enemyX, enemyY);
		break;
	case '#':
		break;
	default:
		break;
	}
}

void level::encounter(player& player, int targetX, int targetY) {
		int enemyX, enemyY, attackRoll, attackResult = 0, playerX, playerY, lineStart, lineEnd, answerNum;
		string enemyName;

		player.getPosition(playerX, playerY);


		for (int i = 0; i < _enemies.size(); i++) {
			
			_enemies[i].getPosition(enemyX, enemyY);
			enemyName = _enemies[i].getName();
			if (targetX == enemyX && targetY == enemyY) {
				
				char tile = getTile(targetX, targetY);
				
				attackResult = encounterSubject(tile, lineStart, lineEnd, answerNum);

				if (attackResult == 1) {
					setTile(targetX, targetY, ' ');
					print();
					printf("Correct!!!\n");
					_enemies[i] = _enemies.back();
					_enemies.pop_back();
					i--;
					system("pause");

					return;
				}

				attackRoll = _enemies[i].attack();
				cout << "The " << enemyName.c_str() << " Spirit attacked player with a roll of: " << attackRoll << endl;
				attackResult = player.takeDamage(attackRoll);
				system("pause");

				if (attackResult != 0) {

					setTile(playerX, playerY, 'X');
					printf("You died!\n");
					system("Pause");
					cin.ignore();

					exit(0);
				}

				return;
			}

		}


	}


int level :: questionPick(int& lineStart, int& lineEnd, int& answerNum) {
	
	cout << endl;
	int line = 0;
	int num = 0;
	string answer;	
	string question;
	string correctAnswer;

	ifstream questions, answers;
	questions.open("questions.txt");
	answers.open("answers.txt");



	while (line < lineStart - 1){
	getline(questions, question);
	line ++;
	}	

	while (line < lineEnd) {
	getline(questions, question);
	cout << question << endl;
	line++;
	}
	
	while (num < answerNum) {
		getline(answers, correctAnswer);
		num++;
	}

	cout << "Answer:";
	cin >> answer;
	

	if (answer != correctAnswer) {
		return 0;
	}
		else if (answer == correctAnswer) {
			return 1;
		}
			

}


int level::encounterSubject(char tile, int& lineStart, int& lineEnd, int& answerNum) {
	int i = 0;
	switch (tile) {
	case 'M':
			lineStart = 1;
			lineEnd = 5;
			answerNum = 1;
			i = questionPick(lineStart, lineEnd, answerNum);
			if (i == 1) {
				return 1;
			}
				else if (i != 1) {
					return 0;
				}
		break;
	case 'S':
			lineStart = 11;
			lineEnd = 15;
			answerNum = 3;
			i = questionPick(lineStart, lineEnd, answerNum);
			if (i == 1) {
				return 1;
			}
				else if (i != 1) {
					return 0;
				}
		break;
	case 'P':
			lineStart = 31;
			lineEnd = 35;
			answerNum = 7;
			i = questionPick(lineStart, lineEnd, answerNum);
			if (i == 1) {
				return 1;
			}
				else if (i != 1) {
					return 0;
				}
		break;
	case 'E':
			lineStart = 36;
			lineEnd = 40;
			answerNum = 8;
			i = questionPick(lineStart, lineEnd, answerNum);
			if (i == 1) {
				return 1;
			}
				else if (i != 1) {
					return 0;
				}
		break;
	case 'R':
			lineStart = 46;
			lineEnd = 50;
			answerNum = 10;
			i = questionPick(lineStart, lineEnd, answerNum);
			if (i == 1) {
				return 1;
			}
				else if (i != 1) {
					return 0;
				}
		break;
	case 'U':
			lineStart = 51;
			lineEnd = 55;
			answerNum = 11;
			i = questionPick(lineStart, lineEnd, answerNum);
			if (i == 1) {
				return 1;
			}
				else if (i != 1) {
					return 0;
				}
		break;
	case 'C':
			lineStart = 61;
			lineEnd = 65;
			answerNum = 13;
			i = questionPick(lineStart, lineEnd, answerNum);
			if ( i == 1) {
				return 1;
			}
				else if (i != 1) {
					return 0;
				}
		break;
	}
}