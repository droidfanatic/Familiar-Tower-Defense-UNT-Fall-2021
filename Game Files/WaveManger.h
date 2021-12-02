#pragma once
#include <vector>
#include "Common.h"
#include "Enemy.h"

using namespace std;

class WaveManager : public CCommon {
private:
	int waveNum;
	int enemyCount;
	int waveMod;
	int enemyIndex;
	int totalEnemyCount;
	int remainingCount;
	pair<int, int> startPoint;
	Vector2 startPointV2;
	int enemyValue[24];
	vector<int> currentWave;

	void generateWave();
	//setters

	//getters

public:
	WaveManager();
	void nextWave(pair<int, int> sPoint);
	void spawnWave();

	//setters
	void setWaveNum(int wave);
	void resetWaveManager();
	void decEnemyRemCount();

	//getters
	int getWaveNum();
	int getTotalCount();
	int getRemainingCount();
};