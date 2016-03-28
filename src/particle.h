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

/**
 * A Particle is a Sprite who is completely defined (appearance and animation) since the construction.
 * After construction the particle is released and it will live until it's animations finishes.
 */
class Particle: public Sprite
{
private:
	timeMS _duration;
	Vector2 _endPos;
	spActor _parent;
	spTween _twFadeOut;
public:
	/**
	 * Constructor
	 * @param anim
	 * @param initialPosition
	 * @param angle in radians
	 * @param speed in pixels per second
	 * @param duration Negative duration keep particle alive until goes out of screen.
	 * @param emit Call Emit() after construction?
	 */
	Particle(spActor parent, ResAnim* anim, Vector2 initialPosition, float angle, float speed,
			timeMS duration, bool emit = true)
			: _duration(duration), _parent(parent)
	{
		setTouchEnabled(false);
		setResAnim(anim);
		setPosition(initialPosition);

		_endPos = initialPosition + Vector2(cos(angle), sin(angle)) * speed
				* ((float) duration / 1000.0f);

		setFadeOut();

		if(emit)
			Emit();
	}

	/**
	 * Starts the tweens for the particle.
	 */
	void Emit()
	{
		//Fade-out tween: Attach destruction to fadeout tween.
		addTween(_twFadeOut)->setDetachActor(true);
		//Position tween.
		addTween(Sprite::TweenPosition(_endPos), _duration, 1,
				false, 0, Tween::ease_outCubic);
		attachTo(_parent);
	}
	/**
	 * Set the fade-out tween. (Mandatory tween for every particle)
	 * @param when Start point [0.0, 1.0] relative to duration.
	 * @param ease
	 */
	void setFadeOut(float when = 0.6, Tween::EASE ease = Tween::ease_linear){
		_twFadeOut = createTween(Sprite::TweenAlpha(0), _duration * 1.0f - when, 1, false,
				_duration * when, Tween::ease_linear);
	}
};

#endif /* PARTICLE_H_ */
