#pragma once
#include "GameEngine\Util\TextureManager.h"

template<typename AllShared, typename TypeShared, const unsigned int TypeCount>
struct Flyweight {
	static TypeShared s_typeShared[TypeCount];
	static AllShared s_allShared;
};

template<typename AllShared, typename TypeShared, const unsigned int TypeCount>
TypeShared Flyweight<AllShared, TypeShared, TypeCount>::s_typeShared[TypeCount];

template<typename AllShared, typename TypeShared, const unsigned int TypeCount>
AllShared Flyweight<AllShared, TypeShared, TypeCount>::s_allShared;

struct TileAllShared {
	unsigned int m_width;
	unsigned int m_height;
};
struct TileTypeShared {
	GameEngine::eTexture::type  m_texture;
	sf::Color m_color = sf::Color::Transparent;//Placeholder until we have textures.
};

enum TileType : unsigned int {
	DEFAULT = 0,
	GRASS,
	WATER,
	DIRT,
	NUM_TYPES
};

class Tile : public Flyweight<TileAllShared, TileTypeShared, TileType::NUM_TYPES> {
public:

private:

};

class Map {
public:
	static Map& getInstance();

	TileType getTileType(unsigned int x, unsigned int y);
	void render();

private:
	Map();
	~Map();
};