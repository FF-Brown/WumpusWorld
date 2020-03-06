

#include "GameWorld.h"

GameWorld::GameWorld()
{
	Coordinate temp;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			board[i][j] = ' ';
		}
	}
	playerPosition = randPosition();
	board[playerPosition.x][playerPosition.y] = 'U';
	placePiece('W', ' '); //Wumpus
	placePiece('G', ' '); //Gold
	int pits = rand() % 6 + 5; //Set # of pits
	for (int i = 0; i < pits; ++i)
		placePiece('P', ' '); //Pit
	score = 0;
	name = "<blank>";
}
char GameWorld::getTile(int x, int y)
{
	return board[x][y];
}
Coordinate GameWorld::findPlayer(void)
{
	return playerPosition;
}
string GameWorld::getName()
{
	return name;
}
void GameWorld::setName(string newName)
{
	name = newName;
}
int GameWorld::getScore()
{
	return score;
}
void GameWorld::setScore(int newScore)
{
	score = newScore;
}
void GameWorld::incrementScore()
{
	score += 5;
}
void GameWorld::viewPenalty()
{
	score -= 2;
}
void GameWorld::cheatPenalty()
{
	score -= 5;
}
void GameWorld::displayEntireWorld()
{
	cout << "     |     |     |     |     |\n";
	cout << "  ";
	for (int i = 0; i < 5; ++i) cout << board[0][i] << "  |  ";
	cout << endl;
	for (int j = 1; j < 5; ++j) {
		cout << "_____|_____|_____|_____|_____|\n";
		cout << "     |     |     |     |     |\n";
		cout << "  ";
		for (int i = 0; i < 5; ++i) cout << board[j][i] << "  |  ";
		cout << endl;
	}
	cout << "     |     |     |     |     |\n";
}
void GameWorld::displayVisibleWorld()
{
	cout << "     |     |     |     |     |\n";
	cout << "  ";
	for (int i = 0; i < 5; ++i) {
		if (playerPosition.x <= 1 && (playerPosition.y - i <= 1 && playerPosition.y - i >= -1))
			cout << board[0][i] << "  |  ";
		else
			cout << ' ' << "  |  ";
	}
	cout << endl;

	for (int j = 1; j < 5; ++j) {
		cout << "_____|_____|_____|_____|_____|\n";
		cout << "     |     |     |     |     |\n";
		cout << "  ";
		for (int i = 0; i < 5; ++i) {
			if (playerPosition.x - j <= 1 && playerPosition.x - j >= -1 && playerPosition.y - i <= 1 && playerPosition.y - i >= -1)
				cout << board[j][i] << "  |  ";
			else
				cout << ' ' << "  |  ";
		}
		cout << endl;
	}

	cout << "     |     |     |     |     |\n";

}
void GameWorld::placePiece(char piece, char def)
{
	Coordinate temp;
	do {
		temp = randPosition();
	} while (board[temp.x][temp.y] != def);
	board[temp.x][temp.y] = piece;
}
char GameWorld::moveUp()
{
	char destination = '\0';
	Coordinate upOne;
	upOne.x = -1;
	upOne.y = 0;
	//Check in bounds
	if (playerPosition.x == 0)
		return '\0';
	//Overwrite P on board
	board[playerPosition.x][playerPosition.y] = ' ';
	//Update player location
	playerPosition = playerPosition + upOne;
	//Get char from space
	destination = board[playerPosition.x][playerPosition.y];
	//Write player to space
	board[playerPosition.x][playerPosition.y] = 'U';
	//Return overwritten character
	return destination;
}
char GameWorld::moveDown()
{
	char destination = '\0';
	Coordinate downOne;
	downOne.x = 1;
	downOne.y = 0;
	if (playerPosition.x == 4)
		return '\0';
	board[playerPosition.x][playerPosition.y] = ' ';
	playerPosition = playerPosition + downOne;
	destination = board[playerPosition.x][playerPosition.y];
	board[playerPosition.x][playerPosition.y] = 'U';
	return destination;
}
char GameWorld::moveRight()
{
	char destination = '\0';
	Coordinate rightOne;
	rightOne.x = 0;
	rightOne.y = 1;
	if (playerPosition.y == 4)
		return '\0';
	board[playerPosition.x][playerPosition.y] = ' ';
	playerPosition = playerPosition + rightOne;
	destination = board[playerPosition.x][playerPosition.y];
	board[playerPosition.x][playerPosition.y] = 'U';
	return destination;
}
char GameWorld::moveLeft()
{
	char destination = '\0';
	Coordinate leftOne;
	leftOne.x = 0;
	leftOne.y = -1;
	if (playerPosition.y == 0)
		return '\0';
	board[playerPosition.x][playerPosition.y] = ' ';
	playerPosition = playerPosition + leftOne;
	destination = board[playerPosition.x][playerPosition.y];
	board[playerPosition.x][playerPosition.y] = 'U';
	return destination;
}
bool GameWorld::haveIWon(char destination)
{
	if (destination == 'G')
		return true;
	else
		return false;
}
bool GameWorld::amIAlive(char destination)
{
	if (destination == 'W' || destination == 'P')
		return false;
	else
		return true;
}
