#include<iostream>
#include<cstdlib>
#include<string>
#include<conio.h>

#include "gameSystem.h"

using namespace std;

int main() {
	gameSystem gameSystem("level.txt");
	gameSystem.playGame();
	
	return 0;
}