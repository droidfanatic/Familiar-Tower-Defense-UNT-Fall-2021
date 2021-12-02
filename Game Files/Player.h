/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Object.h"
#include "mapGen.h"
#include "TileManager.h"
#include "Common.h"

class CPlayer : public CObject {
  protected:
	  const INT MaxCurrency = 5000; ///< Maximum amount of currency the player may hold at one time
	  int CurrentCurrency = 50; ///< Current currency the player has to purchase towers. Starts off with 50
	  int CurrentLives = 100; ///< Amount of lives that the player has to survive
	  const INT MaxLives = 100; ///< Maximum amount of lives the player can have at one time
	  bool Right = false;
	  bool Left = false;
	  bool Up = false;
	  bool Down = false;
	  bool m_bGodMode = false;

	  int xPos = 0;
	  int yPos = 0;
	  size_t tileSize;

  public:
	CPlayer(const Vector2& p); ///< Constructor.

    virtual void move(); ///< Move player object.

	//Player interaction to place towers
	bool PlaceTower(int Tower);

	//Player movement across grid tiles
	void MoveRight();
	void StopRight();
	void MoveLeft();
	void StopLeft();
	void MoveUp();
	void StopUp();
	void MoveDown();
	void StopDown();

	//Adding & subtracting member variables
	void RemoveLives(int Amount);
	void RemoveCurrency(int Amount);
	void AddLives(int Amount);
	void AddCurrency(int Amount);

	bool isAlive();
	int GetCurrentCurrency();
	std::string GetCurrency();
	std::string GetLives();
	std::string GetTAmount(std::vector<CTower*> amount);

	std::string GetPlayerPosition(); ///< Get position of player sprite

	//Get functions for player position on map
	int GetXPos();
	int GetYPos();

	void CollisionResponse(const Vector2& norm, float d, CObject* pObj);
}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__
