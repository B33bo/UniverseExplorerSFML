#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpaceObject.h"

static class Spawner
{
private:
	static std::vector<SpaceObject*> destroyStack;
public:
	static std::vector<SpaceObject*> arr;
	static void Add(SpaceObject*);
	static void Remove(SpaceObject*);
	static void RenderAll(sf::RenderWindow*, float, float);
};