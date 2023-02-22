#pragma once

#include <vector>



namespace BasicEngine {
	class ParticleBatch2D;
	class SpriteBatch;

	class ParticleEngine2D
	{
	private:
		std::vector<ParticleBatch2D*> _batches;
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		//After adding a particle batch the ParticleEngine2D becomes responsible for dealocation
		void addParticleBatch(ParticleBatch2D* particleBatch);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);

	};
}

