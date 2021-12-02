#include "WaveManger.h"

WaveManager::WaveManager() {
	waveNum = 0;
	enemyCount = 0;
	waveMod = 10;
	enemyIndex = 0;
	totalEnemyCount = 0;
	remainingCount = 0;

	enemyValue[0] = 1;
	enemyValue[1] = 2;
	enemyValue[2] = 3;
	enemyValue[3] = 4;
	enemyValue[4] = 5;
	enemyValue[5] = 10;
	enemyValue[6] = 15;
	enemyValue[7] = 20;
	enemyValue[8] = 25;
	enemyValue[9] = 30;
	enemyValue[10] = 35;
	enemyValue[11] = 40;
	enemyValue[12] = 45;
	enemyValue[13] = 50;
	enemyValue[14] = 55;
	enemyValue[15] = 60;
	enemyValue[16] = 70;
	enemyValue[17] = 80;
	enemyValue[18] = 90;
	enemyValue[19] = 100;
	enemyValue[20] = 125;
	enemyValue[21] = 150;
	enemyValue[22] = 175;
	enemyValue[23] = 200;
}
void WaveManager::resetWaveManager() {
	waveNum = 0;
	enemyCount = 0;
	totalEnemyCount = 0;
	remainingCount = 0;
	waveMod = 10;
	enemyIndex = 0;
	currentWave.clear();
}
void WaveManager::nextWave(pair<int, int> sPoint) {
	startPoint = sPoint;
	waveNum++;
	generateWave();
}
void WaveManager::generateWave() {
	currentWave.clear();
	if (waveNum % 10 == 0) {
		waveMod += 5;
	}
	
	if (waveNum == 1)
	{
		enemyCount = 5;
	}
	else if (waveNum == 2)
	{
		enemyCount = 10;
	}
	else
	{
		enemyCount = 5 + waveMod * waveNum;
	}

	while (enemyCount > 0) {
		//choose random enemy less than value retrieved
		//enemyIndex = 0;
		if (waveNum <= 2) {
			enemyIndex = 0;
		}
		else if (waveNum <= 5) {
			enemyIndex = rand() % 3;
		}
		else if (waveNum <= 10) {
			enemyIndex = rand() % 5;
		}
		else if (waveNum <= 15) {
			enemyIndex = rand() % 7;
		}
		else if (waveNum <= 20) {
			enemyIndex = rand() % 9;
		}
		else if (waveNum <= 25) {
			enemyIndex = rand() % 11;
		}
		else if (waveNum <= 30) {
			enemyIndex = rand() % 13;
		}
		else if (waveNum <= 35) {
			enemyIndex = rand() % 15;
		}
		else if (waveNum <= 40) {
			enemyIndex = rand() % 17;
		}
		else if (waveNum <= 50) {
			enemyIndex = rand() % 20;
		}
		else {
			enemyIndex = rand() % 24;
		}

		if (enemyValue[enemyIndex] <= enemyCount) {
			//pushback enemy onto vector
			currentWave.push_back(enemyIndex);

			//subtract enemy cost value from enemyCount
			enemyCount -= enemyValue[enemyIndex];
		}
	}
	totalEnemyCount = currentWave.size();
	remainingCount = currentWave.size();
}
void WaveManager::spawnWave() {
	if (currentWave.size() != 0) {
		startPointV2.x = startPoint.first;
		startPointV2.y = startPoint.second;
		(CEnemy*)m_pObjectManager->createEnemy(startPointV2, currentWave[0]);
		currentWave.erase(currentWave.begin());
	}
}

//setters
void WaveManager::setWaveNum(int wave) {
	waveNum = wave;
}
void WaveManager::decEnemyRemCount() {
	if (remainingCount > 0) {
		remainingCount--;
	}
}

//getters
int WaveManager::getWaveNum() {
	return waveNum;
}
int WaveManager::getTotalCount() {
	return totalEnemyCount;
}
int WaveManager::getRemainingCount() {
	return remainingCount;
}