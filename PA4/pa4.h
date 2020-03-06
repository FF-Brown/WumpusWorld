//#pragma once

#ifndef PA4_H
#define PA4_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include "GameWorld.h"

using namespace std;

struct Coordinate {
	int x;
	int y;
};
Coordinate randPosition(void);
ostream& operator<< (ostream& lhs, Coordinate& rhs);
Coordinate operator+ (const Coordinate& lhs, const Coordinate& rhs);
Coordinate operator- (const Coordinate& lhs, const Coordinate& rhs);

void displayMenu();
void displayControls();
void playGame();
char playerMove(GameWorld& world, char command);
bool didIMove(char input);
void resetGame(GameWorld& world);
void newGame(GameWorld& world);
void setName(GameWorld&);
ostream& operator<< (ostream& output, GameWorld& world);
void saveData(GameWorld& world);


#endif // !PA4_H


