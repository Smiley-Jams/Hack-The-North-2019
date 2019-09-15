#pragma once

#include <vector>

class ParticleManager
{

	enum class Type
	{
		Cloud1 = 0,
		Cloud2 = 1,
		Cloud3 = 2
	};

	struct Particle
	{
		Type type;
		int x;
		int y;
		int frame;	// FOR REALLY SLOW THINGS
	};

public:
	void init();

	void render();
private:
	std::vector<Particle> m_particles;
};