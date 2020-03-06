//#pragma once

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "pa4.h"

class GameWorld {
private:
	char board[5][5];
	Coordinate playerPosition;
	int score;
	string name;

public:
	GameWorld();
	char getTile(int x, int y);
	Coordinate findPlayer(void);
	string getName();
	void setName(string newName);
	int getScore();
	void setScore(int newScore);
	void incrementScore();
	void viewPenalty();
	void cheatPenalty();
	void displayEntireWorld();
	void displayVisibleWorld();
	void placePiece(char piece, char def);
	char moveUp();
	char moveDown();
	char moveRight();
	char moveLeft();
	bool haveIWon(char destination);
	bool amIAlive(char destination);
};

#endif // !GAMEWORLD_H

