#pragma once
#ifndef SPACEOBJECT
#define SPACEOBJECT
#endif
#include "SpaceObject.h"

constexpr float PI = 3.14159265358979323846;

class Orbital : public SpaceObject {
public:
	float rotation;
	float radianPerSecond;
	float orbitalDistance;
	SpaceObject* target;

	void Update(float dt, float cameraScale) override {
		if (target == nullptr)
		{
			Spawner::Remove(this);
			return;
		}

		if (cameraScale > 10'000)
			return;

		rotation += radianPerSecond * dt;
		rotation = fmod(rotation, 2 * PI);
		Xpos = cos(rotation) * orbitalDistance + target->Xpos;
		Ypos = sin(rotation) * orbitalDistance + target->Ypos;
	}
};