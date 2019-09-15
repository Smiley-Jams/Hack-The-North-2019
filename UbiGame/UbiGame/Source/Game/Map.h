#pragma once

#include <SFML/Graphics.hpp>

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

//Data common to all tiles.
struct TileAllShared {
	unsigned int m_width;
	unsigned int m_height;
};

//Data common to type of tile.
struct TileTypeShared {
	sf::Sprite m_sprite;
};

enum eTileType : unsigned int {
	DEFAULT = 0,
	GRASS,
	FOREST,
	MOUNTAIN,
	NUM_TYPES
};

class Tile : public Flyweight<TileAllShared, TileTypeShared, eTileType::NUM_TYPES> {
public:

private:

};

class Map {
public:
	static Map& getInstance();

	//The price we pay for optimal memory saving is having to make lookup functions rather than having public members.
	eTileType getTileType(unsigned int x, unsigned int y);
	// GameEngine::eTexture::type getTileTexture(unsigned int x, unsigned int y);
	// sf::Color getTileColor(unsigned int x, unsigned int y);
	sf::Vector2u getTilePosition(unsigned int x, unsigned int y);

	void render();

private:
	Map();
	~Map();

	inline TileTypeShared& getTypeShared(unsigned int x, unsigned int y);
};