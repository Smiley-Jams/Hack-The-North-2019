#include "CameraManager.h"

#include <SFML/Window/Mouse.hpp>
#include "GameEngine/GameEngineMain.h"
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
	sf::Vector2u size = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->getSize();
	sf::Vector2i pos = sf::Mouse::getPosition(*GameEngine::GameEngineMain::GetInstance()->GetRenderWindow());
	if (pos.x < s_hoverMargin)
	{
		GetCameraView().move(-1.0f, 0.f);
	}
	if (pos.x > size.x - s_hoverMargin)
	{
		GetCameraView().move(1.0f, 0.f);
	}
	if (pos.y < s_hoverMargin)
	{
		GetCameraView().move(0.f, -1.0f);
	}
	if (pos.y > size.y - s_hoverMargin)
	{
		GetCameraView().move(0.f, 1.0f);
	}
}