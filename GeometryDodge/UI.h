#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "UIDataMsg.h"

class UI
{
public:
	UI();
	~UI();

	void update(float dt, UIDataMsg* uidMsg);
	void render(sf::RenderWindow* window);

	sf::Text* getScoreText();
	int getScore();

private:
	void initUI();
	void loadFont();

	sf::Font font;
	sf::Text scoreText;

	int score;
	int timer;
	float count;
};