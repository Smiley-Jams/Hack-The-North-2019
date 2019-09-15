#include "PlayerMovementComponent.h"
#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/Map.h"
#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
	: m_lastFaceIndex(0)
	, m_wasFaceSwapButtonPressed(false)
	, m_lastAnim(GameEngine::EAnimationId::PlayerRight)
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

	bool moving = false;
	if (!moving && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		moving = true;
		wantedVel.x -= playerVel * dt;
		if (m_lastAnim != GameEngine::EAnimationId::PlayerMoveLeft)
		{
			animComponent->PlayAnim(GameEngine::EAnimationId::PlayerMoveLeft);
			m_lastAnim = GameEngine::EAnimationId::PlayerMoveLeft;
		}
	}
	if (!moving && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moving = true;
		wantedVel.x += playerVel * dt;
		if (m_lastAnim != GameEngine::EAnimationId::PlayerMoveRight)
		{
			animComponent->PlayAnim(GameEngine::EAnimationId::PlayerMoveRight);
			m_lastAnim = GameEngine::EAnimationId::PlayerMoveRight;
		}
	}
	if (!moving && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moving = true;
		wantedVel.y -= playerVel * dt;
		if (m_lastAnim != GameEngine::EAnimationId::PlayerMoveUp)
		{
			animComponent->PlayAnim(GameEngine::EAnimationId::PlayerMoveUp);
			m_lastAnim = GameEngine::EAnimationId::PlayerMoveUp;
		}
	}
	if (!moving && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moving = true;
		wantedVel.y += playerVel * dt;
		if (m_lastAnim != GameEngine::EAnimationId::PlayerMoveDown)
		{
			animComponent->PlayAnim(GameEngine::EAnimationId::PlayerMoveDown);
			m_lastAnim = GameEngine::EAnimationId::PlayerMoveDown;
		}
	}
	if (!moving)
	{
		if (m_lastAnim == GameEngine::EAnimationId::PlayerMoveRight) animComponent->PlayAnim(GameEngine::EAnimationId::PlayerRight);
		if (m_lastAnim == GameEngine::EAnimationId::PlayerMoveLeft) animComponent->PlayAnim(GameEngine::EAnimationId::PlayerLeft);
		if (m_lastAnim == GameEngine::EAnimationId::PlayerMoveUp) animComponent->PlayAnim(GameEngine::EAnimationId::PlayerUp);
		if (m_lastAnim == GameEngine::EAnimationId::PlayerMoveDown) animComponent->PlayAnim(GameEngine::EAnimationId::PlayerDown);
		// Doesn't matter what this is as long as it's not a moving anim
		m_lastAnim = GameEngine::EAnimationId::PlayerRight;
	}
	
	//Update the entity position with new velocity
	const Map& map = Map::getInstance();
	GameEngine::Entity& entity = *GetEntity();
	sf::Vector2f desiredPosition = entity.GetPos() + wantedVel;
	sf::Vector2f entitySize = entity.GetSize();

	if (desiredPosition.x >= entitySize.x / 2.0f && desiredPosition.x < map.getWidth() - entitySize.x / 2.0f && desiredPosition.y >= entitySize.y / 2.0f && desiredPosition.y < map.getHeight() - entitySize.y /2.0f)
		entity.SetPos(desiredPosition);
}