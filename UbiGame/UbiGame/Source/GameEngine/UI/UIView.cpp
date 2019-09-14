#include "UIView.h"

#include <SFML/Window/Mouse.hpp>

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"

void UIView::init()
{
	GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->setMouseCursorVisible(false);
	m_cursor.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Cursor));
	m_cursorClicked.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Cursor_clicked));
}

void UIView::render(sf::RenderTarget * renderTarget)
{
	// Render cursor based on whether click occurs
	sf::Vector2i pos = sf::Mouse::getPosition(*GameEngine::GameEngineMain::GetInstance()->GetRenderWindow());
	m_cursor.setPosition(sf::Vector2f(pos));
	m_cursorClicked.setPosition(sf::Vector2f(pos));
	renderTarget->draw(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? m_cursorClicked : m_cursor);
}