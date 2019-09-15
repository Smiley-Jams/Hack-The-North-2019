#include "UIView.h"

#include <SFML/Window/Mouse.hpp>

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/Util/CameraManager.h"
#include "text.h"

#include "Game/Map.h"

constexpr int sResourceSpacing = 120;
sf::Sprite sWoodSprite;
sf::Sprite sOreSprite;
sf::Sprite sWoolSprite;

void UIView::init()
{
	GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setMouseCursorVisible(false);
	GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setMouseCursorGrabbed(true);

	sWoodSprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Icon_wood));
	sOreSprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Icon_ore));
	sWoolSprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Icon_wool));
}

void UIView::set_resources(uint32_t wood, uint32_t ore, uint32_t wool)
{
	m_wood = wood;
	m_ore = ore;
	m_wool = wool;
}

void UIView::render(sf::RenderTarget * renderTarget)
{
	// Camera info since UI doesn't move with the camera
	sf::Vector2i cam = sf::Vector2i(GameEngine::CameraManager::GetInstance()->GetCameraView().getCenter());
	sf::Vector2i scr = sf::Vector2i(GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->getSize()) / 2;

	// Render UI showing the player's resources
	sf::Vector2i curr = sf::Vector2i(static_cast<int>(GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->getSize().x), 0);
	curr.x -= sResourceSpacing;
	sWoolSprite.setPosition(sf::Vector2f(curr + cam - scr));
	Text::drawText(std::to_string(m_wood), curr + sf::Vector2i(32, 0) + cam - scr, 32);
	curr.x -= sResourceSpacing;
	sOreSprite.setPosition(sf::Vector2f(curr + cam - scr));
	Text::drawText(std::to_string(m_ore), curr + sf::Vector2i(32, 0) + cam - scr, 32);
	curr.x -= sResourceSpacing;
	sWoodSprite.setPosition(sf::Vector2f(curr + cam - scr));
	Text::drawText(std::to_string(m_wool), curr + sf::Vector2i(32, 0) + cam - scr, 32);
	renderTarget->draw(sWoodSprite);
	renderTarget->draw(sOreSprite);
	renderTarget->draw(sWoolSprite);

	// Render overlay on tile showing tile resources
	sf::View view = GameEngine::CameraManager::GetInstance()->GetCameraView();
	sf::Vector2f viewCentre = GameEngine::CameraManager::GetInstance()->GetCameraView().getCenter();
	const sf::RenderWindow& window = *GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	sf::Vector2f screenSize(sf::Vector2f{ window.getSize() });
	sf::Vector2f viewTopLeft = viewCentre - view.getSize() / 2.0f;
	sf::Vector2i cursorIndex = sf::Mouse::getPosition(*GameEngine::GameEngineMain::GetInstance()->GetRenderWindow());
	cursorIndex.x += static_cast<int>(viewTopLeft.x);
	cursorIndex.y += static_cast<int>(viewTopLeft.y);
	// Yay hard coded
	int tile_x = cursorIndex.x / 128;
	int tile_y = cursorIndex.y / 128;
	cursorIndex.x = tile_x * 128;
	cursorIndex.y = tile_y * 128;
	sWoodSprite.setPosition(sf::Vector2f(cursorIndex));
	renderTarget->draw(sWoodSprite);
	Text::drawText(std::to_string(Map::getInstance().getResourceAt(tile_x, tile_y).m_wood), cursorIndex + sf::Vector2i(40.f, 10.f), 16);
	cursorIndex.y += 40;
	sOreSprite.setPosition(sf::Vector2f(cursorIndex));
	renderTarget->draw(sOreSprite);
	Text::drawText(std::to_string(Map::getInstance().getResourceAt(tile_x, tile_y).m_ore), cursorIndex + sf::Vector2i(40.f, 10.f), 16);
	cursorIndex.y += 40;
	sWoolSprite.setPosition(sf::Vector2f(cursorIndex));
	renderTarget->draw(sWoolSprite);
	Text::drawText(std::to_string(Map::getInstance().getResourceAt(tile_x, tile_y).m_wool), cursorIndex + sf::Vector2i(40.f, 10.f), 16);
}