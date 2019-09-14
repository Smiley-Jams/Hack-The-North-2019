#pragma once
#include "GameEngine\Util\TextureManager.h"

enum TileType : unsigned int {
	DEFAULT = 0,
	GRASS,
	NUM_TYPES
};

//Can you have nested inheritance? I don't think so, but we could namespace this to indicate grouping.
struct Flyweight {
	struct IAllShared {};
	struct ITypeShared {};
};

//Things specific to an instance of a tile.
struct Tile {
	//Things common between ALL tiles.
	struct AllShared {
		unsigned int m_width;
		unsigned int m_height;
	};
	static AllShared s_allShared;

	//Things common between each type of tile.
	struct TypeShared {
		GameEngine::eTexture::type  m_texture;
		sf::Color m_color = sf::Color::Transparent;//Placeholder until we have textures.
	};
	static TypeShared s_typeShared[TileType::NUM_TYPES];

	//*Insert instance-specific attributes here*

};

Tile::AllShared Tile::s_allShared;
Tile::TypeShared Tile::s_typeShared[TileType::NUM_TYPES];

class Map {
public:
	static Map& getInstance();

	TileType getTileType(unsigned int x, unsigned int y);
	void render();

private:
	Map();
	~Map();
};