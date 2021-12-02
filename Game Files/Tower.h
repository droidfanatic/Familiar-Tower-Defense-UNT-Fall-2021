#ifndef __L4RC_GAME_TOWER_H__
#define __L4RC_GAME_TOWER_H__
//Tower Variables H File

#include "Object.h"

class CTower : public CObject {
public:
	CTower(const Vector2& p); ///< Constructor.
	CTower(int type, int i, int j, Vector2& p);
	virtual void move(); ///< Move tower

	static const Vector2& GetPosition(int x, int y);
	Vector2 ReturnSpritePos();

	int GetXPos();
	int GetYPos();
	int GetType();
	bool GetDeletionStatus();
	void SetXPos(int x);
	void SetYPos(int y);
	void SetDeletion();

protected:
	void RotateTowards(const Vector2&); ///< Swivel towards position.

	int TowerType = 0;
	bool deleteMark = false;
	
	int xPos = 0;
	int yPos = 0;

	LSpriteDesc2D desc;
};

#endif //__L4RC_GAME_TOWER_H__
