#include "text.h"

#include "GameEngine/GameEngineMain.h"

sf::Font Text::s_font;

void Text::init()
{
	if (!s_font.loadFromFile("Resources/font/Raleway-Regular.ttf"))
	{
		// ERROR
	}
}

void Text::drawText(const std::string& str, sf::Vector2i pos, int size, sf::Color color)
{
	sf::Text text;
	text.setPosition(sf::Vector2f(pos));
	text.setFont(s_font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);

	GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->draw(text);
}