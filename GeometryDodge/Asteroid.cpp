#include "Asteroid.h"
#include <iostream>
#include <cstdlib>


Asteroid::Asteroid(sf::RenderWindow* hwnd) : window(hwnd)
{
	position = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	speed = 200.0f;
	randXPos = rand() % 1780 + 50;
	randYPos = rand() % 620 + 50;

	initAsteroid();
}

Asteroid::~Asteroid()
{
	
}

void Asteroid::update(float dt, AsteroidDataMsg* asteroidMsg)
{
	//move();
	velocity.x = asteroidMsg->x - asteroidSprite.getPosition().x;
	velocity.y = asteroidMsg->y - asteroidSprite.getPosition().y;
	asteroidSprite.setPosition(asteroidSprite.getPosition() + velocity);
	//asteroidSprite.move(sf::Vector2f(gwd.x * speed * dt, gwd.y * speed * dt));
	collisionBox = sf::FloatRect(asteroidSprite.getPosition().x - size.x * 0.5f, asteroidSprite.getPosition().y - size.y * 0.5f, size.x, size.y);
	checkScreenBounds();
}

void Asteroid::render(sf::RenderWindow* window)
{
	window->draw(asteroidSprite);
}

void Asteroid::initAsteroid()
{
	loadTexture();
	asteroidTexture.setSmooth(true);
	asteroidSprite.setTexture(asteroidTexture);
	size = asteroidTexture.getSize();
	asteroidSprite.setOrigin(size.x * 0.5f, size.y * 0.5f);
	//asteroidSprite.setPosition(sf::Vector2f(randXPos, randYPos));
	//asteroidSprite.setScale(0.75f, 0.75f);
	//velocity = sf::Vector2f(2.5f, 2.5f);
	collisionBox = sf::FloatRect(asteroidSprite.getPosition().x - size.x * 0.5f, asteroidSprite.getPosition().y - size.y * 0.5f, size.x, size.y);
}

void Asteroid::loadTexture()
{
	if (!asteroidTexture.loadFromFile("res/gfx/asteroids/asterGreySml.png"))
	{
		std::cout << "Error loading asteroid texture\n";
	}
}

void Asteroid::checkScreenBounds()
{
	// If we hit the left or right edges of the screen
	if ((asteroidSprite.getPosition().x + (size.x * 0.5f) > window->getSize().x && velocity.x > 0) ||
		(asteroidSprite.getPosition().x - (size.x * 0.5f) < 0 && velocity.x < 0))
	{
		// Bounce off by negating the current velocity
		velocity.x = -velocity.x;
	}

	// If we hit the top or btm edges of the screen
	if ((asteroidSprite.getPosition().y + (size.y * 0.5f) > window->getSize().y && velocity.y > 0) ||
		(asteroidSprite.getPosition().y - (size.y * 0.5f) < 0 && velocity.y < 0))
	{
		// Bounce off by negating the current velocity
		velocity.y = -velocity.y;
	}
}

void Asteroid::move()
{
	asteroidSprite.setPosition(asteroidSprite.getPosition() + velocity);
}

sf::Sprite* Asteroid::getAsteroidSprite()
{
	return &asteroidSprite;
}

sf::FloatRect Asteroid::getCollisionBox()
{
	return collisionBox;
}

void Asteroid::setCollisionBox(float x, float y, float width, float height)
{
	collisionBox = sf::FloatRect(x, y, width, height);
}
