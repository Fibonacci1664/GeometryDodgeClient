/*
 * This is the UI class and handles
 *		- Initialisation of UI elements.
 *		- Rendering of the UI.
 *		- Updating the UI with the correct score.
 *
 * Original @author D. Green.
 *
 * � D. Green. 2021.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include "UI.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORS / DESTRUCTORS
UI::UI()
{
	score = 0;

	initUI();
}

UI::~UI()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS
void UI::initUI()
{
	loadFont();

	// Set up the SCORE text
	scoreText.setFont(font);
	scoreText.setString("SCORE: " + std::to_string(score));
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(1.0f);
	scoreText.setPosition(20.0f, 15.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::loadFont()
{
	if (!font.loadFromFile("res/fonts/kenvector_future_thin.ttf"))
	{
		std::cout << "Error loading font\n";
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::update(float dt, UIDataMsg* uidMsg)
{
	score = uidMsg->score;
	scoreText.setString("SCORE: " + std::to_string(score));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::render(sf::RenderWindow* window)
{
	window->draw(scoreText);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Text* UI::getScoreText()
{
	return &scoreText;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int UI::getScore()
{
	return score;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////