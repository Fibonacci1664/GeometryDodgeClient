#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* controller_0, GameState* gs) :
	Screen(hwnd, controller_0, gs)
{
	isDebugMode = true;
	localTotalGameTime = 0.0f;

	//pdMsg = new PlayerDataMsg;
	uidMsg = new UIDataMsg;

	initLevel();

	playerUIpckt.uiData = *uidMsg;
	//playerUIpckt.playerData = *pdMsg;
	//gdpckt.asteroidDataMsgs;

	if (isDebugMode)
	{
		initDebugMode();
	}
}

Level::~Level()
{
	if (ui)
	{
		delete ui;
		ui = nullptr;
	}

	if (player1)
	{
		delete player1;
		player1 = nullptr;
	}

	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (asteroids[i])
		{
			delete asteroids[i];
			asteroids[i] = nullptr;
		}
	}

	/*for (int i = 0; i < projectiles.size(); ++i)
	{
		if (projectiles[i])
		{
			delete projectiles[i];
			projectiles[i] = nullptr;
		}
	}*/

	/*if (pdMsg)
	{
		delete pdMsg;
		pdMsg = nullptr;
	}*/

	if (uidMsg)
	{
		delete uidMsg;
		uidMsg = nullptr;
	}
}

void Level::initLevel()
{
	initBackground();
	initUI();
	initPlayer();
	initAsteroids();
}

void Level::initDebugMode()
{
	// Player debug collision box
	player1ColBox.setFillColor(sf::Color(0, 0, 0, 0));
	player1ColBox.setOutlineColor(sf::Color::Red);
	player1ColBox.setOutlineThickness(1.0f);

	// Set the collision box origin to be the top left of the sprites local coords, this is
	// based on the already defined collision box which was defined during object creation
	player1ColBox.setPosition(sf::Vector2f(player1->getCollisionBox().left, player1->getCollisionBox().top));
	player1ColBox.setSize(sf::Vector2f(player1->getCollisionBox().width, player1->getCollisionBox().height));

	// Create a new asteroid collision box
	asteroidColBoxes.push_back(sf::RectangleShape());

	// Asteroids debug collision boxes
	asteroidColBoxes[0].setFillColor(sf::Color(0, 0, 0, 0));
	asteroidColBoxes[0].setOutlineColor(sf::Color::Magenta);
	asteroidColBoxes[0].setOutlineThickness(1.0f);

	// Set the collision box origin to be the top left of the sprites local coords, this is
	// based on the already defined collision box which was defined during object creation
	asteroidColBoxes[0].setPosition(sf::Vector2f(asteroids[0]->getCollisionBox().left, asteroids[0]->getCollisionBox().top));
	asteroidColBoxes[0].setSize(sf::Vector2f(asteroids[0]->getCollisionBox().width, asteroids[0]->getCollisionBox().height));
}

void Level::initBackground()
{
	loadTexture();
	bgTexture.setSmooth(true);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(5.0f, 2.8125f);
}

void Level::initUI()
{
	ui = new UI;
}

void Level::initPlayer()
{
	player1 = new Player(1, window);
}

void Level::initAsteroids()
{
	asteroids.push_back(new Asteroid(window));
}

void Level::spawnNewAsteroid()
{
	// If we get here it means the wave count was incremented, so spawn an asteroid
	asteroids.push_back(new Asteroid(window));
	createNewAsteroidColBox();
}

void Level::updateAsteroids(float dt)
{



	//Update all the asteroids using the data from the server
	//for (int i = 0; i < asteroids.size(); ++i)
	//{
	//	bool oob = asteroids[i]->update(dt);

	//	if (oob)
	//	{
	//		std::cout << "Update - Asteroid vector size is " << asteroids.size() << '\n';

	//		// Create an iterator to the asteroid that has gone oob, as the asteroids all fall at the same speed
	//		// it will always be the first in the list
	//		auto iter1 = asteroids.begin();
	//		// Erase it from the vector
	//		asteroids.erase(iter1);

	//		// Ensure collision box for this asteroid is also removed from the collision box vector
	//		auto iter2 = asteroidColBoxes.begin();
	//		asteroidColBoxes.erase(iter2);


	//		// Decrement the player score
	//		player1->setPlayerScore(player1->getPlayerScore() - 1);

	//		std::cout << "Update - Asteroid vector size is now " << asteroids.size() << '\n';
	//	}
	//}
}

//void Level::updateProjectiles(float dt)
//{
//	// Update all the projectiles using the data from the server
//	for (int i = 0; i < projectiles.size(); ++i)
//	{
//		bool oob = projectiles[i]->update(dt);
//
//		if (oob)
//		{
//			std::cout << "Update - Projectile vector size is " << projectiles.size() << '\n';
//
//			// Create an iterator to the asteroid that has gone oob, as the asteroids all fall at the same speed
//			// it will always be the first in the list
//			auto iter1 = projectiles.begin();
//			// Erase it from the vector
//			projectiles.erase(iter1);
//
//			// Ensure collision box for this asteroid is also removed from the collision box vector
//			auto iter2 = projectileColBoxes.begin();
//			projectileColBoxes.erase(iter2);
//
//			std::cout << "Update - Projectile vector size is now " << projectiles.size() << '\n';
//		}
//	}
//}

void Level::updateDebugMode()
{
	// As these collision boxes are based off of sprites that have already been update using data
	// from the server there is nothing more to do here
	if (isDebugMode)
	{
		// Update the players collision box
		player1ColBox.setPosition(sf::Vector2f(player1->getCollisionBox().left, player1->getCollisionBox().top));

		// Update all the asteroids collision boxes
		for (int i = 0; i < asteroidColBoxes.size(); ++i)
		{
			asteroidColBoxes[i].setPosition(sf::Vector2f(asteroids[i]->getCollisionBox().left, asteroids[i]->getCollisionBox().top));
		}

		// Update all the asteroids collision boxes
		/*for (int i = 0; i < projectileColBoxes.size(); ++i)
		{
			projectileColBoxes[i].setPosition(sf::Vector2f(projectiles[i]->getCollisionBox().left, projectiles[i]->getCollisionBox().top));
		}*/
	}
}

void Level::update(float dt)
{
	if (!isConnected)
	{
		player1->connect(1);
		isConnected = true;
	}

	// Local totalGameTime
	localTotalGameTime += dt;
	// Keep updating the synced time with the local delta time
	syncedTotalGameTime += dt;

	// ############### NETWORK UPDATE ###############
	playerUIpckt = player1->receivePlayerUIPacket();

	// Sync the game time using the time from the first player data msg recvd, This only happens ONCE
	if (!timeSynced)
	{
		// This is req for prediction
		syncedTotalGameTime = playerUIpckt.playerData.timeSent;
		timeSynced = true;
	}
	
	uidMsg = &playerUIpckt.uiData;

	// Create a unique mem addr for this data
	PlayerDataMsg* pdMsg = new PlayerDataMsg;
	// Fill this mem address with the latest player data from the network
	*pdMsg = playerUIpckt.playerData;
	
	// Add the current player data msg to the list of player data messages
	playerMsgs.push_back(pdMsg);

	// Only keep the last 5 player data msgs
	if (playerMsgs.size() > 5)
	{
		// Always pop front as that's the oldest msg
		playerMsgs.pop_front();
	}

	asteroidsPckt = player1->recevieAsteroidPacket();

	// Fill the local vector with all the astroid data from the network packet
	for (int i = 0; i < asteroidsPckt.asteroidDataMsgs.size(); ++i)
	{
		asteroidMsgs.push_back(asteroidsPckt.asteroidDataMsgs[i]);
	}

	// ############### LOCAL UPDATE ###############
	if (uidMsg)
	{
		ui->update(dt, uidMsg);
	}

	if (pdMsg)
	{
		// Update player with latest msg
		player1->update(dt, playerMsgs.back());

		// Don't try and run any prediction until we have at least 3 msgs
		if (playerMsgs.size() >= 3)
		{
			// Update ghost using the past 3 player data msgs to run prediction
			player1->runPredition(syncedTotalGameTime, playerMsgs);
		}
	}

	if (asteroidMsgs.size() > 0)
	{
		for (int i = 0; i < asteroids.size(); i++)
		{
			// Always update using back as that's the latest msg
			asteroids[i]->update(dt, asteroidMsgs.back());
		}
	}

	/*updateAsteroids(dt);
	updateProjectiles(dt);*/
	//updateDebugMode();

	/*if (player1->getPlayerScore() < 0)
	{
		gameState->setCurrentState(State::GAMEOVER);
	}

	if (asteroidSpawnTime >= 1.0f)
	{
		spawnNewAsteroid();
		asteroidSpawnTime = 0.0f;
	}*/
}

void Level::renderAsteroids()
{
	// Draw all the asteroids
	for (int i = 0; i < asteroids.size(); i++)
	{
		window->draw(*asteroids[i]->getAsteroidSprite());
	}
}

//void Level::renderProjectiles()
//{
//	// Draw all the projectiles
//	for (int i = 0; i < projectiles.size(); i++)
//	{
//		window->draw(*projectiles[i]->getProjectileSprite());
//	}
//}

void Level::renderDebugMode()
{
	// Draw all the debug magenta collision boxes
	if (isDebugMode)
	{
		window->draw(player1ColBox);

		/*for (int i = 0; i < asteroidColBoxes.size(); ++i)
		{
			window->draw(asteroidColBoxes[i]);
		}

		for (int i = 0; i < projectileColBoxes.size(); ++i)
		{
			window->draw(projectileColBoxes[i]);
		}*/
	}
}

void Level::render()
{
	beginDraw();

	// Render stuff here
	window->draw(bgSprite);
	window->draw(*ui->getScoreText());
	window->draw(*player1->getPlayerSprite());
	window->draw(*player1->getPlayerGhost());

	renderAsteroids();
	//renderProjectiles();

	

	//renderDebugMode();

	endDraw();
}

void Level::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Level::endDraw()
{
	window->display();
}

void Level::loadTexture()
{
	if (!bgTexture.loadFromFile("res/gfx/bg/blue.png"))
	{
		std::cout << "Error loading background texture.\n";
	}
}

void Level::checkCollisions()
{
	// If player collides with an asteroid, set GAME_OVER state
	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (player1->getCollisionBox().intersects(asteroids[i]->getCollisionBox()))
		{
			gameState->setCurrentState(State::GAMEOVER);
		}
	}
}

void Level::createNewAsteroidColBox()
{
	// Create a new asteroid collision box
	asteroidColBoxes.push_back(sf::RectangleShape());

	// Access the last element in the vector, i.e. the one we just pushed back
	int index = asteroidColBoxes.size() - 1;

	asteroidColBoxes[index].setFillColor(sf::Color(0, 0, 0, 0));
	asteroidColBoxes[index].setOutlineColor(sf::Color::Magenta);
	asteroidColBoxes[index].setOutlineThickness(1.0f);

	// Set the collision box origin to be the top left of the sprites local coords, this is
	// based on the already defined collision box which was defined during object creation
	asteroidColBoxes[index].setPosition(sf::Vector2f(asteroids[index]->getCollisionBox().left, asteroids[index]->getCollisionBox().top));
	asteroidColBoxes[index].setSize(sf::Vector2f(asteroids[index]->getCollisionBox().width, asteroids[index]->getCollisionBox().height));
}