#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class UIWindow
{
public:
	UIWindow();

	void init();

	void render(sf::RenderTarget * renderTarget);
private:
	bool m_active;
};