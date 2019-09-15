#include "ParticleManager.h"

#include <time.h>

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"

#include <SFML/Graphics.hpp>

sf::Sprite sCloud1;
sf::Sprite sCloud2;
sf::Sprite sCloud3;

void ParticleManager::init()
{
	sCloud1.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Particle_cloud1));
	sCloud2.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Particle_cloud2));
	sCloud3.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Particle_cloud3));

	srand(time(nullptr));

	// Populate with initial clouds
	m_particles.reserve(20);
	for (int i = 0; i < 50; ++i)
	{
		int key = rand() % 3;
		m_particles.push_back(Particle{
				static_cast<Type>(key),
				(rand() % 16) * 128,
				(rand() % 16) * 128,
				rand() % 10
			});
	}
}

void ParticleManager::render()
{
	sf::RenderTarget * target = const_cast<sf::RenderTarget*>(GameEngine::GameEngineMain::GetInstance()->getRenderTarget());
	float dt = GameEngine::GameEngineMain::GetTimeDelta();
	for (auto& part : m_particles)
	{
		constexpr int x_speed = 220;
		constexpr int y_speed = 220;
		if (part.type == Type::Cloud1 || part.type == Type::Cloud2 || part.type == Type::Cloud3)
		{
			part.frame++;
			if (part.frame == 15) part.x += 1;
			if (part.frame > 30)
			{
				part.frame = 0;
				part.x += 1;
				part.y += 1;
			}
			if (part.x > 16 * 128 || part.y > 16 * 128)
			{
				int key = rand() % 2;
				if (key == 0) {
					part.x = rand() % 14 * 128;
					part.y = -200;
				} else {
					part.x = -200;
					part.y = rand() % 14 * 128; 
				}
			}
			// If the clouds are too far out, reset
			if (part.type == Type::Cloud1)
			{
				sCloud1.setPosition(sf::Vector2f(static_cast<float>(part.x), static_cast<float>(part.y)));
				target->draw(sCloud1);
			}
			if (part.type == Type::Cloud2)
			{
				sCloud2.setPosition(sf::Vector2f(static_cast<float>(part.x), static_cast<float>(part.y)));
				target->draw(sCloud2);
			}
			if (part.type == Type::Cloud3)
			{
				sCloud3.setPosition(sf::Vector2f(static_cast<float>(part.x), static_cast<float>(part.y)));
				target->draw(sCloud3);
			}
		}
	}
}