#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spawner.h"
#include "Environment.h"

float cameraX = 0;
float cameraY = 0;
float cameraScale = 50;
float camSpeed = 1;

void Movement(float deltaTime, sf::RenderWindow* window) {
	float speed = camSpeed * cameraScale / 5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		cameraX += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		cameraX -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		cameraY += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		cameraY -= speed * deltaTime;

	float aspect = window->getSize().x / (window->getSize().y + .0);
	float yScale = cameraScale / aspect;
	sf::FloatRect view(cameraX - cameraScale / 2, cameraY - yScale / 2, cameraScale, yScale);
	window->setView(sf::View(view));
}

void GetDebugText(sf::Text* object, float dt, sf::View view, sf::RenderWindow* window) {
	sf::Vector2f itemCountPos = sf::Vector2f(view.getCenter().x - view.getSize().x / 2.f, view.getCenter().y - view.getSize().y / 2.f);
	object->setPosition(itemCountPos);
	object->setCharacterSize(100);
	object->setScale(sf::Vector2f(cameraScale / 10000, cameraScale / 10000));

	sf::Vector2f mpos = window->mapPixelToCoords(sf::Mouse::getPosition());

	std::string text = "FPS: " + std::to_string((int)(1 / dt))
		+ "\nObjects: " + std::to_string(Spawner::arr.size())
		+ "\nCamera Position: (" + std::to_string(cameraX) + ", " + std::to_string(cameraY) + ")"
		+ "\nMouse Position: (" + std::to_string(mpos.x) + ", " + std::to_string(mpos.y) + ")"
		+ "\nCamera Scale: " + std::to_string(cameraScale)
		+ "\nCamera Speed: " + std::to_string(camSpeed)
		;
	object->setString(text);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Space Explorer");
	sf::Clock deltaClock;
	sf::Text itemCount = sf::Text();
	sf::Font font;
#ifdef NDEBUG
	font.loadFromFile("./arial.ttf");
#else
	font.loadFromFile("../x64/Debug/arial.ttf");
#endif
	itemCount.setFont(font);

	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseWheelMoved) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					camSpeed += event.mouseWheel.delta * camSpeed * .1;
					if (camSpeed < 0)
						camSpeed = 0;
				}
				else {
					cameraScale -= event.mouseWheel.delta * cameraScale * .1;
					if (cameraScale < 0)
						cameraScale = 0;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					sf::Vector2f targetPos = window.mapPixelToCoords(sf::Mouse::getPosition());
					cameraX = targetPos.x;
					cameraY = targetPos.y;
				}
			}
		}

		Movement(dt.asSeconds(), &window);

		auto& view = window.getView();

		GetDebugText(&itemCount, dt.asSeconds(), view, &window);

		window.clear();
		RefreshEnvironment(view.getCenter().x - view.getSize().x / 2.f,
			view.getCenter().x + view.getSize().x / 2.f,
			view.getCenter().y - view.getSize().y / 2.f,
			view.getCenter().y + view.getSize().y / 2.f);
		Spawner::RenderAll(&window, dt.asSeconds(), cameraScale);
		window.draw(itemCount);
		window.display();
	}

	return 0;
}