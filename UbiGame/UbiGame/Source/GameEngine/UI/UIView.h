#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstdint>

class UIView
{
public:
	void init();

	// Call this function to set UI view data
	void set_resources(uint32_t wood, uint32_t ore, uint32_t wool);

	void render(sf::RenderTarget * renderTarget);
private:

	uint32_t m_wood;
	uint32_t m_ore;
	uint32_t m_wool;
};