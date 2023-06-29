#include "Spawner.h"

std::vector<SpaceObject*> Spawner::arr;

void Spawner::Remove(SpaceObject* object) {
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i]->seed == object->seed) {
			delete arr[i];
			arr.erase(arr.begin() + i);
			break;
		}
		if (i == arr.size() - 1)
			throw;
	}
}

void Spawner::Add(SpaceObject* object) {
	arr.push_back(object);
}

void Spawner::RenderAll(sf::RenderWindow* window, float dt, float cameraScale) {
	for (int i = 0; i < arr.size(); i++) {
		if (i >= arr.size())
			break;
		if (arr[i]->Destroyed)
		{
			continue;
		}
		arr[i]->Render(arr[i]->Xpos, arr[i]->Ypos, window);
		arr[i]->Update(dt, cameraScale);
	}
}