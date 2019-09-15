#include "Map.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/Util/CameraManager.h"

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
	GameEngine::GameEngineMain& engine = *GameEngine::GameEngineMain::GetInstance();
	sf::RenderTarget * target = const_cast<sf::RenderTarget*>(engine.getRenderTarget());
	const TileAllShared& allShared = Tile::s_allShared;
	GameEngine::CameraManager& camera = *GameEngine::CameraManager::GetInstance();
	for (unsigned int i = 0; i < g_rows; i++) {
		for (unsigned int j = 0; j < g_cols; j++) {
			getTypeShared(j, i).m_sprite.setPosition((sf::Vector2f(getTilePosition(j, i))));
			target->draw(getTypeShared(j, i).m_sprite);
		}
	}

	
	sf::View view = GameEngine::CameraManager::GetInstance()->GetCameraView();
	sf::Vector2f viewCentre = GameEngine::CameraManager::GetInstance()->GetCameraView().getCenter();

	const sf::RenderWindow& window = *engine.GetRenderWindow();
	sf::Vector2f screenSize(sf::Vector2f{ window.getSize() });

	sf::Vector2f viewTopLeft = viewCentre - view.getSize() / 2.0f;
	float xOffset = viewTopLeft.x > screenSize.x ? viewTopLeft.x - screenSize.x : 0.0f;
	float yOffset = viewTopLeft.y > screenSize.y ? viewTopLeft.y - screenSize.y : 0.0f;

	//Camera translation is hurting my 5:30am brain :(
	sf::RectangleShape cursorTile{ sf::Vector2f{ (float)allShared.m_width, (float)allShared.m_height} };
	sf::Vector2i cursorIndex = sf::Mouse::getPosition(*engine.GetRenderWindow());
	cursorIndex.x += xOffset;
	cursorIndex.y += yOffset;
	cursorIndex.x /= allShared.m_width;
	cursorIndex.y /= allShared.m_height;
	cursorTile.setPosition(sf::Vector2f{ (float)(cursorIndex.x * allShared.m_width), (float)(cursorIndex.y * allShared.m_height) } -cursorTile.getSize() / 2.0f);
	cursorTile.setFillColor(sf::Color::Yellow);
	target->draw(cursorTile);
}

float Map::getWidth() const
{
	return Tile::s_allShared.m_width * g_cols;
}

float Map::getHeight() const
{
	return Tile::s_allShared.m_height * g_rows;
}

Map::Map()
{
	//Define different globally shared tile attributes here.
	TileAllShared& allShared = Tile::s_allShared;
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
