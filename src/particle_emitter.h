/*
 * particle_emitter.h
 *
 *  Created on: 27 de mar. de 2016
 *      Author: eduardo
 */

#ifndef PARTICLE_EMITTER_H_
#define PARTICLE_EMITTER_H_

#include "oxygine-framework.h"
#include "particle.h"

using namespace oxygine;

DECLARE_SMART(ParticleEmitter, spParticleEmitter)

class ParticleEmitter : public Actor
{
private:

	bool _continous;
	timeMS _life;
	float _interval;
	ResAnim* _anim;

	timeMS _counter;

public:
	ParticleEmitter(ResAnim* animation, float particlesPerSecond)
		: _continous(true)
		, _life(-1)
		, _interval(1/particlesPerSecond * 1000)
		, _anim(animation)
	{
		_counter = _interval;
	}

	void Generate(const int ammount = 1)
	{
		for(int i = 0; i < ammount; i++)
		{
			spParticle particle = new Particle(_anim,getPosition(),scalar::randFloat(0,2*MATH_PI),100.0f,1000);
			addChild( particle );
		}
	}

protected:
	void doUpdate(const UpdateState &us)
	{
		_counter += us.dt;
		if(_counter > _interval)
		{
			Generate(_counter / _interval);
			_counter = 0;
		}

	}

};

#endif /* PARTICLE_EMITTER_H_ */
