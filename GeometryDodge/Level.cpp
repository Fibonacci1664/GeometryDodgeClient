#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* controller_0, GameState* gs) :
	Screen(hwnd, controller_0, gs)
{
	localTotalGameTime = 0.0f;

	uidMsg = new UIDataMsg;

	initLevel();

	playerUIpckt.uiData = *uidMsg;
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

void Level::updateAsteroids(float dt)
{
	if (asteroidMsgs.size() > 0)
	{
		for (int i = 0; i < asteroids.size(); i++)
		{
			// Always update using back as that's the latest msg
			asteroids[i]->update(dt, asteroidMsgs[i]);
		}
	}
}

void Level::updateProjectiles(float dt)
{
	if (projectileMsgs.size() > 0)
	{
		for (int i = 0; i < projectiles.size(); i++)
		{
			// Always update using back as that's the latest msg
			projectiles[i]->update(dt, projectileMsgs[i]);
		}
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
	// ######### PLAYER #########
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
	// ######### PLAYER END #########

	// ######### ASTEROIDS #########
	asteroidsPckt = player1->recevieAsteroidPacket();

	if (asteroidMsgs.size() > 0)
	{
		// Clear the old data before refilling with latest data
		asteroidMsgs.clear();
	}

	if (asteroids.size() > 0)
	{
		// Delete all the old asteroids
		for (int i = 0; i < asteroids.size(); ++i)
		{
			if (asteroids[i])
			{
				delete asteroids[i];
				asteroids[i] = nullptr;
			}
		}

		// Clear the asteroid vector
		asteroids.clear();
	}

	// Fill the local vector with all the astroid data from the network packet
	for (int i = 0; i < asteroidsPckt.asteroidDataMsgs.size(); ++i)
	{
		// Fill with latest data
		asteroidMsgs.push_back(asteroidsPckt.asteroidDataMsgs[i]);

		// Create as many asteroids as there have been msgs recvd, this is currently a 1 to 1 relationship to keep things simple
		asteroids.push_back(new Asteroid(window));
	}

	// ######### ASTEROIDS END #########

	// ######### PROJECTILES #########
	projectilesPckt = player1->recevieProjectilesPacket();

	if (projectileMsgs.size() > 0)
	{
		// Clear the old data before refilling with latest data
		projectileMsgs.clear();
	}

	if (projectiles.size() > 0)
	{
		// Delete all the old projectiles
		for (int i = 0; i < projectiles.size(); ++i)
		{
			if (projectiles[i])
			{
				delete projectiles[i];
				projectiles[i] = nullptr;
			}
		}

		// Clear the projectiles vector
		projectiles.clear();
	}

	// Fill the local vector with all the projectile data from the network packet
	for (int i = 0; i < projectilesPckt.projectileDataMsgs.size(); ++i)
	{
		// Fill with latest data
		projectileMsgs.push_back(projectilesPckt.projectileDataMsgs[i]);

		// Create as many projectiles as there have been msgs recvd, this is currently a 1 to 1 relationship to keep things simple
		// Spawned at the position that has been passed
		projectiles.push_back(new Projectile(window, sf::Vector2f(projectileMsgs[i]->x, projectileMsgs[i]->y)));
	}

	// ######### PROJECTILES END #########

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

	updateAsteroids(dt);
	updateProjectiles(dt);

	//// Check this after ALL other recvs are complete
	//int currentGameState = player1->receiveGameState();

	//if (currentGameState == 2)
	//{
	//	gameState->setCurrentState(State::GAMEOVER);
	//}
}

void Level::renderAsteroids()
{
	// Draw all the asteroids
	for (int i = 0; i < asteroids.size(); i++)
	{
		window->draw(*asteroids[i]->getAsteroidSprite());
	}
}

void Level::renderProjectiles()
{
	// Draw all the projectiles
	for (int i = 0; i < projectiles.size(); i++)
	{
		window->draw(*projectiles[i]->getProjectileSprite());
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
	renderProjectiles();

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