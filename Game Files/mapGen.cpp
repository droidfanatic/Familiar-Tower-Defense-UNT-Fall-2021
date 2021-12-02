 #include "mapGen.h"
#include <iostream>
#include <random>
#include <vector>
#include <time.h>

using namespace std;

//constructor
mapGen::mapGen() {
	seed = time(NULL);
	srand(seed);
	
	tileMap = new char* [9];

	for (int r = 0; r < 9; r++) {
		map.push_back(vector<bool>());
		tileMap[r] = new char[16];
		for (int c = 0; c < 16; c++) {
			map[r].push_back(false);
			terrainNum = (float)rand() / (float)RAND_MAX;
			if (terrainNum >= 0 && terrainNum <= 0.3) {
				tileMap[r][c] = 'Y'; //TowerFloorTile
			}
			else if (terrainNum >= 0.7 && terrainNum <= 1) {
				tileMap[r][c] = 'Z'; //TowerFloorTile
			}
			else {
				tileMap[r][c] = 'T'; //TowerFloorTile
			}
		}
	}
	forceRestart = 0;
	tileColor = rand() % 4;
	startPoint = rand() % 7 + 1;
	startPair.first = startPoint;
	startPair.second = 0;
	posPair = startPair;
	posPair.second = 1;
	pathVec.push_back(startPair);
	pathVec.push_back(posPair);
	directions.push_back('r');
	directions.push_back('r');

	map[startPair.first][startPair.second] = true;
	tileMap[startPair.first][startPair.second] = 'P'; //sets path tile

	map[posPair.first][posPair.second] = true;
	tileMap[posPair.first][posPair.second] = 'P'; //sets path tile

	badDirectionPair = startPair;
}

//setters
void mapGen::createBlankMap() {
	pathVec.clear();
	directions.clear();

	tileMap = new char* [9];

	for (int r = 0; r < 9; r++) {
		tileMap[r] = new char[16];
		for (int c = 0; c < 16; c++) {
			map[r][c] = false;
			tileMap[r][c] = ' '; //BlankTile
		}
	}
}

void mapGen::createNewMap() {
	pathVec.clear();
	directions.clear();

	seed = time(NULL);
	srand(seed);

	tileMap = new char* [9];

	for (int r = 0; r < 9; r++) {
		tileMap[r] = new char[16];
		for (int c = 0; c < 16; c++) {
			map[r][c] = false;
			terrainNum = (float)rand() / (float)RAND_MAX;
			if (terrainNum >= 0 && terrainNum <= 0.3) {
				tileMap[r][c] = 'Y'; //TowerFloorTile
			}
			else if (terrainNum >= 0.7 && terrainNum <= 1) {
				tileMap[r][c] = 'Z'; //TowerFloorTile
			}
			else {
				tileMap[r][c] = 'T'; //TowerFloorTile
			}
		}
	}
	forceRestart = 0;
	tileColor = rand() % 4;
	startPoint = rand() % 7 + 1;
	startPair.first = startPoint;
	startPair.second = 0;
	posPair = startPair;
	posPair.second = 1;
	pathVec.push_back(startPair);
	pathVec.push_back(posPair);
	directions.push_back('r');
	directions.push_back('r');

	map[startPair.first][startPair.second] = true;
	tileMap[startPair.first][startPair.second] = 'P'; //sets path tile

	map[posPair.first][posPair.second] = true;
	tileMap[posPair.first][posPair.second] = 'P'; //sets path tile

	badDirectionPair = startPair;

	while (posPair.second != 15) { //(index != 20) {
		possiblePathVec = getPossiblePath(map, posPair, directions.back(), badDirectionPair);
		if (possiblePathVec.size() == 0) {
			//cout << "No possible moves, return to previous location and try again\n";
			//cout << "RESTART\n";
			if (forceRestart == 25) {
				forceRestart = 0;
				tileColor = rand() % 4;
				startPoint = rand() % 7 + 1;
				startPair.first = startPoint;
				startPair.second = 0;
			}

			posPair = startPair;
			badDirectionPair = startPair;
			posPair.second = 1;

			pathVec.clear();
			directions.clear();
			pathVec.push_back(startPair);
			pathVec.push_back(posPair);
			directions.push_back('r');
			directions.push_back('r');

			tileMap = new char* [9];

			for (int r = 0; r < 9; r++) {
				tileMap[r] = new char[16];
				for (int c = 0; c < 16; c++) {
					map[r][c] = false;
					terrainNum = (float)rand() / (float)RAND_MAX;
					if (terrainNum >= 0 && terrainNum <= 0.3) {
						tileMap[r][c] = 'Y'; //TowerFloorTile
					}
					else if (terrainNum >= 0.7 && terrainNum <= 1) {
						tileMap[r][c] = 'Z'; //TowerFloorTile
					}
					else {
						tileMap[r][c] = 'T'; //TowerFloorTile
					}
				}
			}
			map[startPair.first][startPair.second] = true;
			tileMap[startPair.first][startPair.second] = 'P'; //sets path tile

			map[posPair.first][posPair.second] = true;
			tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
		}
		else if (possiblePathVec.size() == 2) {
			//cout << "50/50 direction choice\n";
			dirChoice = rand() % possiblePathVec.size();
			if (possiblePathVec[dirChoice].second == posPair.second + 1) {
				directions.push_back('r');
			}
			else if (possiblePathVec[dirChoice].second == posPair.second - 1) {
				directions.push_back('l');
			}
			else if (possiblePathVec[dirChoice].first == posPair.first - 1) {
				directions.push_back('u');
			}
			else {
				directions.push_back('d');
			}
			posPair = possiblePathVec[dirChoice];
			map[posPair.first][posPair.second] = true;
			tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
			pathVec.push_back(posPair);
		}
		else if (possiblePathVec.size() == 3) {
			//cout << "50/25/25 direction choice, straight being heavier weight\n";
			dirChoice = rand() % (possiblePathVec.size() + 1);
			if (directions.back() == 'r') {
				if (dirChoice == 0) { //up
					posPair.first -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('u');
				}
				else if (dirChoice == 3) { //down
					posPair.first += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('d');
				}
				else { //right
					posPair.second += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('r');
				}
			}
			else if (directions.back() == 'l') {
				if (dirChoice == 0) { //up
					posPair.first -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('u');
				}
				else if (dirChoice == 3) { //down
					posPair.first += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('d');
				}
				else { //left
					posPair.second -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('l');
				}
			}
			else if (directions.back() == 'u') {
				if (dirChoice == 0) { //right
					posPair.second += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('r');
				}
				else if (dirChoice == 3) { //left
					posPair.second -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('l');
				}
				else { //up
					posPair.first -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('u');
				}
			}
			else if (directions.back() == 'd') {
				if (dirChoice == 0) { //right
					posPair.second += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('r');
				}
				else if (dirChoice == 3) { //left
					posPair.second -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('l');
				}
				else { //down
					posPair.first += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('d');
				}
			}
			else {
				cout << "direction is broken: " << directions.back() << "\n";
			}
		}
		else {
			//cout << "only 1 possible move\n";
			if (possiblePathVec[0].second == posPair.second + 1) {
				directions.push_back('r');
			}
			else if (possiblePathVec[0].second == posPair.second - 1) {
				directions.push_back('l');
			}
			else if (possiblePathVec[0].first == posPair.first - 1) {
				directions.push_back('u');
			}
			else {
				directions.push_back('d');
			}
			posPair = possiblePathVec[0];
			map[posPair.first][posPair.second] = true;
			tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
			pathVec.push_back(posPair);
		}

		if (posPair.second == 15 && pathVec.size() < 25) {
			//cout << "path too short\n";
			forceRestart = 25;
			posPair.second = 0;
			possiblePathVec.clear();
		}
	}
}

void mapGen::createNewMap(int customSeed) {
	pathVec.clear();
	directions.clear();

	seed = customSeed;
	srand(seed);

	tileMap = new char* [9];

	for (int r = 0; r < 9; r++) {
		tileMap[r] = new char[16];
		for (int c = 0; c < 16; c++) {
			map[r][c] = false;
			terrainNum = (float)rand() / (float)RAND_MAX;
			if (terrainNum >= 0 && terrainNum <= 0.3) {
				tileMap[r][c] = 'Y'; //TowerFloorTile
			}
			else if (terrainNum >= 0.7 && terrainNum <= 1) {
				tileMap[r][c] = 'Z'; //TowerFloorTile
			}
			else {
				tileMap[r][c] = 'T'; //TowerFloorTile
			}
		}
	}
	forceRestart = 0;
	tileColor = rand() % 4;
	startPoint = rand() % 7 + 1;
	startPair.first = startPoint;
	startPair.second = 0;
	posPair = startPair;
	posPair.second = 1;
	pathVec.push_back(startPair);
	pathVec.push_back(posPair);
	directions.push_back('r');
	directions.push_back('r');

	map[startPair.first][startPair.second] = true;
	tileMap[startPair.first][startPair.second] = 'P'; //sets path tile

	map[posPair.first][posPair.second] = true;
	tileMap[posPair.first][posPair.second] = 'P'; //sets path tile

	badDirectionPair = startPair;

	while (posPair.second != 15) { //(index != 20) {
		possiblePathVec = getPossiblePath(map, posPair, directions.back(), badDirectionPair);
		if (possiblePathVec.size() == 0) {
			if (forceRestart == 25) {
				forceRestart = 0;
				tileColor = rand() % 4;
				startPoint = rand() % 7 + 1;
				startPair.first = startPoint;
				startPair.second = 0;
			}

			posPair = startPair;
			badDirectionPair = startPair;
			posPair.second = 1;

			pathVec.clear();
			directions.clear();
			pathVec.push_back(startPair);
			pathVec.push_back(posPair);
			directions.push_back('r');
			directions.push_back('r');

			tileMap = new char* [9];

			for (int r = 0; r < 9; r++) {
				tileMap[r] = new char[16];
				for (int c = 0; c < 16; c++) {
					map[r][c] = false;
					terrainNum = (float)rand() / (float)RAND_MAX;
					if (terrainNum >= 0 && terrainNum <= 0.3) {
						tileMap[r][c] = 'Y'; //TowerFloorTile
					}
					else if (terrainNum >= 0.7 && terrainNum <= 1) {
						tileMap[r][c] = 'Z'; //TowerFloorTile
					}
					else {
						tileMap[r][c] = 'T'; //TowerFloorTile
					}
				}
			}

			map[startPair.first][startPair.second] = true;
			tileMap[startPair.first][startPair.second] = 'P'; //sets path tile

			map[posPair.first][posPair.second] = true;
			tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
		}
		else if (possiblePathVec.size() == 2) {
			//cout << "50/50 direction choice\n";
			dirChoice = rand() % possiblePathVec.size();
			if (possiblePathVec[dirChoice].second == posPair.second + 1) {
				directions.push_back('r');
			}
			else if (possiblePathVec[dirChoice].second == posPair.second - 1) {
				directions.push_back('l');
			}
			else if (possiblePathVec[dirChoice].first == posPair.first - 1) {
				directions.push_back('u');
			}
			else {
				directions.push_back('d');
			}
			posPair = possiblePathVec[dirChoice];
			map[posPair.first][posPair.second] = true;
			tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
			pathVec.push_back(posPair);
		}
		else if (possiblePathVec.size() == 3) {
			dirChoice = rand() % (possiblePathVec.size() + 1);
			if (directions.back() == 'r') {
				if (dirChoice == 0) { //up
					posPair.first -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('u');
				}
				else if (dirChoice == 3) { //down
					posPair.first += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('d');
				}
				else { //right
					posPair.second += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('r');
				}
			}
			else if (directions.back() == 'l') {
				if (dirChoice == 0) { //up
					posPair.first -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('u');
				}
				else if (dirChoice == 3) { //down
					posPair.first += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('d');
				}
				else { //left
					posPair.second -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('l');
				}
			}
			else if (directions.back() == 'u') {
				if (dirChoice == 0) { //right
					posPair.second += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('r');
				}
				else if (dirChoice == 3) { //left
					posPair.second -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('l');
				}
				else { //up
					posPair.first -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('u');
				}
			}
			else if (directions.back() == 'd') {
				if (dirChoice == 0) { //right
					posPair.second += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('r');
				}
				else if (dirChoice == 3) { //left
					posPair.second -= 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('l');
				}
				else { //down
					posPair.first += 1;
					map[posPair.first][posPair.second] = true;
					tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
					pathVec.push_back(posPair);
					directions.push_back('d');
				}
			}
			else {
				cout << "direction is broken: " << directions.back() << "\n";
			}
		}
		else {
			if (possiblePathVec[0].second == posPair.second + 1) {
				directions.push_back('r');
			}
			else if (possiblePathVec[0].second == posPair.second - 1) {
				directions.push_back('l');
			}
			else if (possiblePathVec[0].first == posPair.first - 1) {
				directions.push_back('u');
			}
			else {
				directions.push_back('d');
			}
			posPair = possiblePathVec[0];
			map[posPair.first][posPair.second] = true;
			tileMap[posPair.first][posPair.second] = 'P'; //sets path tile
			pathVec.push_back(posPair);
		}

		if (posPair.second == 15 && pathVec.size() < 25) {
			forceRestart = 25;
			posPair.second = 0;
			possiblePathVec.clear();
		}
	}
}

bool mapGen::checkUpBounds(vector<vector<bool>> tempMap, pair<int, int> currentPos, char direction, pair<int, int> badDirection) {
	if (currentPos.first > 1 && currentPos.second > 0) {
		if (tempMap[currentPos.first - 1][currentPos.second - 1] != true
			&& tempMap[currentPos.first - 1][currentPos.second] != true
			&& tempMap[currentPos.first - 1][currentPos.second + 1] != true
			&& tempMap[currentPos.first - 2][currentPos.second] != true
			&& currentPos.first - 1 != badDirection.first) {
			return true;
		}
	}
	else if (currentPos.first == 1 && currentPos.second > 0) {
		if (tempMap[currentPos.first - 1][currentPos.second - 1] != true
			&& tempMap[currentPos.first - 1][currentPos.second] != true
			&& tempMap[currentPos.first - 1][currentPos.second + 1] != true
			&& currentPos.first - 1 != badDirection.first) {
			return true;
		}
	}
	return false;
}

bool mapGen::checkDownBounds(vector<vector<bool>> tempMap, pair<int, int> currentPos, char direction, pair<int, int> badDirection) {
	if (currentPos.first < 7 && currentPos.second > 0) {
		if (tempMap[currentPos.first + 1][currentPos.second - 1] != true //down check
			&& tempMap[currentPos.first + 1][currentPos.second] != true
			&& tempMap[currentPos.first + 1][currentPos.second + 1] != true
			&& tempMap[currentPos.first + 2][currentPos.second] != true
			&& currentPos.first + 1 != badDirection.first) {
			return true;
		}
	}
	else if (currentPos.first == 7 && currentPos.second > 0) {
		if (tempMap[currentPos.first + 1][currentPos.second - 1] != true
			&& tempMap[currentPos.first + 1][currentPos.second] != true
			&& tempMap[currentPos.first + 1][currentPos.second + 1] != true
			&& currentPos.first + 1 != badDirection.first) {
			return true;
		}
	}
	return false;
}

bool mapGen::checkRightBounds(vector<vector<bool>> tempMap, pair<int, int> currentPos, char direction, pair<int, int> badDirection) {
	if (currentPos.first > 0 && currentPos.first < 8 && currentPos.second < 14) {
		if (tempMap[currentPos.first - 1][currentPos.second + 1] != true
			&& tempMap[currentPos.first][currentPos.second + 1] != true
			&& tempMap[currentPos.first + 1][currentPos.second + 1] != true
			&& tempMap[currentPos.first][currentPos.second + 2] != true
			&& currentPos.second + 1 != badDirection.second) {
			return true;
		}
	}
	else if (currentPos.second == 14 && currentPos.first > 0 && currentPos.first < 8) {
		if (tempMap[currentPos.first - 1][currentPos.second + 1] != true
			&& tempMap[currentPos.first][currentPos.second + 1] != true
			&& tempMap[currentPos.first + 1][currentPos.second + 1] != true
			&& currentPos.second + 1 != badDirection.second) {
			return true;
		}
	}
	else if (currentPos.second == 14 && currentPos.first == 0) {
		if (tempMap[currentPos.first][currentPos.second + 1] != true
			&& tempMap[currentPos.first + 1][currentPos.second + 1] != true
			&& currentPos.second + 1 != badDirection.second) {
			return true;
		}
	}
	else if (currentPos.second == 14 && currentPos.first == 8) {
		if (tempMap[currentPos.first - 1][currentPos.second + 1] != true
			&& tempMap[currentPos.first][currentPos.second + 1] != true
			&& currentPos.second + 1 != badDirection.second) {
			return true;
		}
	}
	return false;
}

bool mapGen::checkLeftBounds(vector<vector<bool>> tempMap, pair<int, int> currentPos, char direction, pair<int, int> badDirection) {
	if (currentPos.first > 0 && currentPos.first < 8 && currentPos.second > 2) {
		if (tempMap[currentPos.first - 1][currentPos.second - 1] != true
			&& tempMap[currentPos.first][currentPos.second - 1] != true
			&& tempMap[currentPos.first + 1][currentPos.second - 1] != true
			&& tempMap[currentPos.first][currentPos.second - 2] != true
			&& currentPos.second - 1 != badDirection.second) {
			return true;
		}
	}
	else if (currentPos.second == 2 && currentPos.first > 0 && currentPos.first < 8) {
		if (tempMap[currentPos.first - 1][currentPos.second - 1] != true
			&& tempMap[currentPos.first][currentPos.second - 1] != true
			&& tempMap[currentPos.first + 1][currentPos.second - 1] != true
			&& currentPos.second - 1 != badDirection.second) {
			return true;
		}
	}
	else if (currentPos.second == 2 && currentPos.first == 0) {
		if (tempMap[currentPos.first][currentPos.second - 1] != true
			&& tempMap[currentPos.first + 1][currentPos.second - 1] != true
			&& currentPos.second - 1 != badDirection.second) {
			return true;
		}
	}
	else if (currentPos.second == 2 && currentPos.first == 8) {
		if (tempMap[currentPos.first - 1][currentPos.second - 1] != true
			&& tempMap[currentPos.first][currentPos.second - 1] != true
			&& currentPos.second - 1 != badDirection.second) {
			return true;
		}
	}
	return false;
}

vector<pair<int, int>> mapGen::getPossiblePath(vector<vector<bool>> tempMap, pair<int, int> currentPos, char direction, pair<int, int> badDirection) {
	vector<pair<int, int>> possibleMoves;

	if (direction == 'r') {
		if (checkUpBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first - 1, currentPos.second));
		}
		if (checkRightBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first, currentPos.second + 1));
		}
		if (checkDownBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first + 1, currentPos.second));
		}
	}
	else if (direction == 'l') {
		if (checkUpBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first - 1, currentPos.second));
		}
		if (checkLeftBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first, currentPos.second - 1));
		}
		if (checkDownBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first + 1, currentPos.second));
		}
	}
	else if (direction == 'u') {
		if (checkUpBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first - 1, currentPos.second));
		}
		if (checkLeftBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first, currentPos.second - 1));
		}
		if (checkRightBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first, currentPos.second + 1));
		}
	}
	else if (direction == 'd') {
		if (checkLeftBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first, currentPos.second - 1));
		}
		if (checkRightBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first, currentPos.second + 1));
		}
		if (checkDownBounds(tempMap, currentPos, direction, badDirection)) {
			possibleMoves.push_back(pair<int, int>(currentPos.first + 1, currentPos.second));
		}
	}
	else {
		cout << "direction is broken: " << direction << "\n";
	}

	return possibleMoves;
}

//getters
int mapGen::getSeed() {
	return seed;
}
int mapGen::getTileColor() {
	return tileColor;
}
pair<int, int> mapGen::getStartPoint() {
	return startPair;
}
vector<vector<bool>> mapGen::getMap() {
	return map;
}
char** mapGen::getTileMap() {
	return tileMap;
}
vector<pair<int, int>> mapGen::getPath() {
	return pathVec;
}

//printers
void mapGen::printMap() {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 16; c++) {
			cout << map[r][c] << " ";
		}
		cout << endl;
	}
}
void mapGen::printPath() {
	for (int i = 0; i < pathVec.size(); i++) {
		cout << "(" << pathVec[i].first << ", " << pathVec[i].second << ") ";
	}
}