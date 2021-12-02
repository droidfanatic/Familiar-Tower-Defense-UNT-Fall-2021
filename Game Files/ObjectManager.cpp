/// \file ObjectManager.cpp
/// \brief Code for the the object manager class CObjectManager.

#include "ObjectManager.h"
#include "ComponentIncludes.h"

#include "Player.h"
#include "Bullet.h"
#include "ParticleEngine.h"
#include "Helpers.h"
#include "GameDefines.h"
#include "TileManager.h"
#include "Enemy.h"

/// Create an object and put a pointer to it at the back of the object list
/// `m_stdObjectList`, which it inherits from `LBaseObjectManager`.
/// \param t Sprite type.
/// \param pos Initial position.
/// \return Pointer to the object created.

CObject* CObjectManager::create(eSprite t, const Vector2& pos){
  CObject* pObj = nullptr;

  switch(t){ //create object of type t
    case eSprite::Player:  pObj = new CPlayer(pos); break;
    case eSprite::Bullet:  pObj = new CBullet(eSprite::Bullet,  pos); break;
    case eSprite::Bullet2: pObj = new CBullet(eSprite::Bullet2, pos); break;
	case eSprite::Bullet3: pObj = new CBullet(eSprite::Bullet3, pos); break;
	case eSprite::Bullet4: pObj = new CBullet(eSprite::Bullet4, pos); break;
	case eSprite::Bullet5: pObj = new CBullet(eSprite::Bullet5, pos); break;
	case eSprite::Bullet6: pObj = new CBullet(eSprite::Bullet6, pos); break;
	case eSprite::Bullet7: pObj = new CBullet(eSprite::Bullet7, pos); break;
	case eSprite::Bullet8: pObj = new CBullet(eSprite::Bullet8, pos); break;
	case eSprite::Bullet9: pObj = new CBullet(eSprite::Bullet9, pos); break;
	case eSprite::Bullet10: pObj = new CBullet(eSprite::Bullet10, pos); break;
	case eSprite::Bullet11: pObj = new CBullet(eSprite::Bullet11, pos); break;
	case eSprite::Bullet12: pObj = new CBullet(eSprite::Bullet12, pos); break;
	case eSprite::Bullet13: pObj = new CBullet(eSprite::Bullet13, pos); break;
	case eSprite::Bullet14: pObj = new CBullet(eSprite::Bullet14, pos); break;
	case eSprite::Bullet15: pObj = new CBullet(eSprite::Bullet15, pos); break;
	case eSprite::Bullet16: pObj = new CBullet(eSprite::Bullet16, pos); break;
	case eSprite::Bullet17: pObj = new CBullet(eSprite::Bullet17, pos); break;
    default: pObj = new CObject(t, pos);
  } //switch

  m_stdObjectList.push_back(pObj); //push pointer onto object list
  return pObj; //return pointer to created object
} //create

CObject* CObjectManager::createEnemy(const Vector2& pos, int type) {
    CObject* pObj = nullptr;

    pObj = new CEnemy(type, pos);

    m_stdObjectList.push_back(pObj); //push pointer onto object list
    return pObj; //return pointer to created object
} //create

/// Draw the tiled background and the objects in the object list.

void CObjectManager::draw(int tileColor){
  switch (tileColor) { //select which frame of the tile sprite is to be drawn
    case 0 : m_pTileManager->Draw(eSprite::BlueTile); break; //draw BlueTiled background
    case 1 : m_pTileManager->Draw(eSprite::BrownTile); break; //draw BrownTiled background
    case 2 : m_pTileManager->Draw(eSprite::GrayTile); break; //draw GrayTiled background
    default: m_pTileManager->Draw(eSprite::RedTile); break; //draw RedTiled background
  } //switch

  LBaseObjectManager::draw();
} //draw

/// Perform collision detection and response for each object with the world
/// edges and for all objects with another object, making sure that each pair
/// of objects is processed only once.

void CObjectManager::BroadPhase(){
  LBaseObjectManager::BroadPhase(); //collide with other objects

  //collide with walls

  for(CObject* pObj: m_stdObjectList){ //for each object
      if (!pObj->m_bDead) { //for each non-dead object, that is
          if (pObj->isBullet() && (pObj->m_vPos.x > 992 || pObj->m_vPos.x < 0 || pObj->m_vPos.y > 558 || pObj->m_vPos.y < 0)) {
              pObj->m_bDead = true;
          }
          for (int i = 0; i < 2; i++) { //can collide with 2 edges simultaneously
              Vector2 norm; //collision normal
              float d = 0; //overlap distance
              BoundingSphere s(Vector3(pObj->m_vPos), pObj->m_fRadius);

              if (m_pTileManager->CollideWithWall(s, norm, d)) //collide with wall
                  pObj->CollisionResponse(norm, d); //respond 
          } //for
      }
  } //for
} //BroadPhase

/// Perform collision detection and response for a pair of objects. Makes
/// use of the helper function Identify() because this function may be called
/// with the objects in an arbitrary order.
/// \param p0 Pointer to the first object.
/// \param p1 Pointer to the second object.

void CObjectManager::NarrowPhase(CObject* p0, CObject* p1){
  Vector2 vSep = p0->m_vPos - p1->m_vPos; //vector from *p1 to *p0
  const float d = p0->m_fRadius + p1->m_fRadius - vSep.Length(); //overlap

  if(d > 0.0f){ //bounding circles overlap
    vSep.Normalize(); //vSep is now the collision normal

    p0->CollisionResponse( vSep, d, p1); //this changes separation of objects
    p1->CollisionResponse(-vSep, d, p0); //same separation and opposite normal
  } //if
} //NarrowPhase

/// Create a bullet object and a flash particle effect. It is assumed that the
/// object is round and that the bullet appears at the edge of the object in
/// the direction that it is facing and continues moving in that direction.
/// \param pObj Pointer to an object.
/// \param bullet Sprite type of bullet.

void CObjectManager::FireGun(CObject* pObj, int type, eSprite bullet){
    const Vector2 view = pObj->GetViewVector(); //firing object view vector
    const float w0 = 0.5f * m_pRenderer->GetWidth(pObj->m_nSpriteIndex); //firing object width
    const float w1 = m_pRenderer->GetWidth(bullet); //bullet width
    const Vector2 pos = pObj->m_vPos + (w0 + w1) * view; //bullet initial position

    const Vector2 norm = VectorNormalCC(view); //normal to view direction
    const float m = 2.0f * m_pRandom->randf() - 1.0f; //random deflection magnitude
    const Vector2 deflection = 0.01f * m * norm; //random deflection
	CObject* pBullet; //first bullet creation
	
	if (pObj == m_pPlayer) {
		Vector2 pPos = m_pPlayer->m_vPos;
		pBullet = create(bullet, pPos);
	}
	else {
		pBullet = create(bullet, pos);
	}

	//Creation of all bullets for switch case handling
	CObject* pBullet2;
	CObject* pBullet3;
	CObject* pBullet4;
	CObject* pBullet5;
	CObject* pBullet6;
	CObject* pBullet7;
	CObject* pBullet8;
	CObject* pBullet9;
	CObject* pBullet10;

	int randomizer;
    
	if (type == 3) { //Creation of 2 additional bullets
		pBullet2 = create(bullet, pos);
		pBullet3 = create(bullet, pos);
	}
	if (type == 4) { //Creation of 3 additional bullets
		pBullet2 = create(bullet, pos);
		pBullet3 = create(bullet, pos);
		pBullet4 = create(bullet, pos);
	}
	if (type == 5) { //Creation of 1 additional bullet
		pBullet2 = create(bullet, pos);
	}
	if (type == 6) { //Creation of 7 additiona bullets
		pBullet2 = create(bullet, pos);
		pBullet3 = create(bullet, pos);
		pBullet4 = create(bullet, pos);
		pBullet5 = create(bullet, pos);
		pBullet6 = create(bullet, pos);
		pBullet7 = create(bullet, pos);
		pBullet8 = create(bullet, pos);
	}
	if (type == 8) { //Creation of 2 additional bullets
		pBullet2 = create(bullet, pos);
		pBullet3 = create(bullet, pos);
	}
	if (type == 10) { //Creation of 5 additional bullets
		pBullet2 = create(bullet, pos);
		pBullet3 = create(bullet, pos);
		pBullet4 = create(bullet, pos);
		pBullet5 = create(bullet, pos);
		pBullet6 = create(bullet, pos);
	}
	if (type == 12) { //Creation of 3 additional bullets
		if (pObj == m_pPlayer) {
			Vector2 pPos = m_pPlayer->m_vPos;
			pBullet2 = create(bullet, pPos);
		}
		else {
			pBullet2 = create(bullet, pos);
		}
		if (pObj == m_pPlayer) {
			Vector2 pPos = m_pPlayer->m_vPos;
			pBullet3 = create(bullet, pPos);
		}
		else {
			pBullet3 = create(bullet, pos);
		}
		if (pObj == m_pPlayer) {
			Vector2 pPos = m_pPlayer->m_vPos;
			pBullet4 = create(bullet, pPos);
		}
		else {
			pBullet4 = create(bullet, pos);
		}
	}
	if (type == 14) { //Creation of 9 additional bullets
		pBullet2 = create(bullet, pos);
		pBullet3 = create(bullet, pos);
		pBullet4 = create(bullet, pos);
		pBullet5 = create(bullet, pos);
		pBullet6 = create(bullet, pos);
		pBullet7 = create(bullet, pos);
		pBullet8 = create(bullet, pos);
		pBullet9 = create(bullet, pos);
		pBullet10 = create(bullet, pos);
	}
	
    //particle effect for gun fire
    LParticleDesc2D d;
	LParticleDesc2D d1;
	LParticleDesc2D d2;
	LParticleDesc2D d3;
	LParticleDesc2D d4;
	LParticleDesc2D d5;
	LParticleDesc2D d6;
	LParticleDesc2D d7;
	LParticleDesc2D d8;
	LParticleDesc2D d9;
	LParticleDesc2D d10;

    d.m_vPos = pos;
    d.m_vVel = pObj->m_fSpeed * view;
    d.m_fLifeSpan = 0.25f;
    d.m_fScaleInFrac = 0.4f;
    d.m_fFadeOutFrac = 0.5f;
    d.m_fMaxScale = 0.5f;

    //Switch case on tower type to determine sound, velocity, and bulelts of each tower
    switch (type) {
    //Tower 1 - Basic Tower
    case 1:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
        pBullet->m_vVelocity = pObj->m_vVelocity + 500.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Gray);
        break;
    //Tower 2 - Fast Shot Tower
    case 2:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
        pBullet->m_vVelocity = pObj->m_vVelocity + 750.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::MediumPurple);
        break;
    //Tower 3 - Slow, Fast, Faster Tower
    case 3:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		//Bullet 1
		pBullet->m_vVelocity = pObj->m_vVelocity + 500.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

		//Bullet 2
		pBullet2->m_vVelocity = pObj->m_vVelocity + 400.0f * (view + deflection);
		pBullet2->m_fRoll = pObj->m_fRoll;

		//Bullet 3
		pBullet3->m_vVelocity = pObj->m_vVelocity + 300.0f * (view + deflection);
		pBullet3->m_fRoll = pObj->m_fRoll;

		d.m_fMaxScale = 1.0f;
        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Purple);
        break;
    //Tower 4 - Upwards Cross Tower - Basic Shot, plus 3 Directional Shots (up, left, right)
    case 4:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		//Bullet 1 - Tracks Enemy like normal
		pBullet->m_vVelocity = pObj->m_vVelocity + 450.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

		//Bullet 2 - Horizontal Right Shot
		randomizer = rand() % 550 + 200;
		pBullet2->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet2->m_fRoll = pObj->m_fRoll;

		//Bullet 3 - Horizontal Left Shot
		randomizer = rand() % 550 + 200;
		pBullet3->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet3->m_fRoll = pObj->m_fRoll;

		//Bullet 4 - Vertical Shot
		randomizer = rand() % 550 + 200;
		pBullet4->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet4->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Azure);
        break;
    //Tower 5 - Double Shot Tower
    case 5:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		//Bullet 1
		randomizer = rand() % 650 + 200;
		pBullet->m_vVelocity = pObj->m_vVelocity + randomizer * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

		//Bullet 2
		randomizer = rand() % 400 + 200;
		pBullet2->m_vVelocity = pObj->m_vVelocity + randomizer * (view + deflection);
		pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Aqua);
        break;
    //Tower 6 - Octo Tower
    case 6:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		//Bullet 1 - Upwards Shot
		randomizer = rand() % 500 + 200;
		pBullet->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
        pBullet->m_fRoll = pObj->m_fRoll;

		//Bullet 2 - Downwards Shot
		randomizer = rand() % 500 + 200;
		pBullet2->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet2->m_fRoll = pObj->m_fRoll;

		//Bullet 3 - Right Shot
		randomizer = rand() % 500 + 200;
		pBullet3->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet3->m_fRoll = pObj->m_fRoll;

		//Bullet 4 - Left Shot
		randomizer = rand() % 500 + 200;
		pBullet4->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet4->m_fRoll = pObj->m_fRoll;

		//Bullet 5 - Right Upwards Diagonal Shot
		randomizer = rand() % 500 + 200;
		pBullet5->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet5->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet5->m_fRoll = pObj->m_fRoll;

		//Bullet 6 - Left Downwards Diagonal Shot
		randomizer = rand() % 500 + 200;
		pBullet6->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet6->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet6->m_fRoll = pObj->m_fRoll;

		//Bullet 7 - Right Downwards Diagonal Shot
		randomizer = rand() % 500 + 200;
		pBullet7->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet7->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet7->m_fRoll = pObj->m_fRoll;

		//Bullet 8 - Left Upwards Diagonal Shot
		randomizer = rand() % 500 + 200;
		pBullet8->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet8->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet8->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Aquamarine);
        break;
	//Tower 7 - Faster Shot Tower
    case 7:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
        pBullet->m_vVelocity = pObj->m_vVelocity + 850.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::PaleTurquoise);
        break;
	//Tower 8 - Triple Shot Tower
    case 8:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		//Bullet 1
        pBullet->m_vVelocity = pObj->m_vVelocity + 600.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

		//Bullet 2
		randomizer = rand() % 500 + 400;
		pBullet2->m_vVelocity = pObj->m_vVelocity + randomizer * (view + deflection);
		pBullet2->m_fRoll = pObj->m_fRoll;

		//Bullet 3
		randomizer = rand() % 375 + 200;
		pBullet3->m_vVelocity = pObj->m_vVelocity + randomizer * (view + deflection);
		pBullet3->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::DarkGreen);
        break;
	//Tower 9 - Strong Shot Tower
    case 9:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
        pBullet->m_vVelocity = pObj->m_vVelocity + 600.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Silver);
        break;
	//Tower 10 - Hexashot Tower
    case 10:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		//Bullet 1 - Upwards Shot
		randomizer = rand() % 500 + 200;
		pBullet->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet->m_fRoll = pObj->m_fRoll;

		//Bullet 2 - Downwards Shot
		randomizer = rand() % 500 + 200;
		pBullet2->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet2->m_fRoll = pObj->m_fRoll;

		//Bullet 3 - Right Upwards Diagonal Shot
		randomizer = rand() % 500 + 200;
		pBullet3->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet3->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet3->m_fRoll = pObj->m_fRoll;

		//Bullet 4 - Left Downwards Diagonal Shot
		randomizer = rand() % 500 + 200;
		pBullet4->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet4->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet4->m_fRoll = pObj->m_fRoll;

		//Bullet 5 - Right Downwards Diagonal Shot
		randomizer = rand() % 500 + 200;
		pBullet5->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet5->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet5->m_fRoll = pObj->m_fRoll;

		//Bullet 6 - Left Upwards Diagonal Shot
		randomizer = rand() % 500 + 200;
		pBullet6->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet6->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet6->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Goldenrod);
        break;
	//Tower 11 - Essence Tower
    case 11:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
        pBullet->m_vVelocity = pObj->m_vVelocity + 400.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::DarkGoldenrod);
        break;
	//Tower 12 - Cross Shot Tower
    case 12:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		//Bullet 1 - Upwards Shot
		randomizer = rand() % 600 + 100;
        pBullet->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
        pBullet->m_fRoll = pObj->m_fRoll;

		//Bullet 2 - Downwards Shot
		randomizer = rand() % 600 + 100;
		pBullet2->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet2->m_fRoll = pObj->m_fRoll;

		//Bullet 3 - Right Shot
		randomizer = rand() % 600 + 100;
		pBullet3->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet3->m_fRoll = pObj->m_fRoll;

		//Bullet 4 - Left Shot
		randomizer = rand() % 600 + 100;
		pBullet4->m_vVelocity.x = pObj->m_vVelocity.y + -randomizer;
		pBullet4->m_fRoll = pObj->m_fRoll;

		d.m_nSpriteIndex = (UINT)eSprite::Spark;
		if (pObj == m_pPlayer) {
			d.m_f4Tint = XMFLOAT4(Colors::Purple);
		}
		else {
			d.m_f4Tint = XMFLOAT4(Colors::Orange);
		}
		break;
	//Tower 13 - Lucky Life 13 Tower
    case 13:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
        pBullet->m_vVelocity = pObj->m_vVelocity + 300.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::DimGray);
        break;
	//Tower 14 - Octo Double Trace Tower
    case 14:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		//Bullet 1 - Tracks like normal
        pBullet->m_vVelocity = pObj->m_vVelocity + 200.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

		//Bullet 2 - Right Shot
		randomizer = rand() % 800 + 100;
		pBullet2->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet2->m_fRoll = pObj->m_fRoll;

		//Bullet 3 - Left Shot
		randomizer = rand() % 800 + 100;
		pBullet3->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet3->m_fRoll = pObj->m_fRoll;

		//Bullet 4 - Upwards Right Diagonal Shot
		randomizer = rand() % 800 + 100;
		pBullet4->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet4->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet4->m_fRoll = pObj->m_fRoll;

		//Bullet 5 - Downwards Right Diagonal Shot
		randomizer = rand() % 800 + 100;
		pBullet5->m_vVelocity.x = pObj->m_vVelocity.x + randomizer;
		pBullet5->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet5->m_fRoll = pObj->m_fRoll;

		//Bullet 6 - Upwards Left Diagonal Shot
		randomizer = rand() % 800 + 100;
		pBullet6->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet6->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet6->m_fRoll = pObj->m_fRoll;

		//Bullet 7 - Downwards Left Diagonal Shot
		randomizer = rand() % 800 + 100;
		pBullet7->m_vVelocity.x = pObj->m_vVelocity.x + -randomizer;
		pBullet7->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet7->m_fRoll = pObj->m_fRoll;

		//Bullet 8 - Upwards Shot
		randomizer = rand() % 800 + 100;
		pBullet8->m_vVelocity.y = pObj->m_vVelocity.y + randomizer;
		pBullet8->m_fRoll = pObj->m_fRoll;

		//Bullet 9 - Downwards Shot
		randomizer = rand() % 800 + 100;
		pBullet9->m_vVelocity.y = pObj->m_vVelocity.y + -randomizer;
		pBullet9->m_fRoll = pObj->m_fRoll;

		//Bullet 10
		randomizer = rand() % 800 + 100;
		pBullet10->m_vVelocity = pObj->m_vVelocity + randomizer * (view + deflection);
		pBullet10->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Pink);
        break;
	//Tower 15 - Fast, Slow, and Strong Tower
    case 15:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
        pBullet->m_vVelocity = pObj->m_vVelocity + 150.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::DeepPink);
        break;
	//Tower 16 - The Best Tower
    case 16:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
        pBullet->m_vVelocity = pObj->m_vVelocity + 700.0f * (view + deflection);
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Crimson);
        break;
	//Safety
    default:
		if (m_bGunSound == true)
			m_pAudio->play(eSound::Gun);
		pBullet->m_vVelocity = pObj->m_vVelocity * 0.0f;
        pBullet->m_fRoll = pObj->m_fRoll;

        d.m_nSpriteIndex = (UINT)eSprite::Spark;
        d.m_f4Tint = XMFLOAT4(Colors::Red);
        break;
    }
  
  m_pParticleEngine->create(d);
} //FireGun

/// Reader function for the number of turrets. 
/// \return Number of turrets in the object list.

const size_t CObjectManager::GetNumTurrets() const{
  size_t n = 0; //number of turrets
  
  for(CObject* pObj: m_stdObjectList) //for each object
    if(pObj->m_bIsTarget)
      n++;

  return n;
} //GetNumTurrets

int CObjectManager::getNumBullets() {
    return m_stdObjectList.size();
}

//Get Total Number of Enemies in ObjectList
int CObjectManager::GetNumEnemies() {
    size_t count = 0;
    for (CObject* pObj: m_stdObjectList) {
        if (pObj->m_bIsTarget) {
            count++;
        }
    }
    return count;
}

//Return the position of the first enemy available within tower radius
Vector2 CObjectManager::GetEnemyPosition(CTower* tower) {
	for (CObject* pObj : m_stdObjectList) {
		if (pObj->m_bIsTarget && m_pTileManager->Visible(tower->m_vPos, pObj->m_vPos, tower->m_fRadius)) {
			if (pObj->m_vPos.x < tower->m_vPos.x && !m_bNormalAssets) {
				tower->m_nSpriteIndex = UINT(eSprite::ParberryTowerFlipped);
			}
			else if (!m_bNormalAssets){
				tower->m_nSpriteIndex = UINT(eSprite::ParberryTower);
			}
			return pObj->m_vPos;
		}
	}
	return Vector2(-100000,-100000);
}

float CObjectManager::GetEnemyRadius() {
	float radius = 0;
	for (CObject* pObj : m_stdObjectList) {
		if (pObj->m_bIsTarget) {
			radius = pObj->m_fRadius;
			break;
		}
	}
	return radius;
}
