#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	/*
	//Template definition -> every new animation needs to have an ID and a definition that controls how animation is played
	m_animDefinitions.push_back
	(
	SAnimationDefinition(
	EAnimationId::BirdIdle,
	eTexture::Player,
	sf::Vector2i(0, 0),
	10,
	3)
	);
	*/
	m_animDefinitions.push_back
	(
		SAnimationDefinition(EAnimationId::PlayerRight,
			eTexture::Player,
			sf::Vector2i(0, 0),
			1,
			1)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(EAnimationId::PlayerLeft,
			eTexture::Player,
			sf::Vector2i(1, 0),
			1,
			1)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(EAnimationId::PlayerUp,
			eTexture::Player,
			sf::Vector2i(2, 0),
			1,
			1)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(EAnimationId::PlayerDown,
			eTexture::Player,
			sf::Vector2i(3, 0),
			1,
			1)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(EAnimationId::PlayerMoveRight,
			eTexture::Player,
			sf::Vector2i(4, 0),
			8,
			24)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(EAnimationId::PlayerMoveLeft,
			eTexture::Player,
			sf::Vector2i(12, 0),
			8,
			24)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(EAnimationId::PlayerMoveUp,
			eTexture::Player,
			sf::Vector2i(20, 0),
			6,
			24)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(EAnimationId::PlayerMoveDown,
			eTexture::Player,
			sf::Vector2i(26, 0),
			6,
			24)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}
