// SFML Template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <time.h>
using namespace std;
sf::Texture tile_hidden;
sf::Texture mine;
sf::Texture tile_revealed;
sf::Texture flag;
sf::Texture debug;
sf::Texture face_happy;
sf::Texture face_lose;
sf::Texture face_win;
sf::Texture number_1;
sf::Texture number_2;
sf::Texture number_3;
sf::Texture number_4;
sf::Texture number_5;
sf::Texture number_6;
sf::Texture number_7;
sf::Texture number_8;
sf::Texture test_1;
sf::Texture test_2;
sf::Texture zero;
sf::Texture one;
sf::Texture two;
sf::Texture three;
sf::Texture four;
sf::Texture five;
sf::Texture six;
sf::Texture seven;
sf::Texture eight;
sf::Texture nine;


struct Tile {
	sf::Sprite sprite;
	sf::Sprite sprite2;
	sf::Sprite sprite3;
	sf::Texture texture;
	bool isRevealed;
	int xCoordinate;
	int yCoordinate;
	int xCenter;
	int yCenter;
	float distance;
	bool isBomb;
	int adjacentBombs;
	int numBombs = 0;
	int number;
	bool isFlag = false;
	bool sprite3Set = false;
};

vector<vector<Tile>> tiles;
int AdjacentBombs(int xCoord, int yCoord) {
	int masterCounter = 0;
	if (xCoord == 15 && yCoord == 0) {
		if (tiles[15][1].isBomb) {
			masterCounter++;
		}
		if (tiles[14][1].isBomb) {
			masterCounter++;
		}
		if (tiles[14][0].isBomb) {
			masterCounter++;
		}
	}
	//top row excluding corners
	if (xCoord == 0) {
		//top left corner
		if (xCoord == 0 && yCoord == 0) {
			if (tiles[0][1].isBomb) {
				masterCounter++;
			}
			if (tiles[1][0].isBomb) {
				masterCounter++;
			}
			if (tiles[1][1].isBomb) {
				masterCounter++;
			}
		}
		//top right corner
		else if (xCoord == 0 && yCoord == 24) {
			if (tiles[0][23].isBomb) {
				masterCounter++;
			}
			if (tiles[1][24].isBomb) {
				masterCounter++;
			}
			if (tiles[1][23].isBomb) {
				masterCounter++;
			}
		}
		else {
			if (tiles[0][yCoord - 1].isBomb) {
				masterCounter++;
			}
			if (tiles[0][yCoord + 1].isBomb) {
				masterCounter++;
			}
			if (tiles[1][yCoord].isBomb) {
				masterCounter++;
			}
			if (tiles[1][yCoord + 1].isBomb) {
				masterCounter++;
			}
			if (tiles[1][yCoord - 1].isBomb) {
				masterCounter++;
			}
		}
	}
	//bottom row excluding corners
	else if (xCoord == 15) {
		//bottom right corner
		if (yCoord == 24) {
			if (tiles[15][23].isBomb) {
				masterCounter++;
			}
			if (tiles[14][24].isBomb) {
				masterCounter++;
			}
			if (tiles[14][23].isBomb) {
				masterCounter++;
			}
		}
		else if (yCoord == 0) {   // =mistake?
			if (tiles[15][23].isBomb) {
				masterCounter++;
			}
			if (tiles[14][24].isBomb) {
				masterCounter++;
			}
			if (tiles[14][23].isBomb) {
				masterCounter++;
			}
		}

		else {
			if (tiles[15][yCoord - 1].isBomb) {
				masterCounter++;
			}
			if (tiles[15][yCoord + 1].isBomb) {
				masterCounter++;
			}
			if (tiles[14][yCoord].isBomb) {
				masterCounter++;
			}
			if (tiles[14][yCoord + 1].isBomb) {
				masterCounter++;
			}
			if (tiles[14][yCoord - 1].isBomb) {
				masterCounter++;
			}
		}
	}
	//left column excluding corners
	else if (yCoord == 0 && xCoord != 0 && xCoord != 15) {
		if (tiles[xCoord + 1][0].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord - 1][0].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord - 1][1].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord + 1][1].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord][1].isBomb) {
			masterCounter++;
		}
	}
	//right column excluding corners
	else if (yCoord == 24 && xCoord != 0 && xCoord != 15) {
		if (tiles[xCoord + 1][24].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord - 1][24].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord - 1][23].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord + 1][23].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord][23].isBomb) {
			masterCounter++;

		}
	}
	else {
		if (tiles[xCoord][yCoord + 1].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord][yCoord - 1].isBomb) {
			masterCounter++;

		}
		if (tiles[xCoord + 1][yCoord].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord - 1][yCoord].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord - 1][yCoord - 1].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord + 1][yCoord + 1].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord + 1][yCoord - 1].isBomb) {
			masterCounter++;
		}
		if (tiles[xCoord - 1][yCoord + 1].isBomb) {
			masterCounter++;
		}


	}
	//cout << masterCounter;

	return masterCounter;

}
float Distance(Tile tile, float xCoord, float yCoord) {

	float a = sqrt(pow(tile.xCenter - xCoord, 2) + pow(tile.yCenter - yCoord, 2));
	//cout << a << "\n\n";
	return 	a;

}
void revealMore(int xCoor, int yCoor, int adjBombs) {
	int minx, miny, maxx, maxy;

	minx = (xCoor <= 0 ? 0 : xCoor - 1);
	miny = (yCoor <= 0 ? 0 : yCoor - 1);
	maxx = (xCoor >= 14 ? 16 : xCoor + 2);
	maxy = (yCoor >= 23 ? 25 : yCoor + 2);

	if (tiles[xCoor][yCoor].isBomb == false) {
		for (int x = minx; x < maxx; x++) {
			for (int y = miny; y < maxy; y++) {
				if (tiles[x][y].isBomb == false && tiles[x][y].isRevealed == false && tiles[x][y].isFlag == false && adjBombs == 0) {
					tiles[x][y].isRevealed = true;
					tiles[x][y].adjacentBombs = AdjacentBombs(x, y);
					tiles[x][y].sprite.setTexture(tile_revealed);
					if (tiles[x][y].adjacentBombs == 1) {
						tiles[x][y].sprite3.setTexture(number_1);
						tiles[x][y].sprite3Set = true;
					}
					else if (tiles[x][y].adjacentBombs == 2) {
						tiles[x][y].sprite3.setTexture(number_2);
						tiles[x][y].sprite3Set = true;
					}
					else if (tiles[x][y].adjacentBombs == 3) {
						tiles[x][y].sprite3.setTexture(number_3);
						tiles[x][y].sprite3Set = true;
					}
					else if (tiles[x][y].adjacentBombs == 4) {
						tiles[x][y].sprite3.setTexture(number_4);
						tiles[x][y].sprite3Set = true;
					}
					else if (tiles[x][y].adjacentBombs == 5) {
						tiles[x][y].sprite3.setTexture(number_5);
						tiles[x][y].sprite3Set = true;
					}
					else if (tiles[x][y].adjacentBombs == 6) {
						tiles[x][y].sprite3.setTexture(number_6);
						tiles[x][y].sprite3Set = true;
					}
					else if (tiles[x][y].adjacentBombs == 7) {
						tiles[x][y].sprite3.setTexture(number_7);
						tiles[x][y].sprite3Set = true;
					}
					else if (tiles[x][y].adjacentBombs == 8) {
						tiles[x][y].sprite3.setTexture(number_8);
						tiles[x][y].sprite3Set = true;
					}

					if (tiles[x][y].sprite3Set == false) {
						revealMore(x, y, tiles[x][y].adjacentBombs);
					}
				}
			}
		}
	}
}
void Clicked(float xCoord, float yCoord, bool &endGame) {
	float max = 10000;
	int maxX, maxY;
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 25; y++) {
			tiles[x][y].distance = Distance(tiles[x][y], xCoord, yCoord);
			//cout << tiles[x][y].distance << "\n\n";
		}
	}
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 25; y++) {

			if (tiles[x][y].distance < max) {
				max = tiles[x][y].distance;
				maxX = x;
				maxY = y;
			}
		}
	}

	if (tiles[maxX][maxY].isFlag == false) {
		//cout << "Coordinates: " << maxX << ", " << maxY << endl;
		tiles[maxX][maxY].isRevealed = true;
		tiles[maxX][maxY].adjacentBombs = AdjacentBombs(maxX, maxY);
		//cout << "There are " << tiles[maxX][maxY].adjacentBombs << " nearby.";

		if (tiles[maxX][maxY].isBomb) {
			tiles[maxX][maxY].sprite.setTexture(mine);
			endGame = true; 
		}
		else {
			tiles[maxX][maxY].sprite.setTexture(tile_revealed);
			if (tiles[maxX][maxY].adjacentBombs == 1) {
				tiles[maxX][maxY].sprite3.setTexture(number_1);
				tiles[maxX][maxY].sprite3Set = true;
			}
			else if (tiles[maxX][maxY].adjacentBombs == 2) {
				tiles[maxX][maxY].sprite3.setTexture(number_2);
				tiles[maxX][maxY].sprite3Set = true;
			}
			else if (tiles[maxX][maxY].adjacentBombs == 3) {
				tiles[maxX][maxY].sprite3.setTexture(number_3);
				tiles[maxX][maxY].sprite3Set = true;
			}
			else if (tiles[maxX][maxY].adjacentBombs == 4) {
				tiles[maxX][maxY].sprite3.setTexture(number_4);
				tiles[maxX][maxY].sprite3Set = true;
			}
			else if (tiles[maxX][maxY].adjacentBombs == 5) {
				tiles[maxX][maxY].sprite3.setTexture(number_5);
				tiles[maxX][maxY].sprite3Set = true;
			}
			else if (tiles[maxX][maxY].adjacentBombs == 6) {
				tiles[maxX][maxY].sprite3.setTexture(number_6);
				tiles[maxX][maxY].sprite3Set = true;
			}
			else if (tiles[maxX][maxY].adjacentBombs == 7) {
				tiles[maxX][maxY].sprite3.setTexture(number_7);
				tiles[maxX][maxY].sprite3Set = true;
			}
			else if (tiles[maxX][maxY].adjacentBombs == 8) {
				tiles[maxX][maxY].sprite3.setTexture(number_8);
				tiles[maxX][maxY].sprite3Set = true;
			}
		}
		
		revealMore(maxX, maxY, tiles[maxX][maxY].adjacentBombs);

	}
}
void FlagClick(float xCoord, float yCoord, int &flags) {
	float max = 10000;
	int maxX, maxY;
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 25; y++) {
			tiles[x][y].distance = Distance(tiles[x][y], xCoord, yCoord);
			//cout << tiles[x][y].distance << "\n\n";
		}
	}
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 25; y++) {

			if (tiles[x][y].distance < max) {
				max = tiles[x][y].distance;
				maxX = x;
				maxY = y;
			}
		}
	}

	if (tiles[maxX][maxY].isFlag == false && tiles[maxX][maxY].isRevealed == false && flags > 0) {
		//cout << "Coordinates: " << maxX << ", " << maxY << endl;
		tiles[maxX][maxY].sprite2.setTexture(flag);
		tiles[maxX][maxY].isFlag = true;
		flags--;
	}
	else if (tiles[maxX][maxY].isFlag == true) {
		//cout << "Coordinates: " << maxX << ", " << maxY << endl;
		tiles[maxX][maxY].isFlag = false;
		flags++;
	}
}
void Reset(bool &showMines, bool &debugClick, bool &endGame, int &flagCount, int &tilesRevealed) {
	showMines = false;
	debugClick = false;
	endGame = false;
	flagCount = 50;
	tilesRevealed = 0;
	int xCoord, yCoord;
	yCoord = 0;
	for (int x = 0; x < 16; x++) {
		xCoord = 0;
		int counterC = 0;
		vector<Tile> tempVector;
		for (int y = 0; y < 25; y++) {
			counterC++;
			Tile tempTile;
			tempTile.isRevealed = false;
			tempTile.xCoordinate = xCoord;
			tempTile.yCoordinate = yCoord;
			tempTile.xCenter = tempTile.xCoordinate + 16;
			tempTile.yCenter = tempTile.yCoordinate + 16;
			tempTile.isBomb = false;
			tempTile.number = counterC;


			tempTile.sprite.setTexture(tile_hidden);

			xCoord += 32;
			tempVector.push_back(tempTile);
		}
		tiles.push_back(tempVector);
		yCoord += 32;
	}
	int bombCounter = 0;
	srand(time(NULL));
	while (bombCounter < 50) {
		int x = rand() % 16;
		int y = rand() % 25;
		//cout << x << y << endl;


		if (tiles[x][y].isBomb == false) {
			//tiles[x][y].sprite.setTexture(mine);
			tiles[x][y].isBomb = true;
			bombCounter++;
		}
	}
}
void LoadFiles() {
	if (!tile_revealed.loadFromFile("images/tile_revealed.png", sf::IntRect(0, 0, 32, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!mine.loadFromFile("images/mine.png", sf::IntRect(0, 0, 32, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!tile_hidden.loadFromFile("images/tile_hidden.png", sf::IntRect(0, 0, 32, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!flag.loadFromFile("images/flag.png", sf::IntRect(0, 0, 32, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!face_happy.loadFromFile("images/face_happy.png")) {
		cout << "Error revealed" << endl;
	}
	if (!debug.loadFromFile("images/debug.png")) {
		cout << "Error revealed" << endl;
	}
	if (!test_1.loadFromFile("images/test_1.png")) {
		cout << "Error revealed" << endl;
	}
	if (!test_2.loadFromFile("images/test_2.png")) {
		cout << "Error revealed" << endl;
	}
	if (!number_1.loadFromFile("images/number_1.png")) {
		cout << "Error revealed" << endl;
	}
	if (!number_2.loadFromFile("images/number_2.png")) {
		cout << "Error revealed" << endl;
	}
	if (!number_3.loadFromFile("images/number_3.png")) {
		cout << "Error revealed" << endl;
	}
	if (!number_4.loadFromFile("images/number_4.png")) {
		cout << "Error revealed" << endl;
	}
	if (!number_5.loadFromFile("images/number_5.png")) {
		cout << "Error revealed" << endl;
	}
	if (!number_6.loadFromFile("images/number_6.png")) {
		cout << "Error revealed" << endl;
	}
	if (!number_7.loadFromFile("images/number_7.png")) {
		cout << "Error revealed" << endl;
	}
	if (!number_8.loadFromFile("images/number_8.png")) {
		cout << "Error revealed" << endl;
	}
	if (!face_lose.loadFromFile("images/face_lose.png")) {
		cout << "Error revealed" << endl;
	}
	if (!face_win.loadFromFile("images/face_win.png")) {
		cout << "Error revealed" << endl;
	}
	if (!zero.loadFromFile("images/digits.png", sf::IntRect(0, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!one.loadFromFile("images/digits.png", sf::IntRect(21, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!two.loadFromFile("images/digits.png", sf::IntRect(42, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!three.loadFromFile("images/digits.png", sf::IntRect(63, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!four.loadFromFile("images/digits.png", sf::IntRect(84, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!five.loadFromFile("images/digits.png", sf::IntRect(105, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!six.loadFromFile("images/digits.png", sf::IntRect(126, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!seven.loadFromFile("images/digits.png", sf::IntRect(147, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!eight.loadFromFile("images/digits.png", sf::IntRect(168, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
	if (!nine.loadFromFile("images/digits.png", sf::IntRect(189, 0, 21, 32))) {
		cout << "Error revealed" << endl;
	}
}
void MineCounter(int flags, sf::RenderWindow &win, sf::Sprite &a0, sf::Sprite &a1, sf::Sprite &a2, sf::Sprite &a3, sf::Sprite &a4, sf::Sprite &a5, sf::Sprite &a6, sf::Sprite &a7, sf::Sprite &a8, sf::Sprite &a9) {
	if (flags == 50) {
		win.draw(a5);
		a5.setPosition(sf::Vector2f(21, 512));
		win.draw(a0);
		a0.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 49) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a9);
		a9.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 48) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a8);
		a8.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 47) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a7);
		a7.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 46) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a6);
		a6.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 45) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a5);
		a5.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 44) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a4);
		a4.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 43) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a3);
		a3.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 42) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a2);
		a2.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 41) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a1);
		a1.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 40) {
		win.draw(a4);
		a4.setPosition(sf::Vector2f(21, 512));
		win.draw(a0);
		a0.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 39) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a9);
		a9.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 38) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a8);
		a8.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 37) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a7);
		a7.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 36) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a6);
		a6.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 35) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a5);
		a5.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 34) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a4);
		a4.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 33) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a3);
		a3.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 32) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a2);
		a2.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 31) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a1);
		a1.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 30) {
		win.draw(a3);
		a3.setPosition(sf::Vector2f(21, 512));
		win.draw(a0);
		a0.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 29) {
		win.draw(a2);
		a2.setPosition(sf::Vector2f(21, 512));
		win.draw(a9);
		a9.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 28) {
		win.draw(a2);
		a2.setPosition(sf::Vector2f(21, 512));
		win.draw(a8);
		a8.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 27) {
		win.draw(a2);
		a2.setPosition(sf::Vector2f(21, 512));
		win.draw(a7);
		a7.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 26) {
		win.draw(a2);
		a2.setPosition(sf::Vector2f(21, 512));
		win.draw(a6);
		a6.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 25) {
	win.draw(a2);
	a2.setPosition(sf::Vector2f(21, 512));
	win.draw(a5);
	a5.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 24) {
	win.draw(a2);
	a2.setPosition(sf::Vector2f(21, 512));
	win.draw(a4);
	a4.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 23) {
	win.draw(a2);
	a2.setPosition(sf::Vector2f(21, 512));
	win.draw(a3);
	a3.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 22) {
	win.draw(a2);
	a2.setPosition(sf::Vector2f(21, 512));
	win.draw(a2);
	a2.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 21) {
	win.draw(a2);
	a2.setPosition(sf::Vector2f(21, 512));
	win.draw(a1);
	a1.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 20) {
	win.draw(a2);
	a2.setPosition(sf::Vector2f(21, 512));
	win.draw(a0);
	a0.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 19) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a9);
	a9.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 18) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a8);
	a8.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 17) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a7);
	a7.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 16) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a6);
	a6.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 15) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a5);
	a5.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 14) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a4);
	a4.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 13) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a3);
	a3.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 12) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a2);
	a2.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 11) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a1);
	a1.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 10) {
	win.draw(a1);
	a1.setPosition(sf::Vector2f(21, 512));
	win.draw(a0);
	a0.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 9) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a9);
	a9.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 8) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a8);
	a8.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 7) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a7);
	a7.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 6) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a6);
	a6.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 5) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a5);
	a5.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 4) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a4);
	a4.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 3) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a3);
	a3.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 2) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a2);
	a2.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 1) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a1);
	a1.setPosition(sf::Vector2f(42, 512));
	}
	else if (flags == 0) {
	win.draw(a0);
	a0.setPosition(sf::Vector2f(21, 512));
	win.draw(a0);
	a0.setPosition(sf::Vector2f(42, 512));
	}
}
void Test1(bool &showMines, bool &debugClick, bool &endGame, int &flagCount, int &tilesRevealed) {
	showMines = false;
	debugClick = false;
	endGame = false;
	flagCount = 50;
	tilesRevealed = 0;
	fstream file;
	file.open("boards/testboard.brd");
	while (file.is_open()) {
		string line;
		vector<string> a;
		while (getline(file, line, '\n')) {
			a.push_back(line);
		}
		file.close();

		int xCoord, yCoord;
		yCoord = 0;
		for (int x = 0; x < 16; x++) {
			xCoord = 0;
			int counterC = 0;
			vector<Tile> tempVector;
			string b = a.at(x);
			for (int y = 0; y < 25; y++) {
				counterC++;
				Tile tempTile;
				tempTile.isRevealed = false;
				tempTile.xCoordinate = xCoord;
				tempTile.yCoordinate = yCoord;
				tempTile.xCenter = tempTile.xCoordinate + 16;
				tempTile.yCenter = tempTile.yCoordinate + 16;
				
				tempTile.number = counterC;
				
				if (b[y] == '1') {
					tempTile.sprite.setTexture(tile_hidden);
					tempTile.isBomb = true;
				}
				else if (b[y] == '0') {
					tempTile.sprite.setTexture(tile_hidden);
					tempTile.isBomb = false;
				}

				xCoord += 32;
				tempVector.push_back(tempTile);
			}
			tiles.push_back(tempVector);
			yCoord += 32;
		}
	}
}
void Test2(bool &showMines, bool &debugClick, bool &endGame, int &flagCount, int &tilesRevealed) {
	showMines = false;
	debugClick = false;
	endGame = false;
	flagCount = 50;
	tilesRevealed = 0;
	fstream file;
	file.open("boards/testboard2.brd");
	while (file.is_open()) {
		string line;
		vector<string> a;
		while (getline(file, line, '\n')) {
			a.push_back(line);
		}
		file.close();

		int xCoord, yCoord;
		yCoord = 0;
		for (int x = 0; x < 16; x++) {
			xCoord = 0;
			int counterC = 0;
			vector<Tile> tempVector;
			string b = a.at(x);
			for (int y = 0; y < 25; y++) {
				counterC++;
				Tile tempTile;
				tempTile.isRevealed = false;
				tempTile.xCoordinate = xCoord;
				tempTile.yCoordinate = yCoord;
				tempTile.xCenter = tempTile.xCoordinate + 16;
				tempTile.yCenter = tempTile.yCoordinate + 16;
				tempTile.number = counterC;

				if (b[y] == '1') {
					tempTile.sprite.setTexture(tile_hidden);
					tempTile.isBomb = true;
				}
				else if (b[y] == '0') {
					tempTile.sprite.setTexture(tile_hidden);
					tempTile.isBomb = false;
				}

				xCoord += 32;
				tempVector.push_back(tempTile);
			}
			tiles.push_back(tempVector);
			yCoord += 32;
		}
	}
}


int main()
{
	LoadFiles();

	sf::Sprite background(tile_hidden);
	sf::Sprite happyFace(face_happy);
	sf::Sprite Victory(face_win);
	sf::Sprite Sad(face_lose);
	sf::Sprite Debug(debug);
	sf::Sprite test1(test_1);
	sf::Sprite test2(test_2);
	sf::Sprite Zero(zero);
	sf::Sprite One(one);
	sf::Sprite Two(two);
	sf::Sprite Three(three);
	sf::Sprite Four(four);
	sf::Sprite Five(five);
	sf::Sprite Six(six);
	sf::Sprite Seven(seven);
	sf::Sprite Eight(eight);
	sf::Sprite Nine(nine);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

	bool showMines = false;
	bool debugClick = false;
	bool endGame = false;
	int flagCount = 50;
	int tilesRevealed = 0;
	int xCoord, yCoord;
	yCoord = 0;
	for (int x = 0; x < 16; x++) {
		xCoord = 0;
		int counterC = 0;
		vector<Tile> tempVector;
		for (int y = 0; y < 25; y++) {
			counterC++;
			Tile tempTile;
			tempTile.isRevealed = false;
			tempTile.xCoordinate = xCoord;
			tempTile.yCoordinate = yCoord;
			tempTile.xCenter = tempTile.xCoordinate + 16;
			tempTile.yCenter = tempTile.yCoordinate + 16;
			tempTile.isBomb = false;
			tempTile.number = counterC;


			tempTile.sprite.setTexture(tile_hidden);

			xCoord += 32;
			tempVector.push_back(tempTile);
		}
		tiles.push_back(tempVector);
		yCoord += 32;
	}
	int bombCounter = 0;
	srand(time(NULL));
	while (bombCounter < 50) {
		int x = rand() % 16;
		int y = rand() % 25;
		//cout << x << y << endl;


		if (tiles[x][y].isBomb == false) {
			tiles[x][y].isBomb = true;
			bombCounter++;
		}
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();


			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					float xClick = event.mouseButton.x;
					float yClick = event.mouseButton.y;
					if (endGame) {
						if (xClick > 368 && xClick < 432 && yClick > 512 & yClick < 576) {
							tiles.clear();
							Reset(showMines, debugClick, endGame, flagCount, tilesRevealed);
							cout << "Reset" << endl;
						}
					}
					else if (yClick < 16 * 32) {
						Clicked(xClick, yClick, endGame);
					}
					else if (xClick > 496 && xClick < 560 && yClick > 512 && yClick < 576) {
						if (showMines == false)
							showMines = true;
						else if (showMines == true)
							showMines = false;
						debugClick = true;
					}
					else if (xClick > 368 && xClick < 432 && yClick > 512 & yClick < 576) {
						tiles.clear();
						Reset(showMines, debugClick, endGame, flagCount, tilesRevealed);
						cout << "Reset" << endl;
					}
					//test file 1
					else if (xClick > 560 && xClick < 624 && yClick > 512 & yClick < 576) {
						tiles.clear();
						Test1(showMines, debugClick, endGame, flagCount, tilesRevealed);
						cout << "Test1" << endl;
					}
					//test file 2
					else if (xClick > 624 && xClick < 688 && yClick > 512 & yClick < 576) {
						tiles.clear();
						Test2(showMines, debugClick, endGame, flagCount, tilesRevealed);
						cout << "Test2" << endl;
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right && endGame == false) {
					float xClick = event.mouseButton.x;
					float yClick = event.mouseButton.y;
					if (yClick < 16 * 32) {
						FlagClick(xClick, yClick, flagCount);
					}
				}
			}
		}
		tilesRevealed = 0;
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 25; y++) {

				if (showMines && debugClick) {
					if (tiles[x][y].isBomb)
						tiles[x][y].sprite.setTexture(mine);
				}
				else if (showMines == false && debugClick) {
					if (tiles[x][y].isBomb)
						tiles[x][y].sprite.setTexture(tile_hidden);
				}

				if (endGame) {
					if (tiles[x][y].isBomb && tiles[x][y].isFlag == false)
						tiles[x][y].sprite.setTexture(mine);
				}

				//window.draw(background);
				window.draw(tiles[x][y].sprite);
				tiles[x][y].sprite.setPosition(sf::Vector2f(tiles[x][y].xCoordinate, tiles[x][y].yCoordinate)); // absolute position
				window.draw(tiles[x][y].sprite3);
				tiles[x][y].sprite3.setPosition(sf::Vector2f(tiles[x][y].xCoordinate, tiles[x][y].yCoordinate));

				if (tiles[x][y].isFlag) {
					window.draw(tiles[x][y].sprite2);
					tiles[x][y].sprite2.setPosition(sf::Vector2f(tiles[x][y].xCoordinate, tiles[x][y].yCoordinate));
				}

				if (tiles[x][y].isRevealed)
					tilesRevealed++;
			}
		}

		debugClick = false;
		window.draw(happyFace);
		happyFace.setPosition(sf::Vector2f(368, 512));
		window.draw(Debug);
		Debug.setPosition(sf::Vector2f(496, 512));
		window.draw(test1);
		test1.setPosition(sf::Vector2f(560, 512));
		window.draw(test2);
		test2.setPosition(sf::Vector2f(624, 512));
		window.draw(Zero);
		Zero.setPosition(sf::Vector2f(0, 512));
		MineCounter(flagCount, window, Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine);

		if (tilesRevealed == 350 && flagCount == 0) {
			window.draw(Victory);
			Victory.setPosition(sf::Vector2f(368, 512));
		}

		if (endGame) {
			window.draw(Sad);
			Sad.setPosition(sf::Vector2f(368, 512));
		}

		window.display();

		//cout << tilesRevealed << endl;
		//cout << flagCount << endl;

		if (tilesRevealed == 350 && flagCount == 0) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					float xClick = event.mouseButton.x;
					float yClick = event.mouseButton.y;
					if (xClick > 368 && xClick < 432 && yClick > 512 & yClick < 576) {
						tiles.clear();
						Reset(showMines, debugClick, endGame, flagCount, tilesRevealed);
						cout << "Reset" << endl;
					}
				}
			}
		}
	}
}