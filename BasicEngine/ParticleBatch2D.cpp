#include "ParticleBatch2D.h"

namespace BasicEngine {

	ParticleBatch2D::ParticleBatch2D()
	{
	}

	ParticleBatch2D::~ParticleBatch2D()
	{
		delete[] _particles;
	}
	void ParticleBatch2D::init(int maxParticles, float decayRate, const GLTexture& texture, std::function<void(Particle2D&, float)> updateFunc/*= defaultParticleUpdate*/)
	{
		_maxParticles = maxParticles;
		_particles = new Particle2D[maxParticles];

		_decayRate = decayRate;

		_texture = texture;

		_updatefunc = updateFunc;
	}
	void ParticleBatch2D::update(float deltaTime)
	{
		for (size_t i = 0; i < _maxParticles; i++)
		{
			//Check if the particle is active
			if (_particles[i].life > 0.0f)
			{
				_updatefunc(_particles[i], deltaTime);
				_particles[i].life -= _decayRate * deltaTime;
			}
		}
	}
	void ParticleBatch2D::draw(SpriteBatch* spriteBatch)
	{
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < _maxParticles; i++)
		{
			auto& p = _particles[i];
			//Check if the particle is active
			if (p.life > 0.0f)
			{
				glm::vec4 destRect(p.position.x, p.position.y, p.width, p.width);
				spriteBatch->draw(destRect,uvRect,_texture.id,0.0f, p.color);
			}
		}
	}
	void ParticleBatch2D::addParticle(const glm::vec2& position, const glm::vec2& velocity, const Color& color, float width)
	{
			auto& p = _particles[findFreeParticle()];

			p.life = 1.0f;
			p.position = position;
			p.velocity = velocity;
			p.color = color;
			p.width = width;
			
	}

	int ParticleBatch2D::findFreeParticle()
	{
		for (size_t i = _lastFreeParticle; i < _maxParticles; i++)
		{
			if (_particles[i].life <= 0.0f)
			{
				_lastFreeParticle = i;
				return i;
			}
		}

		for (size_t i = 0; i < _lastFreeParticle; i++)
		{
			if (_particles[i].life <= 0.0f)
			{
				_lastFreeParticle = i;
				return i;
			}
		}

		//No particles are free - override first particle
		return 0;
	}
	
}
