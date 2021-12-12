#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"

class GameOver : public Screen
{
public:
	GameOver(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~GameOver();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	void initGameOver();
	void initUI();
	void loadTexture();
	void beginDraw();
	void endDraw();

	void loadFont();

	sf::Font font;
	sf::Text gameOverText;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;
};