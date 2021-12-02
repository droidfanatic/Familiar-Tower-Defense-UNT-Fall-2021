#pragma once
#include <vector>

using namespace std;

class mapGen {
private:
	vector<vector<bool>> map;
	char** tileMap;
	int failMod, forceRestart, startPoint, dirChoice, seed, tileColor;
	float terrainNum;
	pair<int, int> startPair, endPair, posPair, badDirectionPair;
	vector<pair<int, int>> possiblePathVec, pathVec;
	vector<char> directions;

	//getters
	vector<pair<int, int>> getPossiblePath(vector<vector<bool>>, pair<int, int>, char, pair<int, int>);
	bool checkUpBounds(vector<vector<bool>>, pair<int, int>, char, pair<int, int>);
	bool checkDownBounds(vector<vector<bool>>, pair<int, int>, char, pair<int, int>);
	bool checkRightBounds(vector<vector<bool>>, pair<int, int>, char, pair<int, int>);
	bool checkLeftBounds(vector<vector<bool>>, pair<int, int>, char, pair<int, int>);

public:
	//construtor
	mapGen();

	//setters
	void createBlankMap();
	void createNewMap();
	void createNewMap(int);

	//getters
	int getSeed();
	int getTileColor();
	pair<int, int> getStartPoint();
	vector<vector<bool>> getMap();
	char** getTileMap();
	vector<pair<int, int>> getPath();

	//printers
	void printMap();
	void printPath();
};