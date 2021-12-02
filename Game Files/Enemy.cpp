#include "Enemy.h"

// Using turret as a temp value
CEnemy::CEnemy(int type, const Vector2& p) : CObject(eSprite::EnemyS, p)
{
	m_fRadius = 10;
	m_bStatic = false;
	m_bIsTarget = true;

	EnemyType = type;

	if (m_bNormalAssets) {
		m_nSpriteIndex = UINT(eSprite::EnemyS);
	}
	else {
		m_nSpriteIndex = UINT(eSprite::Student);
	}
	m_nCurrentFrame = EnemyType;

	if (pWave->getWaveNum() < 3)
	{
		EnemyHealth = 1.0f;
	}
	else
	{
		//do cases for 0-23 and this is where health can be set when enemy is created
		switch (EnemyType) {
		// Enemy variant 0
		case 0:
			EnemyHealth = EnemyHealth;
			EnemyWorth = EnemyWorth * 0.5f;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 1
		case 1:
			EnemyHealth = EnemyHealth + 1;
			EnemyWorth = EnemyWorth;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 2
		case 2:
			EnemyHealth = EnemyHealth + 2;
			EnemyWorth = EnemyWorth + 1;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 3
		case 3:
			EnemyHealth = EnemyHealth + 3;
			EnemyWorth = EnemyWorth + 2;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 4
		case 4:
			EnemyHealth = EnemyHealth + 4;
			EnemyWorth = EnemyWorth + 3;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 5
		case 5:
			EnemyHealth = EnemyHealth + 5;
			EnemyWorth = EnemyWorth + 3;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 6
		case 6:
			EnemyHealth = EnemyHealth + 6;
			EnemyWorth = EnemyWorth + 3;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 20) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 35) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 7
		case 7:
			EnemyHealth = EnemyHealth + 7;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 20) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 35) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 8
		case 8:
			EnemyHealth = EnemyHealth + 9;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 40) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 60) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 9
		case 9:
			EnemyHealth = EnemyHealth + 11;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			break;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 5;
			}
		// Enemy variant 10
		case 10:
			EnemyHealth = EnemyHealth + 15;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 11
		case 11:
			EnemyHealth = EnemyHealth + 17;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 5;
			}
			break;
		// Enemy variant 12
		case 12:
			EnemyHealth = EnemyHealth + 20;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 13
		case 13:
			EnemyHealth = EnemyHealth + 21;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 14
		case 14:
			EnemyHealth = EnemyHealth + 25;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 15
		case 15:
			EnemyHealth = EnemyHealth + 30;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 16
		case 16:
			EnemyHealth = EnemyHealth + 40;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 17
		case 17:
			EnemyHealth = EnemyHealth + 50;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 18
		case 18:
			EnemyHealth = EnemyHealth + 60;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 19
		case 19:
			EnemyHealth = EnemyHealth + 70;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 20
		case 20:
			EnemyHealth = EnemyHealth + 80;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			break;
		// Enemy variant 21
		case 21:
			EnemyHealth = EnemyHealth + 90;
			EnemyWorth = EnemyWorth + 6;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += 10;
			}
			break;
		// Enemy variant 22
		case 22:
			EnemyHealth = EnemyHealth + 120;
			EnemyWorth = EnemyWorth + 7;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += 10;
			}
			break;
		// Enemy variant 23
		case 23:
			EnemyHealth = EnemyHealth + 140;
			EnemyWorth = EnemyWorth + 8;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 40) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 80) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += 20;
			}
			break;
		// Default case
		default:
			EnemyHealth = EnemyHealth;
			EnemyWorth = EnemyWorth;
			EnemyMoveSpeed = EnemyMoveSpeed;
			break;
		}
	}
}

void CEnemy::move()
{
	if (pathIndex == 0)
	{
		m_vPos = GetPos(pMap->getPath()[pathIndex]);
		eTarget = m_vPos;
	}

	if (m_vPos == eTarget)
	{
		moveCounter = 0;
		pathIndex++;
		if (pathIndex < pMap->getPath().size())
			eTarget = GetPos(pMap->getPath()[pathIndex]);
		else
		{
			if(!m_bGodMode) {
				m_pPlayer->RemoveLives(EnemyHealth);
				m_pAudio->play(eSound::lifeLost);
			}
			m_bDead = true;
			pWave->decEnemyRemCount();
		}
	}
	else
	{ 
		moveCounter++;
		if (eTarget.x < m_vPos.x)
		{
			m_vPos.x = m_vPos.x - EnemyMoveSpeed;
		}
		else if (eTarget.x > m_vPos.x)
		{
			m_vPos.x = m_vPos.x + EnemyMoveSpeed;
		}
		else if (eTarget.y < m_vPos.y)
		{
			m_vPos.y = m_vPos.y - EnemyMoveSpeed;
		}
		else if (eTarget.y > m_vPos.y)
		{
			m_vPos.y = m_vPos.y + EnemyMoveSpeed;
		}
	}
}

// Really wonky numbers to account for pixel measurements
const Vector2& CEnemy::GetPos(pair<int, int> ePos)
{
	return Vector2((ePos.second) * 62 + 31, (9 - ePos.first) * 62 - 31);
}

bool CEnemy::getIsDead()
{
	return m_bDead;
}

void CEnemy::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {

	if (m_bNormalAssets) {
		m_nSpriteIndex = UINT(eSprite::EnemyS);
	}
	else {
		m_nSpriteIndex = UINT(eSprite::Student);
	}

	m_nCurrentFrame = EnemyType;

	if (pObj)
	{
		if ((pObj->m_nSpriteIndex == (UINT)eSprite::Bullet) || (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet2)
			|| (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet3) || (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet4)
			|| (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet5) || (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet6)
			|| (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet7) || (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet8)
			|| (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet9) || (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet10)
			|| (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet11) || (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet12)
			|| (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet13) || (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet14)
			|| (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet15) || (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet16)
			|| (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet17)
			&& !(pObj->m_nSpriteIndex == (UINT)eSprite::Player))
		{
			// Shot by tower 1 - Basic
			if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet)
			{
				EnemyHealth = EnemyHealth - 1;
			}
			// Shot by tower 2 - Fast shot
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet2)
			{
				EnemyHealth = EnemyHealth - 1;
			}
			// Shot by tower 3 - Slow, fast, faster
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet3)
			{
				EnemyHealth = EnemyHealth - 1;
			}
			// Shot by tower 4 - Upwards cross trace
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet4)
			{
				EnemyHealth = EnemyHealth - 2;
			}
			// Shot by tower 5 - Double shot
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet5)
			{
				EnemyHealth = EnemyHealth - 2;
			}
			// Shot by tower 6 - Octo
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet6)
			{
				EnemyHealth = EnemyHealth - 1;
			}
			// Shot by tower 7 - Faster shot
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet7)
			{
				EnemyHealth = EnemyHealth - 3;
			}
			// Shot by tower 8 - Triple shot
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet8)
			{
				EnemyHealth = EnemyHealth - 2;
			}
			// Shot by tower 9 - Strong shot
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet9)
			{
				EnemyHealth = EnemyHealth - 5;
			}
			// Shot by tower 10 - Hexashot
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet10)
			{
				EnemyHealth = EnemyHealth - 1;
			}
			// Shot by tower 11 - Essence
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet11)
			{
				EnemyHealth = EnemyHealth - 1;
			}
			// Shot by tower 12 - Cross shot
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet12)
			{
				EnemyHealth = EnemyHealth - 2;
			}
			// Shot by tower 13 - Lucly Life
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet13)
			{
				EnemyHealth = EnemyHealth - 1;
			}
			// Shot by tower 14 - Octo double trace
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet14)
			{
				EnemyHealth = EnemyHealth - 2;
			}
			// Shot by tower 15 - Fast, slow, & strong
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet15)
			{
				EnemyHealth = EnemyHealth - 5;
			}
			// Shot by tower 16 - the best
			else if (pObj->m_nSpriteIndex == (UINT)eSprite::Bullet16)
			{
				EnemyHealth = EnemyHealth - 5;
			}
			if(checkDead())
				m_pPlayer->AddCurrency(EnemyWorth);

			bool bStatic = false;
			if (m_bDead)return; //dead, bail out
		}
	}
} //CollisionResponse

void CEnemy::kill()
{
	CObject::m_bDead = true;
	//delete this;
}

bool CEnemy::checkDead()
{
	if (EnemyHealth <= 0)
	{
		m_pAudio->play(eSound::Boom);
		m_bDead = true;
		pWave->decEnemyRemCount();
		DeathFX();
		return true;
	}
	return false;
}