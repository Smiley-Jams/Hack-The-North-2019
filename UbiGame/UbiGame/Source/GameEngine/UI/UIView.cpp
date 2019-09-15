#include "UIView.h"

#include <SFML/Window/Mouse.hpp>

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/Util/CameraManager.h"
#include "text.h"

constexpr int sResourceSpacing = 120;
sf::Sprite sWoodSprite;
sf::Sprite sOreSprite;
sf::Sprite sWoolSprite;

void UIView::init()
{
	GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setMouseCursorVisible(false);
	GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setMouseCursorGrabbed(true);

	m_cursor.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Cursor));
	m_cursorClicked.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Cursor_clicked));

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

	// Render cursor based on whether click occurs (Need to take into account camera position)
	sf::Vector2i pos = sf::Mouse::getPosition(*GameEngine::GameEngineMain::GetInstance()->GetRenderWindow());
	m_cursor.setPosition(sf::Vector2f(pos + cam - scr));
	m_cursorClicked.setPosition(sf::Vector2f(pos + cam - scr));
	renderTarget->draw(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? m_cursorClicked : m_cursor);
}