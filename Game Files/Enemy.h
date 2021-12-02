//Enemy Variables H File
#ifndef __L4RC_GAME_ENEMY_H__
#define __L4RC_GAME_ENEMY_H__

#include "Object.h"
#include "mapGen.h"
#include "Common.h"
#include "TileManager.h"
#include "Game.h"
#include "ComponentIncludes.h"
#include "WaveManger.h"

class CEnemy : public CObject
{
protected:
	int EnemyType = 0;
	LSpriteDesc2D desc;

	UINT EnemyMoveSpeed = 1; ///< The speed that the enemies move along the track, default is 2 (MUST BE EVENLY DIVISIBLE BY 124)
	int EnemyHealth = 1; ///< The amount of health that an enemy starts with, starting is 10
	int EnemyWorth = 2; ///< The amount of currency that an emey will drop for the user, default is 10
	int pathIndex = 0;
	
	int moveCounter = 0;
	Vector2 eTarget;
	Vector2 eDest;
public:
	CEnemy(int type, const Vector2& p); ///< Constructor

	virtual void move();

	void RemoveHealth(int Amount);

	static const Vector2& GetPos(pair<int, int>);

	bool getIsDead();

	void CollisionResponse(const Vector2& norm, float d, CObject* pObj);

	void kill();

	bool checkDead();
};

#endif