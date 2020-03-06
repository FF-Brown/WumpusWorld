

#include "pa4.h"

Coordinate randPosition(void) 
{
	Coordinate temp;
		temp.x = rand() % 5;
		temp.y = rand() % 5;
	return temp;
}
Coordinate operator+ (const Coordinate& lhs, const Coordinate& rhs) 
{
	Coordinate temp;
	temp.x = lhs.x + rhs.x;
	temp.y = lhs.y + rhs.y;
	return temp;
}
Coordinate operator- (const Coordinate& lhs, const Coordinate& rhs)
{
	Coordinate temp;
	temp.x = lhs.x - rhs.x;
	temp.y = lhs.y - rhs.y;
	return temp;
}
ostream& operator<< (ostream& lhs, Coordinate& rhs)
{
	lhs << "(" << rhs.x << "," << rhs.y << ")";
	return lhs; 
}
void displayMenu()
{
	int option = 0;
	do	{
		system("cls"); 
		cout << "Wumpus World\nMain Menu\n";
		cout << "1. Play Game\n";
		cout << "2. Controls\n";
		cout << "3. Exit\n";
		cin >> option;
		if (option == 1)
			playGame();
		if (option == 2)
			displayControls();
		else if (option == 3) {
			cout << "Goodbye!\n";
		}
	} while (option != 3);
}
void displayControls()
{
	cout << "The game is played on a 5x5 board. The user must navigate around pits and the wumpus\nto find the gold in the cave.\nMovement is achieved with the right-handed IJKL or the more typical WASD.\nUser must hit <enter> after every movement.\nV will show the visible part of the cave.\nC shows the entire cave.\nR will reset the board without resetting the player.\nN will reset the board and player data.\nQ quits the game.\n\n";
	cout << "5 points are awarded for every step taken successfully.\n2 points are subtracted each time the player chooses to view the visible part of the cave.\n5 points are subtracted every time the player views the entire cave.\nGood luck!\n\n";
}
void playGame()
{
	char input = '\0', move = '\0';
	bool result = false;
	GameWorld world;

	setName(world); //Set player name if necessary
	world.displayVisibleWorld();
	do {
		cout << "Current score: " << world.getScore() << endl;
		cout << "Enter command: ";
		cin >> input;
		move = playerMove(world, input); 
		if (didIMove(input)) { //If character moved this turn
			result = world.amIAlive(move);
			if (!result) { //Not alive
				cout << "You died!\n";
				input = 'q';
				system("pause");
				saveData(world);
			}
			else
				world.incrementScore();
			result = world.haveIWon(move);
			if (result) { //'Won' the game
				cout << "You found the gold!\n";
				input = 'q';
				system("pause");
				saveData(world);
			}
		}
	} while (input != 'q' && input != 'Q');
	cout << "Saving data...\n";
}
char playerMove(GameWorld &world, char command)
{
	char move = '\0';
	if (command == 'i' || command == 'I' || command == 'w' || command == 'W')
		move = world.moveUp();
	else if (command == 'k' || command == 'K' || command == 's' || command == 'S')
		move = world.moveDown();
	else if (command == 'l' || command == 'L' || command == 'd' || command == 'D')
		move = world.moveRight();
	else if (command == 'j' || command == 'J' || command == 'a' || command == 'A')
		move = world.moveLeft();
	else if (command == 'v' || command == 'V') {
		system("cls");
		world.displayVisibleWorld();
		world.viewPenalty();
	}
	else if (command == 'c' || command == 'C') {
		system("cls");
		world.displayEntireWorld();
		world.cheatPenalty();
	}
	else if (command == 'r' || command == 'R') {
		resetGame(world);
		cout << "Board reset\n";
		world.displayVisibleWorld();
	}
	else if (command == 'n' || command == 'N') {
		newGame(world);
		cout << "New game.\n";
		world.displayVisibleWorld();
	}
	else if (command == 'q' || command == 'Q')
		cout << "Exiting...\n";
	else
		cout << "Invalid input.\n";
	return move;
}
bool didIMove(char input)
{
	char moveControls[] = "ijklwasdIJKLWASD";
	for (int i = 0; i < 17; ++i) { //Prefer to use strlen()
		if (input == moveControls[i])
			return true;
	}
	return false;
}
void resetGame(GameWorld& world)
{
	int score = world.getScore();
	string name = world.getName();
	world = GameWorld::GameWorld();
	world.setScore(score);
	world.setName(name);
}
void newGame(GameWorld& world)
{
	world = GameWorld::GameWorld();
}
void setName(GameWorld& world)
{
	string name;
	if (world.getName() == "<blank>") {
		cout << "Enter your name: ";
		cin >> name;
		world.setName(name);
	}
}
ostream& operator<< (ostream& output, GameWorld& world)
{
	output << world.getName() << ": " << world.getScore() << " points\n";
	return output;
}
void saveData(GameWorld& world)
{
	fstream outfile;
	outfile.open("GameScores.txt", fstream::app); 
	outfile << world;
}