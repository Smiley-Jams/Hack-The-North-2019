#include "UIWindow.h"

#include <SFML/Graphics/Rect.hpp>

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/Util/CameraManager.h"

#include "text.h"

constexpr int sVerticalButtonHeight = 128;
constexpr int sButtonWidth = 64;
constexpr int sButtonHeight = 128;
sf::Sprite sButtonSprite;
sf::Sprite sButtonPressedSprite;
sf::Sprite sBackground;
constexpr int sBackgroundSize = 200;
constexpr int sBackgroundMargin = 100;

UIWindow::UIWindow() : m_active(false)
{

}

void UIWindow::init()
{
	// The button sprite would always be at the same position
	sButtonSprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::UI_side_button));
	sButtonPressedSprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::UI_side_button_clicked));
	sBackground.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::UI_background));
}

// Also do updating in render because why not...
void UIWindow::render(sf::RenderTarget * renderTarget)
{
	// Camera info since UI doesn't move with the camera
	sf::Vector2i cam = sf::Vector2i(GameEngine::CameraManager::GetInstance()->GetCameraView().getCenter());
	sf::Vector2i scr = sf::Vector2i(GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->getSize()) / 2;
	sButtonSprite.setPosition(sf::Vector2f(sf::Vector2i(0, sVerticalButtonHeight) + cam - scr));
	sButtonPressedSprite.setPosition(sf::Vector2f(sf::Vector2i(0, sVerticalButtonHeight) + cam - scr));

	// Check to see if we the UI becomes active
	sf::Vector2i pos = sf::Mouse::getPosition(*GameEngine::GameEngineMain::GetInstance()->GetRenderWindow());
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::IntRect collision(0, sVerticalButtonHeight, sButtonWidth, sButtonHeight);
		if (collision.contains(pos))
		{
			m_active = true;
		}
		else
		{
			sf::IntRect bigCollision(sBackgroundMargin, sBackgroundMargin, (scr.x - sBackgroundMargin) * 2, (scr.y - sBackgroundMargin) * 2);
			if (m_active && !bigCollision.contains(pos))
			{
				m_active = false;
			}
		}
	}

	// Render the side buttons
	renderTarget->draw(m_active ? sButtonPressedSprite : sButtonSprite);

	// Render the actual menu if needed
	if (m_active)
	{
		int x = sBackgroundMargin + cam.x - scr.x;
		int y = sBackgroundMargin + cam.y - scr.y;
		sBackground.setPosition(static_cast<float>(x), static_cast<float>(y));
		float x_scale = static_cast<float>((scr.x - sBackgroundMargin) * 2) / static_cast<float>(sBackgroundSize);
		float y_scale = static_cast<float>((scr.y - sBackgroundMargin) * 2) / static_cast<float>(sBackgroundSize);
		sBackground.setScale(x_scale, y_scale);
		renderTarget->draw(sBackground);
	}
}