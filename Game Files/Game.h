/// \file Game.h
/// \brief Interface for the game class CGame.

#ifndef __L4RC_GAME_GAME_H__
#define __L4RC_GAME_GAME_H__

#include "Component.h"
#include "Common.h"
#include "ObjectManager.h"
#include "Settings.h"
#include <string>
#include "Player.h"
#include "mapGen.h"
#include "Enemy.h"
#include "Tower.h"
#include "WaveManger.h"
#include <vector>

/// \brief The game class.
///
/// The game class is the object-oriented implementation of the game. This class
/// must contain the following public member functions. `Initialize()` does
/// initialization and will be run exactly once at the start of the game.
/// `ProcessFrame()` will be called once per frame to create and render the
/// next animation frame. `Release()` will be called at game exit but before
/// any destructors are run.

class CGame :
    public LComponent,
    public LSettings,
    public CCommon {

private:
    bool m_bDrawFrameRate = false; ///< Draw the frame rate.
    eGameState m_eGameState = eGameState::Waiting; ///< Game state.
    int m_nNextLevel = 0; ///< Current level number.
    int eMove = 0;
    int eCounter = 0;
    int spawnDelay = 30;
    int waveDelay = 60;
    int spawnDelayCounter = 0;
    int waveDelayCounter = 0;
    int enemyCounter = 0;
    int MenuButtonNums[5];
    bool Menus[5];
    bool FirstTowerSet = true;
    bool PlaySound = true;
    bool AutoSpawn = false;
    bool AutoSpawnInProg = false;
    bool WaveInProg = false;
    Vector2 cursorPos;
    LSpriteDesc2D TowerDesc;
    LSpriteDesc2D WaveProgessDesc;
    vector<int> TowerGUIS;
    
    void LoadImages(); ///< Load images.
    void LoadSounds(); ///< Load sounds.
    void ToggleSound();
    void ToggleAssets();
    void MainMenu();
    void LevelMenu();
    void Settings();
    void Help();
    void BeginGame(); ///< Begin playing the game.
    void KeyboardHandler(); ///< The keyboard handler.
    void ControllerHandler(); ///< The controller handler.
    void RenderFrame(); ///< Render an animation frame.
    void DrawFrameRateText(); ///< Draw frame rate text to screen.
    void DrawGodModeText(); ///< Draw god mode text if in god mode.
    void CreateObjects(); ///< Create game objects.
    void FollowCamera(); ///< Make camera follow player character.
    void ProcessGameState(); ///< Process game state.

	void DrawVariablesToScreen(); //Render player variables to screen

	bool CheckTile();
	bool CheckExistingTower(int x, int y);
	//std::string GetTAmount(std::vector<CTower*> amount);

  public:
    ~CGame(); ///< Destructor.

    void Initialize(); ///< Initialize the game.
    void ProcessFrame(); ///< Process an animation frame.
    void Release(); ///< Release the renderer.

	CTower* baseTower;
}; //CGame

#endif //__L4RC_GAME_GAME_H__
