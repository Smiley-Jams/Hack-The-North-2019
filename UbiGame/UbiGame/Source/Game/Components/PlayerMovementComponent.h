#pragma once
#include "GameEngine\EntitySystem\Component.h"
#include "GameEngine\Util\AnimationManager.h"

namespace Game
{
	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

	private:
		int m_lastFaceIndex;
		bool m_wasFaceSwapButtonPressed;
		GameEngine::EAnimationId::type m_lastAnim;
	};
}