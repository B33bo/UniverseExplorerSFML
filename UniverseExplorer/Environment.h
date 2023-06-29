#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Spawner.h"
#include "AllObjects.h"
constexpr float sizeOfCell = 100;

enum Environment
{
	Nothing,
	Stars,
	Balls,
};

float RandomBetween(float a, float b) {
	return (rand() / (RAND_MAX + 0.f)) * (b - a) + a;
}

SpaceObject* GetAtPos(int x, int y, int seed) {
	srand(seed);
	if (rand() % 2 == 0)
		return nullptr;
	float xPos = x + RandomBetween(-sizeOfCell / 2, sizeOfCell / 2);
	float yPos = y + RandomBetween(-sizeOfCell / 2, sizeOfCell / 2);
	Star* newObject = new Star(xPos, yPos, seed);
	Spawner::Add((SpaceObject*)newObject);
	return (SpaceObject*)newObject;
}

int seed(int x, int y) {
	return 1050011 * x * x * x + 1050013 * y * y * y;
}

bool includes(int seed, std::vector<int> pos) {
	for (int i = 0; i < pos.size(); i++)
	{
		if (pos[i] == seed)
			return true;
	}
	return false;
}

std::map<int, SpaceObject*> positions;
void RefreshEnvironment(int xMin, int xMax, int yMin, int yMax) {
	xMin = floor(xMin / sizeOfCell) * sizeOfCell;
	yMin = floor(yMin / sizeOfCell) * sizeOfCell;
	xMax = floor(xMax / sizeOfCell) * sizeOfCell + sizeOfCell * 2;
	yMax = floor(yMax / sizeOfCell) * sizeOfCell + sizeOfCell * 2;

	std::vector<int> posFound = std::vector<int>();
	for (int x = xMin; x < xMax; x += sizeOfCell)
	{
		for (int y = yMin; y < yMax; y += sizeOfCell)
		{
			int currSeed = seed(x, y);
			posFound.push_back(currSeed);
			if (positions.find(currSeed) != positions.end())
				continue; // already added :-)

			SpaceObject* obj = GetAtPos(x, y, currSeed);

			positions.insert({ currSeed, obj });
		}
	}

	std::vector<int> deleteFromPositions = std::vector<int>();
	for (const auto& pos : positions) {
		if (pos.second == nullptr)
			continue;
		if (includes(pos.first, posFound))
			continue;
		deleteFromPositions.push_back(pos.first);
	}

	for (int i = 0; i < deleteFromPositions.size(); i++)
	{
		Spawner::Remove(positions[deleteFromPositions[i]]);
		positions.erase(deleteFromPositions[i]);
	}
}