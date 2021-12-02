/// \file Tower.cpp
/// \brief Code for the tower object class CTower

#include "Tower.h"
#include "Common.h"
#include "Game.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "Player.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"

/// Create and initialize a tower object given its position
/// \param p Position of Tower

CTower::CTower(const Vector2& p) : CObject(eSprite::Tower, p) {
	m_bStatic = true; //towers are static
	m_bIsTarget = false;
	m_fRadius = 10;
} //constructor

CTower::CTower(int type, int i, int j, Vector2& p) : CObject(eSprite::Tower, p) {
	m_bStatic = true;
	m_bIsTarget = false;
	yPos = j;
	xPos = i;
	TowerType = type;
	desc.m_vPos = m_vPos;

	//Change Tower Sprite Index based on Type
	if (m_bNormalAssets) {
		m_nSpriteIndex = UINT(eSprite::Tower);
	}
	else {
		m_nSpriteIndex = UINT(eSprite::ParberryTower);
	}
	switch (TowerType) {
	case 1:
		m_nCurrentFrame = 0;
		m_fRadius = 150;
		m_pGunFireEvent = new LEventTimer(1.0f);
		break;
	case 2:
		m_nCurrentFrame = 1;
		m_fRadius = 140;
		m_pGunFireEvent = new LEventTimer(0.65f);
		break;
	case 3:
		m_nCurrentFrame = 2;
		m_fRadius = 150;
		m_pGunFireEvent = new LEventTimer(1.5f);
		break;
	case 4:
		m_nCurrentFrame = 3;
		m_fRadius = 250;
		m_pGunFireEvent = new LEventTimer(1.0f);
		break;
	case 5:
		m_nCurrentFrame = 4;
		m_fRadius = 300;
		m_pGunFireEvent = new LEventTimer(1.5f);
		break;
	case 6:
		m_nCurrentFrame = 5;
		m_fRadius = 150;
		m_pGunFireEvent = new LEventTimer(1.25f);
		break;
	case 7:
		m_nCurrentFrame = 6;
		m_fRadius = 100;
		m_pGunFireEvent = new LEventTimer(0.35f);
		break;
	case 8:
		m_nCurrentFrame = 7;
		m_fRadius = 235;
		m_pGunFireEvent = new LEventTimer(1.25f);
		break;
	case 9:
		m_nCurrentFrame = 8;
		m_fRadius = 350;
		m_pGunFireEvent = new LEventTimer(1.5f);
		break;
	case 10:
		m_nCurrentFrame = 9;
		m_fRadius = 275;
		m_pGunFireEvent = new LEventTimer(2.0f);
		break;
	case 11:
		m_nCurrentFrame = 10;
		m_fRadius = 300;
		m_pGunFireEvent = new LEventTimer(1.25f);
		break;
	case 12:
		m_nCurrentFrame = 11;
		m_fRadius = 150;
		m_pGunFireEvent = new LEventTimer(0.5f);
		break;
	case 13:
		m_nCurrentFrame = 12;
		m_fRadius = 250;
		m_pGunFireEvent = new LEventTimer(1.15f);
		break;
	case 14:
		m_nCurrentFrame = 13;
		m_fRadius = 300;
		m_pGunFireEvent = new LEventTimer(1.0f);
		break;
	case 15:
		m_nCurrentFrame = 14;
		m_fRadius = 400;
		m_pGunFireEvent = new LEventTimer(0.55f);
		break;
	case 16:
		m_nCurrentFrame = 15;
		m_fRadius = 500;
		m_pGunFireEvent = new LEventTimer(0.25f);
		break;
	default:
		m_nCurrentFrame = 0;
		m_fRadius = 150;
		m_pGunFireEvent = new LEventTimer(1.0f);
	}

	m_vPos = Vector2((xPos + 0.5f) * ((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * 0.5f),
		(8 - yPos + 0.5f) * ((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * 0.5f));
}

void CTower::move() {
	if (m_pPlayer) {
		const float radius = ((CTower*)m_pPlayer)->m_fRadius;
		if (m_pTileManager->Visible(m_vPos, m_pObjectManager->GetEnemyPosition(this), m_fRadius)) {
			RotateTowards(m_pObjectManager->GetEnemyPosition(this));
		}
		else {
			m_fRotSpeed = 0.0f;
		}
	}
	m_fRoll += 0.2f * m_fRotSpeed* XM_2PI * m_pTimer->GetFrameTime(); //rotate
	NormalizeAngle(m_fRoll);
}

//Look towards the enemy that passes through the radius of the tower
void CTower::RotateTowards(const Vector2& position) {
	const Vector2 v = position - m_vPos; //vector from target to tower
	const float theta = atan2f(v.y, v.x); //orientation of that vector
	float diff = m_fRoll - theta;
	NormalizeAngle(diff); //normalizing to [-pi, pi]

	float fAngleDelta = 0.05f; //allowable angle discrepancy
	float fTrackingSpeed = 2.0f; //rotation speed when tracking

	//Changing rotate speed and angle discrepancy from bullets depending on tower type
	switch (TowerType) {
	case 1:
		fAngleDelta = 0.07f;
		fTrackingSpeed = 2.0f;
		break;
	case 2:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 3.0f;
		break;
	case 3:
		fAngleDelta = 0.06f;
		fTrackingSpeed = 2.25f;
		break;
	case 4:
		fAngleDelta = 0.15f;
		fTrackingSpeed = 2.45f;
		break;
	case 5:
		fAngleDelta = 0.2f;
		fTrackingSpeed = 2.35f;
		break;
	case 6:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 3.0f;
		break;
	case 7:
		fAngleDelta = 0.04f;
		fTrackingSpeed = 2.15f;
		break;
	case 8:
		fAngleDelta = 0.04f;
		fTrackingSpeed = 2.0f;
		break;
	case 9:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 2.45f;
		break;
	case 10:
		fAngleDelta = 0.04f;
		fTrackingSpeed = 2.5f;
		break;
	case 11:
		fAngleDelta = 0.04f;
		fTrackingSpeed = 2.5f;
		break;
	case 12:
		fAngleDelta = 0.09f;
		fTrackingSpeed = 2.75f;
		break;
	case 13:
		fAngleDelta = 0.08f;
		fTrackingSpeed = 2.85f;
		break;
	case 14:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 3.0f;
		break;
	case 15:
		fAngleDelta = 0.07f;
		fTrackingSpeed = 3.0f;
		break;
	case 16:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 3.0f;
		break;
	deafult:
		fAngleDelta = 0.07f;
		fTrackingSpeed = 2.0f;
		break;
	}

	//Randomization for Tower 11
	int randomCurrencyAdd = rand() % 20 + 1;
	int randomChancePercent = rand() % 100 + 1;

	//Randomization for Tower 13
	int randomPercentLiveAdd = rand() % 100 + 1;

	if (diff > fAngleDelta)m_fRotSpeed = -fTrackingSpeed; //clockwise
	else if (diff < -fAngleDelta)m_fRotSpeed = fTrackingSpeed; //counterclockwsise
	else m_fRotSpeed = 0; //stop rotating


	if (fabsf(diff) < fAngleDelta && m_pGunFireEvent->Triggered()) {
		switch (TowerType) {
		//Tower 1
		case 1:
			m_pObjectManager->FireGun(this, 1, eSprite::Bullet);
			break;
		//Tower 2
		case 2:
			m_pObjectManager->FireGun(this, 2, eSprite::Bullet2);
			break;
		//Tower 3
		case 3:
			m_pObjectManager->FireGun(this, 3, eSprite::Bullet3);
			break;
		//Tower 4
		case 4:
			m_pObjectManager->FireGun(this, 4, eSprite::Bullet4);
			break;
		//Tower 5
		case 5:
			m_pObjectManager->FireGun(this, 5, eSprite::Bullet5);
			break;
		//Tower 6
		case 6:
			m_pObjectManager->FireGun(this, 6, eSprite::Bullet6);
			break;
		//Tower 7
		case 7:
			m_pObjectManager->FireGun(this, 7, eSprite::Bullet7);
			break;
		//Tower 8
		case 8:
			m_pObjectManager->FireGun(this, 8, eSprite::Bullet8);
			break;
		//Tower 9
		case 9:
			m_pObjectManager->FireGun(this, 9, eSprite::Bullet9);
			break;
		//Tower 10
		case 10:
			m_pObjectManager->FireGun(this, 10, eSprite::Bullet10);
			break;
		//Tower 11
		case 11:
			m_pObjectManager->FireGun(this, 11, eSprite::Bullet11);
			//This tower has a 50% chance to grant 1 Currency on every shot
			if (randomChancePercent >= 50) {
				m_pPlayer->AddCurrency(1);
			}
			randomChancePercent = rand() % 100 + 1;
			//This tower has a 5% chance to award a random amount of currency of range 1-20
			if (randomChancePercent >= 95) {
				m_pPlayer->AddCurrency(randomCurrencyAdd);
				m_pAudio->play(eSound::manaDrop);
			}
			break;
		//Tower 12
		case 12:
			m_pObjectManager->FireGun(this, 12, eSprite::Bullet12);
			break;
		//Tower 13
		case 13:
			m_pObjectManager->FireGun(this, 13, eSprite::Bullet13);
			//This tower has a 1% chance to grant to grant a life on every shot
			if (randomPercentLiveAdd == 100) {
				m_pPlayer->AddLives(1);
				m_pAudio->play(eSound::manaDrop);
			}
			break;
		//Tower 14
		case 14:
			m_pObjectManager->FireGun(this, 14, eSprite::Bullet14);
			break;
		//Tower 15
		case 15:
			m_pObjectManager->FireGun(this, 15, eSprite::Bullet15);
			break;
		//Tower 16
		case 16:
			m_pObjectManager->FireGun(this, 16, eSprite::Bullet16);
			break;
		default:
			break;
		}
	} //Rotate Towards target
}

const Vector2& CTower::GetPosition(int x, int y) {
	return Vector2(x, y);
}

int CTower::GetXPos() {
	return xPos;
}

int CTower::GetYPos() {
	return yPos;
}

void CTower::SetXPos(int x) {
	xPos = x;
}

void CTower::SetYPos(int y) {
	yPos = y;
}

Vector2 CTower::ReturnSpritePos() {
	return m_vPos;
}

void CTower::SetDeletion() {
	deleteMark = true;
}

bool CTower::GetDeletionStatus() {
	return deleteMark;
}

int CTower::GetType() {
	return TowerType;
}
