#pragma once
#ifndef SPACEOBJECT
#define SPACEOBJECT
#include "SpaceObject.h"
#endif
#include "Orbital.h"
#include <SFML/Graphics.hpp>

class Planet : public Orbital {
	enum PlanetType
	{
		Rock,
		Water,
		Terrestrial,
		Random,
		Moon,
	};
private:
	sf::CircleShape circle;
public:
	float size;
	PlanetType planetType;
	Planet* moons[2];
	int moonCount;

	sf::Color GetColor() {
		int grey;
		switch (planetType)
		{
		case Planet::Random:
			return sf::Color(RandomBetween(0, 255), RandomBetween(0, 255), RandomBetween(0, 255));
		case Planet::Rock:
			grey = RandomBetween(0, 255);
			return sf::Color(RandomBetween(grey, 255), grey, grey);
		case Planet::Water:
			return sf::Color(0, 0, RandomBetween(128, 255));
		case Planet::Moon:
			grey = RandomBetween(0, 255);
			return sf::Color(grey, grey, grey);
		case Planet::Terrestrial:
			return sf::Color(RandomBetween(0, 100), RandomBetween(128, 255), RandomBetween(0, 100));
		default:
			break;
		}
		return sf::Color::Red;
	}

	Planet() {
		size = 0;
		moonCount = 0;
		planetType = Moon;
	}

	Planet(float x, float y, int inSeed) {
		Xpos = x;
		Ypos = y;
		seed = inSeed;

		size = RandomBetween(1, 2.5);
		planetType = (PlanetType)(rand() % 3);

		Init();

		for (int i = 0; i < moonCount; i++)
		{
			moons[i] = new Planet();
			moons[i]->seed = inSeed + 0xF00;
			moons[i]->orbitalDistance = RandomBetween(size * 2, size * 3);
			moons[i]->rotation = RandomBetween(0, PI * 2);
			moons[i]->radianPerSecond = RandomBetween(1, PI);
			moons[i]->target = this;
			moons[i]->size = size / 2;
			moons[i]->Init();
			Spawner::Add(moons[i]);
		}
	}

	void Init() {
		circle = sf::CircleShape();
		circle.setFillColor(GetColor());
		circle.setRadius(size);
		circle.setOrigin(size / 2.f, size / 2.f);

		if (planetType == Moon)
			moonCount = 0;
		else
			moonCount = rand() % 2;
	}

	void Render(float x, float y, sf::RenderWindow* window) override {
		circle.setPosition(x, y);
		window->draw(circle);
	}

	~Planet() {
		for (int i = 0; i < moonCount; i++)
		{
			moons[i]->target = nullptr;
		}
	}
};