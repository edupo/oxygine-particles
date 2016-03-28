/*
 * particle.h
 *
 *  Created on: 27 de mar. de 2016
 *      Author: eduardo
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(Particle, spParticle)

class Particle: public Sprite {
private:
	void onTweenDone(Event *event) {
		Destroy();
	}
public:
	Particle(ResAnim* anim, Vector2 initialPosition, float angle, float speed,
			timeMS duration) {
		setResAnim(anim);
		setPosition(initialPosition);

		Vector2 direction(cos(angle), sin(angle));

		Vector2 endPos = direction * speed * ((float) duration / 1000.0f);
		addTween(Sprite::TweenAlpha(0),duration * 0.4, 1, false, duration * 0.6, Tween::ease_linear);
		spTween tween = addTween(Sprite::TweenPosition(endPos), duration, 1,
				false, 0, Tween::ease_outCubic);

		tween->setDoneCallback( CLOSURE(this, &Particle::onTweenDone) );
	}
	void Destroy() {
		detach();
	}
};

#endif /* PARTICLE_H_ */
