/*
 * particle_emitter.h
 *
 *  Created on: 27 de mar. de 2016
 *      Author: edupo - contact@eduardolezcano.com
 */

#ifndef PARTICLE_EMITTER_H_
#define PARTICLE_EMITTER_H_

#include "oxygine-framework.h"
#include "particle.h"

using namespace oxygine;

DECLARE_SMART(ParticleEmitter, spParticleEmitter)

class ParticleEmitter: public Actor
{
private:

	ResAnim* _anim;
	spActor _parent;

	timeMS _minLife, _maxLife;
	float _minSpeed, _maxSpeed;
	float _minScale, _maxScale;

	timeMS _duration;
	float _interval;
	timeMS _counter;

	mutable unsigned short _flags;
	enum flags
	{
		flag_disable 		= 1,
		flag_freeParticles 	= 1 << 1,
		flag_last 			= flag_freeParticles
	};

public:
	ParticleEmitter(ResAnim* animation, float particlesPerSecond, timeMS duration = -1,
			bool freeParticles = true)
			: _flags(0), _duration(duration)
	{
		setGenerationSpeed(particlesPerSecond);
		setAnim(animation);

		setParticleLife(500);
		setParticleSpeed(1000.0f);
		setParticleScale(1.0f);

		_counter = _interval;

		if (freeParticles)
		{
			_flags |= flag_freeParticles;
			_parent = getStage();
		}
		else
			_parent = this;
	}

	void setGenerationSpeed(float particlesPerSecond)
	{
		_interval = 1.0f / particlesPerSecond * 1000.0f;
	}
	void setAnim(ResAnim* anim)
	{
		_anim = anim;
	}
	void setParticleLife(timeMS life, float variation = 0.0f)
	{
		_minLife = life * (1.0f - variation);
		_maxLife = life * (1.0f + variation);
	}
	void setParticleSpeed(float speed, float variation = 0.0f)
	{
		_minSpeed = speed * (1.0f - variation);
		_maxSpeed = speed * (1.0f + variation);
	}
	void setParticleScale(float scale, float variation = 0.0f)
	{
		_minScale = scale * (1.0f - variation);
		_maxScale = scale * (1.0f + variation);
	}
	void setDisable(bool diable)
	{
		_flags &= ~flag_disable;
		if (diable)
			_flags |= flag_disable;
	}

protected:

	void Generate(const int ammount = 1)
	{
		for (int i = 0; i < ammount; i++)
		{
			spParticle particle = new Particle(_parent, _anim,
					_flags & flag_freeParticles ? convert_local2stage(this, getPosition()) : getPosition(),
					scalar::randFloat(0, 2 * MATH_PI), scalar::randFloat(_minSpeed,_maxSpeed), 1000);
			particle->setScale(scalar::randFloat(_minScale,_maxScale));
		}
	}

	void doUpdate(const UpdateState &us)
	{
		if (_flags & flag_disable)
			return;

		_counter += us.dt;
		if (_counter > _interval)
		{
			Generate(_counter / _interval);
			_counter = 0;
		}

	}

};

#endif /* PARTICLE_EMITTER_H_ */
