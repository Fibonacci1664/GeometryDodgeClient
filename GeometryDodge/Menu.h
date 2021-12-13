/*
 * This is the Menu class and handles
 *		- Loading the Menu texture, font, and sprite.
 *		- Handling input and changing state on key press 'Enter'
 *
 * Original @author D. Green.
 *
 * © D. Green. 2021.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include <SFML/Network/IpAddress.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Menu : public Screen
{
public:
	Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~Menu();

	void handleInput(float dt);
	void update(float dt, sf::String playerIPinput);
	void render();

private:
	void initMenu();
	void initUI();
	void loadTexture();
	void beginDraw();
	void endDraw();

	void loadFont();

	sf::Font font;
	sf::Text IPaddrPrompt;

	sf::Text IPaddrInputText;
	sf::Text IPaddrText;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	sf::IpAddress localIP;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////