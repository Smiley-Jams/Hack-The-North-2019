#include "CameraManager.h"

#include <SFML/Window/Mouse.hpp>
#include "GameEngine/GameEngineMain.h"
#include "Game/Map.h"

using namespace GameEngine;

CameraManager* CameraManager::sm_instance = nullptr;

constexpr int s_hoverMargin = 40;

CameraManager::CameraManager()
{

}


CameraManager::~CameraManager()
{

}

void CameraManager::update(float delta)
{
	// HARD CODED BARS TO SEE IF MOUSE IS HOVERED OVER CAMERA MOVE AREA
	const sf::RenderWindow& window = *GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	sf::Vector2u screenSize = window.getSize();
	sf::Vector2f cameraCentre = GetCameraView().getCenter();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	//Constrain based on camera position, mouse move margin, and mouse position.
	sf::FloatRect view {
		cameraCentre.x - screenSize.x / 2, cameraCentre.y - screenSize.y / 2,
		cameraCentre.x + screenSize.x / 2, cameraCentre.y + screenSize.y / 2,
	};

	if (mousePosition.x < s_hoverMargin && view.left > 1)
	{
		GetCameraView().move(-1.0f, 0.f);
	}
	if (mousePosition.x > screenSize.x - s_hoverMargin && view.width < Map::getInstance().getWidth())
	{
		GetCameraView().move(1.0f, 0.f);
	}
	if (mousePosition.y < s_hoverMargin && view.top > 1)
	{
		GetCameraView().move(0.f, -1.0f);
	}
	if (mousePosition.y > screenSize.y - s_hoverMargin && view.height < Map::getInstance().getHeight())
	{
		GetCameraView().move(0.f, 1.0f);
	}
}