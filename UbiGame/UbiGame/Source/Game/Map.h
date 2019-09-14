#pragma once
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
enum TileType : unsigned int {
	DEFAULT = 0,
	NUM_TYPES
};

struct TileShared {
	unsigned int m_width;
	unsigned int m_height;
};

struct TileUnique {
};

class Map {
public:
	Map& getInstance() {
		static Map map;
		return map;
	}

	TileType getTileType(unsigned int x, unsigned int y);
	void render();

private:
	Map() {}
	~Map() {}

	GameEngine::SpriteRenderComponent* m_renderer = nullptr;
};