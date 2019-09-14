#include "Map.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include <cassert>

namespace {
	const unsigned int g_rows = 16;
	const unsigned int g_cols = 16;
	/*TileType*/unsigned int g_tiles[g_rows][g_cols] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
}

Map& Map::getInstance()
{
	static Map map;
	return map;
}

TileType Map::getTileType(unsigned int x, unsigned int y)
{
	assert(x > 0 && y > 0 && x < g_cols && y < g_rows);
	return static_cast<TileType>(g_tiles[y][x]);
}

//Call this at the start of MainGame::Update().
void Map::render()
{
	GameEngine::Entity entity;
	auto renderer = entity.AddComponent<GameEngine::SpriteRenderComponent>();
	sf::Vector2f tilePosition(0.0f, 0.0f);
	for (unsigned int i = 0; i < g_rows; i++) {
		for (unsigned int j = 0; j < g_cols; j++) {
			//Get tile position and texture information, render accordingly.
		}
	}
}

Map::Map()
{
	//Define different globally shared tile attributes here.
	TileAllShared& allShared = Tile::s_allShared;
	allShared.m_width = GameEngine::GameEngineMain::WINDOW_WIDTH;
	allShared.m_height = GameEngine::GameEngineMain::WINDOW_HEIGHT;

	//Define and wire different type-shared tile attributes here.
	TileTypeShared grass = { GameEngine::eTexture::Grass, sf::Color::Green };
	TileTypeShared water = { GameEngine::eTexture::Water, sf::Color::Blue };
	TileTypeShared dirt = { GameEngine::eTexture::Dirt, sf::Color::Yellow };

	Tile::s_typeShared[GRASS] = grass;
	Tile::s_typeShared[WATER] = water;
	Tile::s_typeShared[DIRT] = dirt;
}

Map::~Map()
{
}
