#include "UIView.h"

#include <SFML/Window/Mouse.hpp>

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/Util/CameraManager.h"

void UIView::init()
{
	GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setMouseCursorVisible(false);
	m_cursor.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Cursor));
	m_cursorClicked.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Cursor_clicked));
}

void UIView::render(sf::RenderTarget * renderTarget)
{
	// Render cursor based on whether click occurs (Need to take into account camera position)
	sf::Vector2i pos = sf::Mouse::getPosition(*GameEngine::GameEngineMain::GetInstance()->GetRenderWindow());
	sf::Vector2i cam = sf::Vector2i(GameEngine::CameraManager::GetInstance()->GetCameraView().getCenter());
	sf::Vector2i scr = sf::Vector2i(GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->getSize()) / 2;
	m_cursor.setPosition(sf::Vector2f(pos + cam - scr));
	m_cursorClicked.setPosition(sf::Vector2f(pos + cam - scr));
	renderTarget->draw(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? m_cursorClicked : m_cursor);
}