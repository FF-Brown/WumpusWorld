

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

struct Coordinate {
	int x;
	int y;
};
Coordinate randPosition(void); 
ostream& operator<< (ostream& lhs, Coordinate& rhs);

class GameWorld {
private:
	char board[5][5];
	Coordinate playerPosition;
	int score;
	string name;

public:
	GameWorld(char space)	
	{
		Coordinate temp;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				board[i][j] = space;
			}
		}
		playerPosition = randPosition(); 
		board[playerPosition.x][playerPosition.y] = 'U';
		placePiece('W', space); //Wumpus
		placePiece('G', space); //Gold
		int pits = rand() % 6 + 5; //Set # of pits
		for (int i = 0; i < pits; ++i)
			placePiece('P', space); //Pit
		score = 0;
		name = "<blank>";
	}
	char getTile(int x, int y)	{ return board[x][y]; }
	Coordinate findPlayer(void)	{ return playerPosition; }
	string getName()
	{
		return name;
	}
	void setName(string newName)
	{
		name = newName;
	}
	int getScore()
	{
		return score;
	}
	void setScore(int newScore)
	{
		score = newScore;
	}
	void incrementScore()
	{
		score += 5;
	}
	void viewPenalty()
	{
		score -= 2;
	}
	void cheatPenalty()
	{
		score -= 5;
	}
	void displayEntireWorld() 
	{
		cout << "     |     |     |     |     |\n";
		cout << "  ";
		for(int i = 0; i < 5; ++i) cout << board[0][i] << "  |  ";
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
	void displayVisibleWorld()
	{
		cout << "     |     |     |     |     |\n";
		cout << "  ";
		for (int i = 0; i < 5; ++i) {
			if(playerPosition.x <= 1 && (playerPosition.y - i <= 1 && playerPosition.y - i >= -1))
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
				if(playerPosition.x - j <= 1 && playerPosition.x - j >= -1 && playerPosition.y - i <= 1 && playerPosition.y - i >= -1)
					cout << board[j][i] << "  |  ";
				else
					cout << ' ' << "  |  ";
			}
			cout << endl;
		}

		cout << "     |     |     |     |     |\n";

	}
	void placePiece(char piece, char def)
	{
		Coordinate temp;
		do {
			temp = randPosition();
		} while (board[temp.x][temp.y] != def);
		board[temp.x][temp.y] = piece;
	}
	char moveUp();
	char moveDown();
	char moveRight();
	char moveLeft();
	bool haveIWon(char destination);
	bool amIAlive(char destination);
};

Coordinate operator+ (const Coordinate& lhs, const Coordinate& rhs);
Coordinate operator- (const Coordinate& lhs, const Coordinate& rhs);
void displayMenu();
void displayControls();
void playGame();
char playerMove(GameWorld &world, char command);
bool didIMove(char input);
void resetGame(GameWorld& world);
void newGame(GameWorld& world);
void setName(GameWorld&);	
ostream& operator<< (ostream& output, GameWorld& world);
void saveData(GameWorld& world);