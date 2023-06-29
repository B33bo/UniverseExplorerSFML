#pragma once
#include <SFML/Graphics.hpp>

class SpaceObject {
public:
	virtual ~SpaceObject() = default;
	SpaceObject() = default;
	virtual void Render(float x, float y, sf::RenderWindow* window) {
		throw;
	}
	virtual void Update(float dt, float cameraScale) {
	}
	float Xpos = 0;
	float Ypos = 0;
	float rotation = 0;
	int seed = 0;
	bool Destroyed = false;

	float RandomBetween(float a, float b) {
		return rand() / (RAND_MAX + 0.f) * (b - a) + a;
	}
};