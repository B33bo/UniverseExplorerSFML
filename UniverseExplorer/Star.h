#pragma once
#ifndef SPACEOBJECT
#define SPACEOBJECT
#include "SpaceObject.h"
#endif
#include "Planet.h"
#include <SFML/Graphics.hpp>

class Star : SpaceObject {
public:
	sf::CircleShape circle;
	float size;
	float temperatureKelvin;
	Planet* planets[4];
	int planetCount;

	static sf::Color BlackBodyRadiation(float temp) {
		if (temp < 1000)
			temp = 1000;

		if (temp < 1500) {
			return sf::Color((int)((temp - 1000) / 1000.0 * 255), 0, 0);
		}
		if (temp < 3000) {
			return sf::Color(255, (temp - 1500) / 1500.0 * 255, 0);
		}
		if (temp < 7000) {
			return sf::Color(255, 255, (temp - 3000) / 5000.0 * 255);
		}
		return sf::Color((temp * -1 / 2000.0 + 4.5f) * 255, 255, 255);
	}

	Star(float x, float y, int inSeed) {
		size = RandomBetween(2, 4);
		circle = sf::CircleShape();
		circle.setFillColor(sf::Color::White);
		circle.setRadius(size);
		circle.setOrigin(size / 2.f, size / 2.f);
		temperatureKelvin = RandomBetween(1000, 10000);
		circle.setFillColor(BlackBodyRadiation(temperatureKelvin));
		Xpos = x;
		Ypos = y;
		seed = inSeed;

		planetCount = rand() % 4;
		for (int i = 0; i < planetCount; i++)
		{
			Planet* planet = new Planet(Xpos, Ypos, seed + 1);
			planet->orbitalDistance = RandomBetween(size * 2, size * 2 + 25);
			planet->rotation = RandomBetween(0, 2 * PI);
			planet->radianPerSecond = RandomBetween(2, 10) / planet->orbitalDistance;
			planet->target = this;
			planets[i] = planet;
			Spawner::Add((SpaceObject*)planet);
		}
	}

	~Star() {
		for (int i = 0; i < planetCount; i++)
		{
			if (planets[i] == nullptr)
				continue;
			planets[i]->target = nullptr;
		}
	}

	void Render(float x, float y, sf::RenderWindow* window) override {
		circle.setPosition(x, y);
		window->draw(circle);
	}
};