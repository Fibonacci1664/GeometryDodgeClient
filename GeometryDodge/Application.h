/*
 * This is the Application class and handles
 *		- Window creation.
 *		- Polling window events.
 *		- The main game loop.
 *		- Creation, updating and deletion of all Screen objects.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2021.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include "Level.h"
#include "Menu.h"
#include "GameOver.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Application
{
public:
	Application(int width, int height);
	~Application();

	void run();

private:
	void initWindow();
	void processWindowEvents();
	bool runGameLoop(Level* level, Menu* menu, GameOver* gameOver, float deltaTime);

	sf::RenderWindow window;
	Input input;
	GameState gameState;
	Level* level;
	Menu* menu;
	GameOver* gameOver;

	sf::String playerIPinput;
	sf::Text IPaddrText;

	int windowWidth;
	int windowHeight;
	float displayGameOverTimer;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////