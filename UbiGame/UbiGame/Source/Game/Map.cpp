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
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
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

eTileType Map::getTileType(unsigned int x, unsigned int y)
{
	assert(x > 0 && y > 0 && x < g_cols && y < g_rows);
	return static_cast<eTileType>(g_tiles[y][x]);
}

GameEngine::eTexture::type Map::getTileTexture(unsigned int x, unsigned int y)
{
	return getTypeShared(x, y).m_texture;
}

sf::Color Map::getTileColor(unsigned int x, unsigned int y)
{
	return getTypeShared(x, y).m_color;
}

sf::Vector2u Map::getTilePosition(unsigned int x, unsigned int y)
{
	//Do this just to ensure we don't go out of bounds.
	getTileType(x, y);
	return sf::Vector2u{ Tile::s_allShared.m_width * x, Tile::s_allShared.m_height * y };
}

//Call this at the start of MainGame::Update().
void Map::render()
{
	const TileAllShared& allShared = Tile::s_allShared;
	GameEngine::Entity entity;
	GameEngine::SpriteRenderComponent& renderer = *static_cast<GameEngine::SpriteRenderComponent*>
		(entity.AddComponent<GameEngine::SpriteRenderComponent>());
	entity.SetSize(sf::Vector2f{ (float)allShared.m_width, (float)allShared.m_height });
	for (unsigned int i = 0; i < g_rows; i++) {
		for (unsigned int j = 0; j < g_cols; j++) {
			//Get tile position and texture information, render accordingly.
			entity.SetPos((sf::Vector2f)getTilePosition(j, i));
			//renderer.SetTexture(getTileTexture(j, i));
			renderer.SetFillColor(getTileColor(j, i));
			renderer.Render(const_cast<sf::RenderTarget*>(GameEngine::GameEngineMain::GetInstance()->getRenderTarget()));
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

inline TileTypeShared& Map::getTypeShared(unsigned int x, unsigned int y)
{
	return Tile::s_typeShared[getTileType(x, y)];
}
