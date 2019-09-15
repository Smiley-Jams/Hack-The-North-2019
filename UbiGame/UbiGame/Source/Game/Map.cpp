#include "Map.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

#include <cassert>
#include <cstdio>
#include <fstream>

#include "json.hpp"
using json = nlohmann::json;

// MAPS ARE HARD CODED TO BE 16 x 16
namespace {
	const unsigned int g_rows = 16;
	const unsigned int g_cols = 16;
	unsigned int g_tiles[g_rows][g_cols];
	TileResource g_resources[g_rows][g_cols];
}

Map& Map::getInstance()
{
	static Map map;
	return map;
}

eTileType Map::getTileType(unsigned int x, unsigned int y)
{
	assert(x >= 0 && y >= 0 && x < g_cols && y < g_rows);
	return static_cast<eTileType>(g_tiles[y][x]);
}

sf::Vector2u Map::getTilePosition(unsigned int x, unsigned int y)
{
	//Do this just to ensure we don't go out of bounds.
	getTileType(x, y);
	return sf::Vector2u{ Tile::s_allShared.m_width * x, Tile::s_allShared.m_height * y };
}

void Map::loadMap(const std::string& path)
{
	std::ifstream map(path);
	if (map.is_open())
	{
		json map_data;
		map >> map_data;

		try
		{
			for (int y = 0; y < g_rows; ++y)
			{
				for (int x = 0; x < g_cols; ++x)
				{
					g_tiles[y][x] = map_data["tiles"][y * g_rows + x];
					g_resources[y][x].m_wood = map_data["resources"][y * g_rows + x]["wood"];
					g_resources[y][x].m_ore  = map_data["resources"][y * g_rows + x]["ore"];
					g_resources[y][x].m_wool = map_data["resources"][y * g_rows + x]["wool"];
				}
			}
		}
		catch (std::exception& e)
		{
			// ERROR
		}
	}
	else
	{
		// ERROR
	}
}

// Call this at the start of MainGame::Update().
void Map::render()
{
	sf::RenderTarget * target = const_cast<sf::RenderTarget*>(GameEngine::GameEngineMain::GetInstance()->getRenderTarget());
	const TileAllShared& allShared = Tile::s_allShared;
	for (unsigned int i = 0; i < g_rows; i++) {
		for (unsigned int j = 0; j < g_cols; j++) {
			getTypeShared(j, i).m_sprite.setPosition((sf::Vector2f(getTilePosition(j, i))));
			target->draw(getTypeShared(j, i).m_sprite);
		}
	}
}

Map::Map()
{
	//Define different globally shared tile attributes here.
	TileAllShared& allShared = Tile::s_allShared;
	// allShared.m_width = GameEngine::GameEngineMain::WINDOW_WIDTH / g_cols;
	// allShared.m_height = GameEngine::GameEngineMain::WINDOW_HEIGHT / g_rows;
	allShared.m_width = 128;
	allShared.m_height = 128;

	//Define and wire different type-shared tile attributes here.
	Tile::s_typeShared[GRASS].m_sprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Tile_grass));
	Tile::s_typeShared[FOREST].m_sprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Tile_forest));
	Tile::s_typeShared[MOUNTAIN].m_sprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Tile_mountain));

	loadMap();
}

Map::~Map()
{
}

inline TileTypeShared& Map::getTypeShared(unsigned int x, unsigned int y)
{
	return Tile::s_typeShared[getTileType(x, y)];
}
