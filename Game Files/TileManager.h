/// \file TileManager.h
/// \brief Interface for the tile manager CTileManager.

#ifndef __L4RC_GAME_TILEMANAGER_H__
#define __L4RC_GAME_TILEMANAGER_H__

#include <vector>

#include "Common.h"
#include "Settings.h"
#include "Sprite.h"
#include "GameDefines.h"

/// \brief The tile manager.
///
/// The tile manager is responsible for the tile-based background.

class CTileManager: 
  public CCommon, 
  public LSettings
{
  private:
    size_t m_nWidth = 0; ///< Number of tiles wide.
    size_t m_nHeight = 0; ///< Number of tiles high.

    float m_fTileSize = 0.0f; ///< Tile width and height.

    char** m_chMap = nullptr; ///< The level map.

    std::vector<BoundingBox> m_vecWalls; ///< AABBs for the walls.
    std::vector<Vector2> m_vecTurrets; ///< Turret positions.
    Vector2 m_vPlayer; ///< Player location.

    void MakeBoundingBoxes(); ///< Make bounding boxes for walls.

  public:
    CTileManager(size_t); ///< Constructor.
    ~CTileManager(); ///< Destructor.

    void LoadEmptyMap(char** customMap);
    void LoadMap(char** customMap);
    void LoadMap(char*); ///< Load a map.
    void Draw(eSprite); ///< Draw the map with a given tile.
    void DrawBoundingBoxes(eSprite); ///< Draw the bounding boxes.
    void GetObjects(std::vector<Vector2>&, Vector2&); ///< Get objects.

    const bool Visible(const Vector2&, const Vector2&, float) const; ///< Check visibility.
    const bool CollideWithWall(BoundingSphere, Vector2&, float&) const; ///< Object-wall collision test.

	char GetTile(int x, int y);

	void LoadMapFromImageFile(char*); ///< Load map
}; //CTileManager

#endif //__L4RC_GAME_TILEMANAGER_H__