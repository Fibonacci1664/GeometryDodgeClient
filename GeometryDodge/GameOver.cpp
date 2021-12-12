#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow* hwnd, Input* in, GameState* gs) : Screen(hwnd, in, gs)
{
	initGameOver();
}

GameOver::~GameOver()
{

}

void GameOver::initGameOver()
{
	loadTexture();
	bgTexture.setSmooth(true);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(5.0f, 2.8125f);

	initUI();
}

void GameOver::initUI()
{
	loadFont();

	gameOverText.setFont(font);
	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(64);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(1.0f);
	gameOverText.setPosition(window->getSize().x * 0.36f, window->getSize().y * 0.43f);
}

void GameOver::loadFont()
{
	if (!font.loadFromFile("res/fonts/kenvector_future_thin.ttf"))
	{
		std::cout << "Error loading font\n";
	}
}

void GameOver::loadTexture()
{
	if (!bgTexture.loadFromFile("res/gfx/bg/blue.png"))
	{
		std::cout << "Error loading background texture.\n";
	}
}

void GameOver::handleInput(float dt)
{
}

void GameOver::update(float dt)
{

}

void GameOver::render()
{
	beginDraw();
	window->draw(bgSprite);
	window->draw(gameOverText);
	endDraw();
}

void GameOver::beginDraw()
{
	window->clear(sf::Color::Black);
}

void GameOver::endDraw()
{
	window->display();
}
