#include "PlayerMovementComponent.h"
#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/Map.h"
#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
	: m_lastFaceIndex(0)
	, m_wasFaceSwapButtonPressed(false)
{

}


PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void PlayerMovementComponent::Update()
{
	__super::Update();

	//Grabs how much time has passed since the last Update() call
	float dt = GameEngine::GameEngineMain::GetTimeDelta();

	//by default the wanted velocity is 0
	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);
	//player Velocity is applied when we have some input (for the time being let's make it 10pixels a second)
	float playerVel = 100.f;

	GameEngine::AnimationComponent* animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		wantedVel.x -= playerVel * dt;
		animComponent->PlayAnim(GameEngine::EAnimationId::PlayerLeft);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		wantedVel.x += playerVel * dt;
		animComponent->PlayAnim(GameEngine::EAnimationId::PlayerRight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		wantedVel.y -= playerVel * dt;
		animComponent->PlayAnim(GameEngine::EAnimationId::PlayerUp);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		wantedVel.y += playerVel * dt;
		animComponent->PlayAnim(GameEngine::EAnimationId::PlayerDown);
	}
	
	//Update the entity position with new velocity
	const Map& map = Map::getInstance();
	GameEngine::Entity& entity = *GetEntity();
	sf::Vector2f desiredPosition = entity.GetPos() + wantedVel;
	sf::Vector2f entitySize = entity.GetSize();

	if (desiredPosition.x >= entitySize.x / 2.0f && desiredPosition.x < map.getWidth() - entitySize.x / 2.0f && desiredPosition.y >= entitySize.y / 2.0f && desiredPosition.y < map.getHeight() - entitySize.y /2.0f)
		entity.SetPos(desiredPosition);
}