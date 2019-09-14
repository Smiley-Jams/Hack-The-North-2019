#pragma once

#include <SFML/Graphics/Text.hpp>
#include <string>

class Text
{
public:
	static void init();
	static void drawText(const std::string& str, sf::Vector2i pos = { 0, 0 }, int size = 16, sf::Color color = sf::Color::White);
private:
	static sf::Font s_font;
};