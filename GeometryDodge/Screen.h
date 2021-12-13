/*
 * This is the parent class of all other 'screens'.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2021.
 */

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES.
#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include "Input.h"
#include "GameState.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Screen
{
public:
	Screen();
	Screen(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~Screen();

	virtual void handleInput(float dt);
	virtual void update(float dt);
	virtual void render();

	virtual State getGameState();
	virtual void setGameState(State s);

protected:
	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////