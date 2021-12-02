/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"

#include "GameDefines.h"
#include "SpriteRenderer.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"
#include "TileManager.h"
#include "shellapi.h"
#include <fstream>
#include <iostream>

/// Delete the renderer, the object manager, and the tile manager. The renderer
/// needs to be deleted before this destructor runs so it will be done elsewhere.

CGame::~CGame(){
  delete m_pParticleEngine;
  delete m_pObjectManager;
  delete m_pTileManager;
  delete pMap;
  delete pWave;
} //destructor

/// Initialize the renderer, the tile manager and the object manager, load 
/// images and sounds, and begin the game.

void CGame::Initialize(){
  m_pRenderer = new LSpriteRenderer(eSpriteMode::Batched2D); 
  m_pRenderer->Initialize(eSprite::Size); 
  LoadImages(); //load images from xml file list
  
  m_pTileManager = new CTileManager((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * .5f);
  m_pObjectManager = new CObjectManager; //set up the object manager 
  LoadSounds(); //load the sounds for this game

  m_pParticleEngine = new LParticleEngine2D(m_pRenderer);

  pMap = new mapGen();
  pWave = new WaveManager();

  for (int i = 0; i < 17; i++) {
	  TowerGUIS.push_back(i);
  }

  TowerDesc.m_nSpriteIndex = (UINT)eSprite::Tower;
  WaveProgessDesc.m_nSpriteIndex = (UINT)eSprite::WaveProgress;

  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - 40);

  Menus[0] = true;
  Menus[1] = false;
  Menus[2] = false;
  Menus[3] = false;
  Menus[4] = false;

  MenuButtonNums[0] = 0;
  MenuButtonNums[1] = 0;
  MenuButtonNums[2] = 0;
  MenuButtonNums[3] = 0;
  MenuButtonNums[4] = 0;
  if (PlaySound) {
	  m_pAudio->stop();
	  m_pAudio->loop(eSound::MenuMusic);
  }
  MainMenu();
} //Initialize

/// Load the specific images needed for this game. This is where `eSprite`
/// values from `GameDefines.h` get tied to the names of sprite tags in
/// `gamesettings.xml`. Those sprite tags contain the name of the corresponding
/// image file. If the image tag or the image file are missing, then the game
/// should abort from deeper in the Engine code leaving you with an error
/// message in a dialog box.

void CGame::LoadImages(){  
  m_pRenderer->BeginResourceUpload();

  m_pRenderer->Load(eSprite::Background, "Background");
  m_pRenderer->Load(eSprite::Background2, "Background2");
  m_pRenderer->Load(eSprite::MapBorder, "MapBorder");
  m_pRenderer->Load(eSprite::BlueTile, "BlueTile");
  m_pRenderer->Load(eSprite::BrownTile, "BrownTile");
  m_pRenderer->Load(eSprite::GrayTile, "GrayTile");
  m_pRenderer->Load(eSprite::RedTile, "RedTile");
  m_pRenderer->Load(eSprite::Auto, "Auto");
  m_pRenderer->Load(eSprite::NoAuto, "NoAuto");
  m_pRenderer->Load(eSprite::Checked, "Checked");
  m_pRenderer->Load(eSprite::Unchecked, "Unchecked");
  m_pRenderer->Load(eSprite::WaveProgress, "WaveProgress");
  m_pRenderer->Load(eSprite::GameOver, "GameOver");
  m_pRenderer->Load(eSprite::Health, "Health");
  m_pRenderer->Load(eSprite::Mana, "Mana");
  m_pRenderer->Load(eSprite::WaveNumber, "WaveNumber");
  m_pRenderer->Load(eSprite::Tselect, "Tselect");
  m_pRenderer->Load(eSprite::Tunselect, "Tunselect");
  m_pRenderer->Load(eSprite::MenuUButton, "MenuUButton");
  m_pRenderer->Load(eSprite::MenuCursor, "MenuCursor");
  m_pRenderer->Load(eSprite::Player,  "player");
  m_pRenderer->Load(eSprite::Bullet,  "bullet");
  m_pRenderer->Load(eSprite::Bullet2, "bullet2");
  m_pRenderer->Load(eSprite::Bullet3, "bullet3");
  m_pRenderer->Load(eSprite::Bullet4, "bullet4");
  m_pRenderer->Load(eSprite::Bullet5, "bullet5");
  m_pRenderer->Load(eSprite::Bullet6, "bullet6");
  m_pRenderer->Load(eSprite::Bullet7, "bullet7");
  m_pRenderer->Load(eSprite::Bullet8, "bullet8");
  m_pRenderer->Load(eSprite::Bullet9, "bullet9");
  m_pRenderer->Load(eSprite::Bullet10, "bullet10");
  m_pRenderer->Load(eSprite::Bullet11, "bullet11");
  m_pRenderer->Load(eSprite::Bullet12, "bullet12");
  m_pRenderer->Load(eSprite::Bullet13, "bullet13");
  m_pRenderer->Load(eSprite::Bullet14, "bullet14");
  m_pRenderer->Load(eSprite::Bullet15, "bullet15");
  m_pRenderer->Load(eSprite::Bullet16, "bullet16");
  m_pRenderer->Load(eSprite::Bullet17, "bullet17");
  m_pRenderer->Load(eSprite::Smoke,   "smoke");
  m_pRenderer->Load(eSprite::Spark,   "spark");
  m_pRenderer->Load(eSprite::Tower,   "Tower");
  m_pRenderer->Load(eSprite::TowerNumber, "TowerNumber");
  m_pRenderer->Load(eSprite::TowerCursor, "TowerCursor");
  m_pRenderer->Load(eSprite::TowerPrice, "TowerPrice"); 
  m_pRenderer->Load(eSprite::ParberryTower, "ParberryTower");
  m_pRenderer->Load(eSprite::ParberryTowerFlipped, "ParberryTowerFlipped");
  m_pRenderer->Load(eSprite::EnemyS, "EnemyS");
  m_pRenderer->Load(eSprite::Student, "Student");
  m_pRenderer->Load(eSprite::Title, "Title");
  m_pRenderer->Load(eSprite::Help, "Help");
  m_pRenderer->EndResourceUpload();
} //LoadImages

/// Initialize the audio player and load game sounds.

void CGame::LoadSounds(){
  m_pAudio->Initialize(eSound::Size);

  m_pAudio->Load(eSound::Gun, "gun");
  m_pAudio->Load(eSound::Boom, "boom");
  m_pAudio->Load(eSound::MenuMusic, "MenuMusic");
  m_pAudio->Load(eSound::BossWave, "BossWave");
  m_pAudio->Load(eSound::Click, "Click");
  m_pAudio->Load(eSound::lifeLost, "lifeLost");
  m_pAudio->Load(eSound::manaDrop, "manaDrop");
  m_pAudio->Load(eSound::towerPlaced, "towerPlaced");
} //LoadSounds

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release(){
  delete m_pRenderer;
  m_pRenderer = nullptr; //for safety
} //Release

/// Ask the object manager to create a player object and turrets specified by
/// the tile manager.

void CGame::CreateObjects(){
  std::vector<Vector2> turretpos; //vector of turret positions
  Vector2 playerpos; //player positions
  m_pTileManager->GetObjects(turretpos, playerpos); //get positions
  
  m_pPlayer = (CPlayer*)m_pObjectManager->create(eSprite::Player, playerpos);
} //CreateObjects

void CGame::ToggleSound() {
	if (PlaySound) {
		m_pAudio->stop();
	}
	else {
		m_pAudio->loop(eSound::MenuMusic);
	}
	PlaySound = !PlaySound;
}

void CGame::ToggleAssets() {
	m_bNormalAssets = !m_bNormalAssets;
	if (m_bNormalAssets) {
		TowerDesc.m_nSpriteIndex = (UINT)eSprite::Tower;
	}
	else {
		TowerDesc.m_nSpriteIndex = (UINT)eSprite::ParberryTower;
	}
}

void CGame::MainMenu() {
	pWave->resetWaveManager();
    m_pParticleEngine->clear(); //clear old particles
    m_pObjectManager->clear(); //clear old objects
    m_bScreenText = false;

    pMap->createBlankMap();
    m_pTileManager->LoadEmptyMap(pMap->getTileMap());

    baseTowers.clear();

    m_eGameState = eGameState::Waiting;
}

void CGame::LevelMenu() {
    m_pParticleEngine->clear(); //clear old particles
    m_pObjectManager->clear(); //clear old objects
}

void CGame::Settings() {
    m_pParticleEngine->clear(); //clear old particles
    m_pObjectManager->clear(); //clear old objects
}

void CGame::Help() {
    m_pParticleEngine->clear(); //clear old particles
    m_pObjectManager->clear(); //clear old objects
}

/// Call this function to start a new game. This should be re-entrant so that
/// you can restart a new game without having to shut down and restart the
/// program. Clear the particle engine to get rid of any existing particles,
/// delete any old objects out of the object manager and create some new ones.

void CGame::BeginGame(){  
  m_pParticleEngine->clear(); //clear old particles
  FirstTowerSet = true;

  for (int i = baseTowers.size() - 1; i >= 0; i--) {
	  delete baseTowers[i];
  }
  baseTowers.clear();

  AutoSpawn = false;
  AutoSpawnInProg = false;

  pMap->createNewMap();
  m_pTileManager->LoadMap(pMap->getTileMap());

  // just so I could see the path coords
  ofstream file("mapOutput.txt");
  streambuf* buf = cout.rdbuf();
  cout.rdbuf(file.rdbuf());

  pMap->printPath();
  
  m_pObjectManager->clear(); //clear old objects
  CreateObjects(); //create new objects (must be after map is loaded) 
  if (PlaySound) {
	  m_pAudio->stop();
	  m_pAudio->loop(eSound::BossWave);
  }
  //m_pAudio->stop(); //stop all currently playing sounds
  //m_pAudio->play(eSound::Start); //play start-of-game sound
  m_eGameState = eGameState::Playing; //now playing
  //DrawVariablesToScreen();
  m_bScreenText = true;

  pair<int, int> startLocation = pMap->getStartPoint();

  auto startPoint = pMap->getStartPoint();
  pWave->resetWaveManager();

} //BeginGame

/// Poll the keyboard state and respond to the key presses that happened since
/// the last frame.

void CGame::KeyboardHandler(){
  m_pKeyboard->GetState(); //get current keyboard state
  if (m_eGameState == eGameState::Waiting) {
	  if (Menus[0]) {// main menu
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[0] == 0) { //Level menu
			  m_pAudio->play(eSound::Click);
			  MenuButtonNums[0] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[1])));
			  Menus[0] = false;
			  //Menus[1] = true;
			  BeginGame();
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[0] == 1) { //settings menu
			  m_pAudio->play(eSound::Click);
			  MenuButtonNums[0] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[2])));
			  Menus[0] = false;
			  Menus[2] = true;
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[0] == 2) { //help screen
			  m_pAudio->play(eSound::Click);
			  MenuButtonNums[0] = 0;
			  MenuButtonNums[3] = 2;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[3])));
			  Menus[0] = false;
			  Menus[3] = true;
		  } //if

		  if ((m_pKeyboard->TriggerDown('W') || m_pKeyboard->TriggerDown(VK_UP)) && MenuButtonNums[0] != 0) {
			  MenuButtonNums[0] -= 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[0])));
		  }
		  if ((m_pKeyboard->TriggerDown('S') || m_pKeyboard->TriggerDown(VK_DOWN)) && MenuButtonNums[0] != 2) {
			  MenuButtonNums[0] += 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[0])));
		  }
	  }
	  else if (Menus[1]) {// level select
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[1] == 0) {
			  m_pAudio->play(eSound::Click);
			  MenuButtonNums[1] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[0])));
			  Menus[1] = false;
			  BeginGame();
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[1] == 2) {
			  m_pAudio->play(eSound::Click);
			  MenuButtonNums[1] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[0])));
			  Menus[0] = true;
			  Menus[1] = false;
		  }

		  if ((m_pKeyboard->TriggerDown('W') || m_pKeyboard->TriggerDown(VK_UP)) && MenuButtonNums[1] != 0) {
			  MenuButtonNums[1] -= 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[1])));
		  }
		  if ((m_pKeyboard->TriggerDown('S') || m_pKeyboard->TriggerDown(VK_DOWN)) && MenuButtonNums[1] != 2) {
			  MenuButtonNums[1] += 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[1])));
		  }
	  }
	  else if (Menus[2]) { // settings
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[2] == 0) { // change assests
			  m_pAudio->play(eSound::Click);
			  ToggleAssets();
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[2] == 1) { // toggle sounds
			  m_pAudio->play(eSound::Click);
			  ToggleSound();
		  }
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[2] == 2) {
			  m_pAudio->play(eSound::Click);
			  MenuButtonNums[2] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[0])));
			  Menus[0] = true;
			  Menus[2] = false;
		  } //if

		  if ((m_pKeyboard->TriggerDown('W') || m_pKeyboard->TriggerDown(VK_UP)) && MenuButtonNums[2] != 0) {
			  MenuButtonNums[2] -= 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[2])));
		  }
		  if ((m_pKeyboard->TriggerDown('S') || m_pKeyboard->TriggerDown(VK_DOWN)) && MenuButtonNums[2] != 2) {
			  MenuButtonNums[2] += 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[2])));
		  }
	  }
	  else if (Menus[3]) { // about
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[3] == 2) {
			  m_pAudio->play(eSound::Click);
			  MenuButtonNums[3] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[0])));
			  Menus[0] = true;
			  Menus[3] = false;
		  } //if
	  }
  }
  else if (m_eGameState == eGameState::Gameover) {
	  if (Menus[4]) {// gameover
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[4] == 0) { // Restart Game
			  m_pAudio->play(eSound::Click);
			  MenuButtonNums[4] = 0;
			  Menus[4] = false;
			  BeginGame();
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[4] == 1) { // Return To Main Menu
			  if (PlaySound) {
				  m_pAudio->stop();
				  m_pAudio->loop(eSound::MenuMusic);
			  }
			  m_pAudio->play(eSound::Click);
			  MainMenu();
			  MenuButtonNums[4] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 180, m_nWinHeight / 2 - (40 + (90 * MenuButtonNums[0])));
			  Menus[0] = true;
			  Menus[4] = false;
		  } //if

		  if ((m_pKeyboard->TriggerDown('A') || m_pKeyboard->TriggerDown(VK_LEFT)) && MenuButtonNums[4] != 0) {
			  MenuButtonNums[4] -= 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 230, m_nWinHeight / 2 - 83);
		  }
		  if ((m_pKeyboard->TriggerDown('D') || m_pKeyboard->TriggerDown(VK_RIGHT)) && MenuButtonNums[4] != 1) {
			  MenuButtonNums[4] += 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 - 83);
		  }
	  }
  }
  else if (m_eGameState == eGameState::Playing) {
	  if (m_pKeyboard->TriggerDown(VK_RETURN) && m_bGodMode) {
		  pWave->resetWaveManager();
		  BeginGame();
	  } //if
	  /*if (m_pKeyboard->TriggerDown(VK_SPACE)) {
		  m_pPlayer->AddCurrency(1000);
		  m_bGodMode = !m_bGodMode;
	  }
	  //Kill Switch... I Got Tired Of Waiting To Die
	  if (m_pKeyboard->Down(VK_CONTROL) && m_pKeyboard->Down('K') && m_bGodMode) {
		  m_pPlayer->RemoveLives(1000);
		  m_bGodMode = !m_bGodMode;
	  }*/

	  //if (m_pKeyboard->TriggerDown(VK_F1)) //help
		  //ShellExecute(0, 0, "https://larc.unt.edu/code/topdown/", 0, 0, SW_SHOW);

	  if (m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate
		  m_bDrawFrameRate = !m_bDrawFrameRate;

	  //if (m_pKeyboard->TriggerDown(VK_F3)) //toggle AABB drawing
		  //m_bDrawAABBs = !m_bDrawAABBs;

	  //-----------------------------------------------------------------------------------------
	  //Player controls to move from tile to tile
	  //Move Player Right
	  if (m_pKeyboard->TriggerDown('D') || m_pKeyboard->TriggerDown(VK_RIGHT)) {
		  m_pPlayer->MoveRight();
		  m_pPlayer->move();
		  m_pPlayer->StopRight();
	  }
	  //Move Player Left
	  if (m_pKeyboard->TriggerDown('A') || m_pKeyboard->TriggerDown(VK_LEFT)) {
		  m_pPlayer->MoveLeft();
		  m_pPlayer->move();
		  m_pPlayer->StopLeft();
	  }
	  //Move Player Up
	  if (m_pKeyboard->TriggerDown('W') || m_pKeyboard->TriggerDown(VK_UP)) {
		  m_pPlayer->MoveDown();
		  m_pPlayer->move();
		  m_pPlayer->StopDown();
	  }
	  //Move Player Down
	  if (m_pKeyboard->TriggerDown('S') || m_pKeyboard->TriggerDown(VK_DOWN)) {
		  m_pPlayer->MoveUp();
		  m_pPlayer->move();
		  m_pPlayer->StopUp();
	  }
	  //-----------------------------------------------------------------------------------------
	  //Controls for the player to place tower
	  //Tower 1/9 Placement
	  if (m_pKeyboard->TriggerDown('1'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(1) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(35);
					  }
					  baseTowers.push_back(new CTower(1, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
				  else if (m_pPlayer->PlaceTower(9) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(515);
					  }
					  baseTowers.push_back(new CTower(9, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
			  }
		  }
	  //Tower 2/10 Placement
	  if (m_pKeyboard->TriggerDown('2'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(2) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(75);
					  }
					  baseTowers.push_back(new CTower(2, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
				  else if (m_pPlayer->PlaceTower(10) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(600);
					  }
					  baseTowers.push_back(new CTower(10, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
			  }
		  }
	  //Tower 3/11 Placement
	  if (m_pKeyboard->TriggerDown('3'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(3) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(115);
					  }
					  baseTowers.push_back(new CTower(3, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
				  else if (m_pPlayer->PlaceTower(11) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(675);
					  }
					  baseTowers.push_back(new CTower(11, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
			  }
		  }
	  //Tower 4/12 Placement
	  if (m_pKeyboard->TriggerDown('4'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(4) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(200);
					  }
					  baseTowers.push_back(new CTower(4, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
				  else if (m_pPlayer->PlaceTower(12) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(750);
					  }
					  baseTowers.push_back(new CTower(12, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
			  }
		  }
	  //Tower 5/13 Placement
	  if (m_pKeyboard->TriggerDown('5'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(5) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(300);
					  }
					  baseTowers.push_back(new CTower(5, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
				  else if (m_pPlayer->PlaceTower(13) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(825);
					  }
					  baseTowers.push_back(new CTower(13, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
			  }
		  }
	  //Tower 6/14 Placement
	  if (m_pKeyboard->TriggerDown('6'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(6) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(375);
					  }
					  baseTowers.push_back(new CTower(6, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
				  else if (m_pPlayer->PlaceTower(14) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(875);
					  }
					  baseTowers.push_back(new CTower(14, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
			  }
		  }
	  //Tower 7/15 Placement
	  if (m_pKeyboard->TriggerDown('7'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(7) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(445);
					  }
					  baseTowers.push_back(new CTower(7, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
				  else if (m_pPlayer->PlaceTower(15) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(930);
					  }
					  baseTowers.push_back(new CTower(15, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
			  }
		  }
	  //Tower 8/16 Placement
	  if (m_pKeyboard->TriggerDown('8'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(8) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(480);
					  }
					  baseTowers.push_back(new CTower(8, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
				  else if (m_pPlayer->PlaceTower(16) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(995);
					  }
					  baseTowers.push_back(new CTower(16, i, j, m_pPlayer->m_vPos));
					  m_pAudio->play(eSound::towerPlaced);
				  }
			  }
		  }
	  //Tower Switch Button
	  if (m_pKeyboard->TriggerDown('0')) {
		  if (FirstTowerSet != true) FirstTowerSet = true;
		  else {
			  FirstTowerSet = false;
		  }
	  }

	  //Player Familiar Shot Button
	  if (m_pKeyboard->TriggerDown('Q')) {
		  if (m_pPlayer->GetCurrentCurrency() - 20 >= 0) {
			  m_pPlayer->RemoveCurrency(20);
			  m_pObjectManager->FireGun(m_pPlayer, 12, eSprite::Bullet);
		  }
	  }

	  //Tower Deletion Button
	  if (m_pKeyboard->TriggerDown('Z')) {
		  int i = 0;
		  int j = 0;
		  i = m_pPlayer->GetXPos();
		  j = m_pPlayer->GetYPos();
		  if (CheckExistingTower(i, j) == true) {
			  Vector2 playerPos = m_pPlayer->m_vPos;
			  for (int x = 0; x < baseTowers.size(); x++) {
				  if (baseTowers[x]->GetXPos() == i && baseTowers[x]->GetYPos() == j) {
					  baseTowers[x]->SetDeletion();
					  int towerType = baseTowers[x]->GetType();
					  //Get Money Back From Selling Tower
					  switch (towerType) {
						case 1:
							m_pPlayer->AddCurrency(5);
							break;
						case 2:
							m_pPlayer->AddCurrency(10);
							break;
						case 3:
							m_pPlayer->AddCurrency(20);
							break;
						case 4:
							m_pPlayer->AddCurrency(35);
							break;
						case 5:
							m_pPlayer->AddCurrency(50);
							break;
						case 6:
							m_pPlayer->AddCurrency(75);
							break;
						case 7:
							m_pPlayer->AddCurrency(100);
							break;
						case 8:
							m_pPlayer->AddCurrency(135);
							break;
						case 9:
							m_pPlayer->AddCurrency(175);
							break;
						case 10:
							m_pPlayer->AddCurrency(200);
							break;
						case 11:
							m_pPlayer->AddCurrency(225);
							break;
						case 12:
							m_pPlayer->AddCurrency(250);
							break;
						case 13:
							m_pPlayer->AddCurrency(275);
							break;
						case 14:
							m_pPlayer->AddCurrency(300);
							break;
						case 15:
							m_pPlayer->AddCurrency(350);
							break;
						case 16:
							m_pPlayer->AddCurrency(400);
							break;
						default:
							m_pPlayer->AddCurrency(10);
							break;
					  }
				  }
			  }
		  }
	  }

	  //Toggle Gun Fire Sounds
	  if (m_pKeyboard->TriggerDown('V')) {
		  if (m_bGunSound == true)
			m_bGunSound = false;
		  else {
			  m_bGunSound = true;
		  }
	  }


	  //-----------------------------------------------------------------------------------------
	  //Debug Controls
	  //if (m_pKeyboard->TriggerDown(VK_F1)) //help
		  //ShellExecute(0, 0, "https://larc.unt.edu/code/topdown/", 0, 0, SW_SHOW);

	  if (m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate
		  m_bDrawFrameRate = !m_bDrawFrameRate;

	  //if (m_pKeyboard->TriggerDown(VK_F3)) //toggle AABB drawing
		  //m_bDrawAABBs = !m_bDrawAABBs;

	  //-----------------------------------------------------------------------------------------
	  if (m_pKeyboard->TriggerDown(VK_BACK)) //start game
		  BeginGame();

	  if (m_pKeyboard->TriggerDown('E')) {
		  if (!WaveInProg) {
			  if (AutoSpawn && !AutoSpawnInProg) {
				  AutoSpawnInProg = true;
			  }
			  else {
				  pWave->nextWave(pMap->getStartPoint());
			  }
		  }
	  }

	  if (m_pKeyboard->TriggerDown('R')) {
		  AutoSpawn = !AutoSpawn;
		  if (!AutoSpawn) {
			  AutoSpawnInProg = false;
		  }
	  }
  }
} //KeyboardHandler

/// Poll the XBox controller state and respond to the controls there.

void CGame::ControllerHandler(){
  if(!m_pController->IsConnected())return;

  m_pController->GetState(); //get state of controller's controls 
} //ControllerHandler

/// Draw the current frame rate to a hard-coded position in the window.
/// The frame rate will be drawn in a hard-coded position using the font
/// specified in `gamesettings.xml`.

void CGame::DrawFrameRateText(){
  const std::string s = std::to_string(m_pTimer->GetFPS()) + " fps"; //frame rate
  const Vector2 pos(m_nWinWidth - 128.0f, 30.0f); //hard-coded position
  m_pRenderer->DrawScreenText(s.c_str(), pos, Colors::White); //draw to screen
} //DrawFrameRateText

/// Draw the god mode text to a hard-coded position in the window using the
/// font specified in `gamesettings.xml`.

void CGame::DrawGodModeText(){
  const Vector2 pos(32.0f, 5.0f); //hard-coded position
  m_pRenderer->DrawScreenText("God Mode", pos, Colors::Red); //draw to screen
} //DrawGodModeText

/// Ask the object manager to draw the game objects. The renderer is notified of
/// the start and end of the frame so that it can let Direct3D do its
/// pipelining jiggery-pokery.

void CGame::RenderFrame(){
  m_pRenderer->BeginFrame(); //required before rendering

  if (m_eGameState == eGameState::Waiting) {
	  m_pRenderer->Draw(eSprite::Background, m_vWinCenter); //draw background
	  m_pRenderer->Draw(eSprite::Background2, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 15)); //draw background 
	  if (Menus[3] == 0) {
		  m_pRenderer->Draw(eSprite::Title, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 + 125));
	  }
  }
  else {
	  m_pRenderer->Draw(eSprite::Background, Vector2(m_vWorldSize.x / 2.0f, m_vWorldSize.y / 2.0f)); //draw background
	  WaveProgessDesc.m_nCurrentFrame = 0;
	  WaveProgessDesc.m_fXScale = 1;
	  WaveProgessDesc.m_vPos = Vector2(m_vWorldSize.x / 2.0f, m_vWorldSize.y + 33);
	  m_pRenderer->Draw(&WaveProgessDesc);
  }

  if (Menus[0]) { //Main Menu
      m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 40));
      m_pRenderer->DrawScreenText("Start Game", Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 + 17), Colors::Azure);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 130));
      m_pRenderer->DrawScreenText("Settings", Vector2(m_nWinWidth / 2 - 57, m_nWinHeight / 2 + 107), Colors::Azure);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 220));
      m_pRenderer->DrawScreenText("Help", Vector2(m_nWinWidth / 2 - 35, m_nWinHeight / 2 + 197), Colors::Azure);
  }
  else if (Menus[1]) { //Level Menu
      m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2));
      m_pRenderer->DrawScreenText("Start Game", Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 - 20), Colors::Azure);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 220));
      m_pRenderer->DrawScreenText("Back", Vector2(m_nWinWidth / 2 - 35, m_nWinHeight / 2 + 197), Colors::Azure);
  }
  else if (Menus[2]) { //Settings
      m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
	  if (m_bNormalAssets) {
		  m_pRenderer->Draw(eSprite::Checked, Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 - 40));
	  }
	  else {
		  m_pRenderer->Draw(eSprite::Unchecked, Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 - 40));
	  }
	  if (PlaySound) {
		  m_pRenderer->Draw(eSprite::Checked, Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 - 130));
	  }
	  else {
		  m_pRenderer->Draw(eSprite::Unchecked, Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 - 130));
	  }
	  m_pRenderer->DrawScreenText("Normal Assets?", Vector2(m_nWinWidth / 2 - 46, m_nWinHeight / 2 + 18), Colors::Black);
	  m_pRenderer->DrawScreenText("Normal Assets?", Vector2(m_nWinWidth / 2 - 45, m_nWinHeight / 2 + 17), Colors::Azure);
	  m_pRenderer->DrawScreenText("Music On?", Vector2(m_nWinWidth / 2 - 26, m_nWinHeight / 2 + 108), Colors::Black);
	  m_pRenderer->DrawScreenText("Music On?", Vector2(m_nWinWidth / 2 - 25, m_nWinHeight / 2 + 107), Colors::Azure);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 220));
      m_pRenderer->DrawScreenText("Back", Vector2(m_nWinWidth / 2 - 35, m_nWinHeight / 2 + 197), Colors::Azure);
  }
  else if (Menus[3]) { //Help
	  m_pRenderer->Draw(eSprite::Help, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 + 45));
      m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 220));
      m_pRenderer->DrawScreenText("Back", Vector2(m_nWinWidth / 2 - 35, m_nWinHeight / 2 + 197), Colors::Azure);
  }

  m_pObjectManager->draw(pMap->getTileColor()); //draw objects
  m_pParticleEngine->Draw(); //draw particles
  if(m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required
  if(m_bGodMode)DrawGodModeText(); //draw god mode text, if required
  if(m_bScreenText)DrawVariablesToScreen(); //draw player variables

  for (int i = 0; i < baseTowers.size(); i++) {
	  if (baseTowers[i]->GetDeletionStatus() != true) {
          baseTowers[i]->draw();
      }
  }
  if (m_eGameState == eGameState::Playing || m_eGameState == eGameState::Gameover) {
	  if (AutoSpawn) {
		  m_pRenderer->Draw(eSprite::Auto, Vector2(242.0f, m_vWorldSize.y + 33));
	  }
	  else {
		  m_pRenderer->Draw(eSprite::NoAuto, Vector2(242.0f, m_vWorldSize.y + 33));
	  }
	  m_pRenderer->Draw(eSprite::WaveNumber, Vector2(100.0f, m_vWorldSize.y + 33));
	  m_pRenderer->Draw(eSprite::Health, Vector2(750.0f, m_vWorldSize.y + 33));
	  m_pRenderer->Draw(eSprite::Mana, Vector2(900.0f, m_vWorldSize.y + 33));
	  if (FirstTowerSet) {
		  m_pRenderer->Draw(eSprite::Tselect, Vector2(-54, m_vWorldSize.y / 2.0f));
		  m_pRenderer->Draw(eSprite::Tunselect, Vector2(m_vWorldSize.x + 54, m_vWorldSize.y / 2.0f));
	  }
	  else {
		  m_pRenderer->Draw(eSprite::Tunselect, Vector2(-54, m_vWorldSize.y / 2.0f));
		  m_pRenderer->Draw(eSprite::Tselect, Vector2(m_vWorldSize.x + 54, m_vWorldSize.y / 2.0f));
	  }
	  for (int i = 0; i < 16; i++) {
		  TowerDesc.m_nCurrentFrame = i;
		  if (i < 8) {
			  TowerDesc.m_vPos = Vector2(-53, (m_vWorldSize.y - 15) - (62 * i));
		  }
		  else {
			  TowerDesc.m_vPos = Vector2((m_vWorldSize.x + 54), (m_vWorldSize.y - 15) - (62 * (i - 8)));
		  }

		  m_pRenderer->Draw(&TowerDesc);
		  m_pRenderer->Draw(eSprite::TowerPrice, Vector2(m_vWorldSize.x / 2.0f, -33));

		  if (FirstTowerSet) {
			  m_pRenderer->Draw(eSprite::TowerCursor, Vector2(-54, m_vWorldSize.y - 542));
			  m_pRenderer->Draw(eSprite::TowerNumber, Vector2(-54, m_vWorldSize.y / 2.0f));
			  m_pRenderer->DrawScreenText("35", Vector2(265, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("75", Vector2(355, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("115", Vector2(448, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("200", Vector2(533, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("300", Vector2(626, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("375", Vector2(720, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("445", Vector2(815, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("480", Vector2(903, m_vWorldSize.y + 69), Colors::White);
		  }
		  else {
			  m_pRenderer->Draw(eSprite::TowerCursor, Vector2((m_vWorldSize.x + 54), m_vWorldSize.y - 542));
			  m_pRenderer->Draw(eSprite::TowerNumber, Vector2(m_vWorldSize.x + 55, m_vWorldSize.y / 2.0f));
			  m_pRenderer->DrawScreenText("515", Vector2(255, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("600", Vector2(348, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("675", Vector2(439, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("750", Vector2(535, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("825", Vector2(628, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("875", Vector2(720, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("930", Vector2(812, m_vWorldSize.y + 69), Colors::White);
			  m_pRenderer->DrawScreenText("995", Vector2(905, m_vWorldSize.y + 69), Colors::White);
		  }
	  }
	  WaveProgessDesc.m_nCurrentFrame = 1;
	  if (pWave->getRemainingCount() == 0) {
		  WaveProgessDesc.m_fXScale = 0;
	  }
	  else {
		  WaveProgessDesc.m_fXScale = pWave->getRemainingCount() / (float)pWave->getTotalCount();
	  }
	  WaveProgessDesc.m_vPos = Vector2(506, m_vWorldSize.y + 23);

	  m_pRenderer->Draw(&WaveProgessDesc);
	  m_pRenderer->Draw(eSprite::MapBorder, Vector2(m_vWorldSize.x / 2.0f, m_vWorldSize.y / 2.0f));
  }

  if (Menus[4]) {
	  m_pRenderer->Draw(eSprite::GameOver, Vector2(m_vWorldSize.x / 2.0f, m_vWorldSize.y / 2.0f));
	  m_pRenderer->DrawScreenText("Game Over", Vector2(m_vWorldSize.x / 2.0f + 18, m_vWorldSize.y / 2.0f - 9), Colors::Black);
	  m_pRenderer->DrawScreenText("Retry?", Vector2(m_vWorldSize.x / 2.0f - 12, m_vWorldSize.y / 2.0f + 61), Colors::Black);
	  m_pRenderer->DrawScreenText("Quit?", Vector2(m_vWorldSize.x / 2.0f + 138, m_vWorldSize.y / 2.0f + 61), Colors::Black);
	  m_pRenderer->DrawScreenText("Game Over", Vector2(m_vWorldSize.x / 2.0f + 20, m_vWorldSize.y / 2.0f - 10), Colors::Red);
	  m_pRenderer->DrawScreenText("Retry?", Vector2(m_vWorldSize.x / 2.0f - 10, m_vWorldSize.y / 2.0f + 60), Colors::Red);
	  m_pRenderer->DrawScreenText("Quit?", Vector2(m_vWorldSize.x / 2.0f + 140, m_vWorldSize.y / 2.0f + 60), Colors::Red);
	  m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
  }

  m_pRenderer->EndFrame(); //required after rendering
} //RenderFrame

/// Make the camera follow the player, but don't let it get too close to the
/// edge unless the world is smaller than the window, in which case we just
/// center everything.

void CGame::FollowCamera(){
  if(m_pPlayer == nullptr)return; //safety

  Vector3 vCameraPos(m_pPlayer->m_vPos); //player position

  if (Menus[0] || Menus[1] || Menus[2] || Menus[3]) {
      vCameraPos.x = m_nWinWidth / 2.0f; // center camera horizontally
      vCameraPos.y = m_nWinHeight / 2.0f; // center camera vertically
  }
  else {
      vCameraPos.x = m_vWorldSize.x / 2.0f; // center camera horizontally
      vCameraPos.y = m_vWorldSize.y / 2.0f; // center camera vertically
  }
  								
  m_pRenderer->SetCameraPos(vCameraPos); //camera to player
} //FollowCamera

/// This function will be called regularly to process and render a frame
/// of animation, which involves the following. Handle keyboard input.
/// Notify the audio player at the start of each frame so that it can prevent
/// multiple copies of a sound from starting on the same frame.  
/// Move the game objects. Render a frame of animation. 

void CGame::ProcessFrame(){
  KeyboardHandler(); //handle keyboard input
  ControllerHandler(); //handle controller input
  m_pAudio->BeginFrame(); //notify audio player that frame has begun
  
  m_pTimer->Tick([&]() { //all time-dependent function calls should go here
	m_pObjectManager->move(); //move all objects
	FollowCamera(); //make camera follow player

	for (int i = 0; i < baseTowers.size(); i++) {
		if (eCounter >= 0) {
			if (baseTowers[i] == NULL) {
				delete baseTowers[i];
			}
			baseTowers[i]->move();
		}
	}
	
	int TSize = baseTowers.size();
	if (TSize > 0) {
		for (int i = 0; i < TSize; i++) {
			if (baseTowers[i]->GetDeletionStatus() == true) {
				baseTowers.erase(baseTowers.begin() + i);
				TSize = baseTowers.size();
			}
		}
	}

    m_pParticleEngine->step(); //advance particle animation
  });

  RenderFrame(); //render a frame of animation
  ProcessGameState(); //check for end of game
} //ProcessFrame

/// Take action appropriate to the current game state. If the game is currently
/// playing, then if the player has been killed or all turrets have been
/// killed, then enter the wait state. If the game has been in the wait
/// state for longer than 3 seconds, then restart the game.

void CGame::ProcessGameState(){
  static float t = 0; //time at start of game

  //SET THIS UP TO WORK WITH LIVES
  switch(m_eGameState){
    case eGameState::Playing:
		if (pWave->getRemainingCount() == 0) {
			WaveInProg = false;
		}
		else {
			WaveInProg = true;
		}

		if (AutoSpawn && AutoSpawnInProg && !WaveInProg && waveDelayCounter == waveDelay) {
			pWave->nextWave(pMap->getStartPoint());
			waveDelayCounter = 0;
		}
		else {
			if (!WaveInProg) {
				if (waveDelayCounter >= waveDelay) {
					waveDelayCounter = 0;
				}
				else {
					waveDelayCounter++;
				}
			}
		}

		if(spawnDelayCounter == spawnDelay){
			pWave->spawnWave();
			spawnDelayCounter = 0;
		}
		else {
			spawnDelayCounter++;
		}
      //IF LIVES == 0
      if(stoi(m_pPlayer->GetLives()) <= 0){
		if (!Menus[4]) {
		  m_eGameState = eGameState::Gameover;
		  Menus[4] = true;
		  MenuButtonNums[4] = 0;
		  cursorPos = Vector2(m_nWinWidth / 2 - 230, m_nWinHeight / 2 - 83);
		}
        t = m_pTimer->GetTime(); //start wait timer
      } //if
      break;

    case eGameState::Waiting:
      break;
  } //switch
} //CheckForEndOfGame

void CGame::DrawVariablesToScreen() {
	const Vector2 CurrentCurrency(1025.0f, 5.0f);
	const Vector2 Lives(875.0f, 5.0f);
    const Vector2 WaveNum(225.0f, 5.0f);

	int enemyCount = m_pObjectManager->GetNumEnemies();
	std::string enemyAmount = to_string(enemyCount);

	m_pRenderer->DrawScreenText(m_pPlayer->GetCurrency().c_str(), CurrentCurrency, Colors::DeepSkyBlue);
	m_pRenderer->DrawScreenText(m_pPlayer->GetLives().c_str(), Lives, Colors::Red);
	m_pRenderer->DrawScreenText(to_string(pWave->getWaveNum()).c_str(), WaveNum, Colors::DarkSeaGreen);
}

bool CGame::CheckTile() {
	if (m_pTileManager->GetTile(m_pPlayer->GetXPos(), m_pPlayer->GetYPos()) == 'T') {
		return true;
	}
	else {
		return false;
	}
}

bool CGame::CheckExistingTower(int x, int y) {
	for (int i = 0; i < baseTowers.size(); i++) {
		if (baseTowers[i]->GetXPos() == x && baseTowers[i]->GetYPos() == y) {
			return true;
		}
	}
	return false;
}
