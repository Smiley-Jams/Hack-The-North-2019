#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class UIView
{
public:
	void init();

	void render(sf::RenderTarget * renderTarget);
private:
	sf::Sprite m_cursor;
	sf::Sprite m_cursorClicked;
};