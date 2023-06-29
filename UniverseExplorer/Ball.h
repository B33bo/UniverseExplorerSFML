#pragma once
#ifndef SPACEOBJECT
#define SPACEOBJECT
#include "SpaceObject.h"
#endif
#include "Orbital.h"
#include <SFML/Graphics.hpp>

class Ball : public Orbital {
private:
	sf::CircleShape circle;
public:
	float size;

	Ball() {
		size = 0;
	}

	Ball(float x, float y, int inSeed) {
		size = RandomBetween(1, 2.5);
		circle = sf::CircleShape();
		circle.setFillColor(sf::Color::White);
		circle.setRadius(size);
		circle.setOrigin(size / 2.f, size / 2.f);
		circle.setFillColor(sf::Color(RandomBetween(0, 255), RandomBetween(0, 255), RandomBetween(0, 255)));
		Xpos = x;
		Ypos = y;
		seed = inSeed;
	}

	void Render(float x, float y, sf::RenderWindow* window) override {
		circle.setPosition(x, y);
		window->draw(circle);
	}
};