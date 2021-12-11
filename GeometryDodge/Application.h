#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include "Level.h"
#include "Menu.h"

class Application
{
public:
	Application(int width, int height);
	~Application();

	void run();

private:
	void initWindow();
	void processWindowEvents();
	void runGameLoop(Level* level, Menu* menu, float deltaTime);

	sf::RenderWindow window;
	Input input;
	GameState gameState;
	Level* level;
	Menu* menu;

	sf::String playerIPinput;
	sf::Text IPaddrText;

	int windowWidth;
	int windowHeight;

};