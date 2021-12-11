#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs) : Screen(hwnd, in, gs)
{
	initMenu();
}

Menu::~Menu()
{

}

void Menu::initMenu()
{
	loadTexture();
	bgTexture.setSmooth(true);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(5.0f, 2.8125f);

	initUI();
}

void Menu::initUI()
{
	loadFont();

	IPaddrPrompt.setFont(font);
	IPaddrPrompt.setString("Please Input IP to Connect To:> ");
	IPaddrPrompt.setCharacterSize(32);
	IPaddrPrompt.setFillColor(sf::Color::Red);
	IPaddrPrompt.setOutlineColor(sf::Color::Black);
	IPaddrPrompt.setOutlineThickness(1.0f);
	IPaddrPrompt.setPosition(window->getSize().x * 0.18f, window->getSize().y * 0.45f);
	
	IPaddrInputText.setFont(font);
	IPaddrInputText.setCharacterSize(32);
	IPaddrInputText.setFillColor(sf::Color::Red);
	IPaddrInputText.setOutlineColor(sf::Color::Black);
	IPaddrInputText.setOutlineThickness(1.0f);

	IPaddrText.setFont(font);
	IPaddrText.setString("Server IP:> " + localIP.getLocalAddress().toString());
	IPaddrText.setCharacterSize(32);
	IPaddrText.setFillColor(sf::Color::Red);
	IPaddrText.setOutlineColor(sf::Color::Black);
	IPaddrText.setOutlineThickness(1.0f);
	IPaddrText.setPosition(window->getSize().x * 0.33f, window->getSize().y * 0.05f);
}

void Menu::loadFont()
{
	if (!font.loadFromFile("res/fonts/kenvector_future_thin.ttf"))
	{
		std::cout << "Error loading font\n";
	}
}

void Menu::loadTexture()
{
	if (!bgTexture.loadFromFile("res/gfx/bg/blue.png"))
	{
		std::cout << "Error loading background texture.\n";
	}
}

void Menu::handleInput(float dt)
{
	// Check the bool key array in the input class to see if the index corrosponding
	// to the Enter/Return key is true, i.e. the key has been pressed
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		setGameState(State::LEVEL);
	}
}

void Menu::update(float dt, sf::String playerIPinput)
{
	IPaddrInputText.setString(playerIPinput);
	IPaddrInputText.setPosition(window->getSize().x * 0.68f, window->getSize().y * 0.45f);
}

void Menu::render()
{
	beginDraw();
	window->draw(bgSprite);
	window->draw(IPaddrPrompt);
	window->draw(IPaddrInputText);
	window->draw(IPaddrText);
	endDraw();
}

void Menu::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Menu::endDraw()
{
	window->display();
}
