#pragma once
#include "GameState.h"
#include "Screen.h"
#include "Player.h"
#include "UI.h"
#include "Asteroid.h"
#include <list>
#include "Projectile.h"
#include "NetworkManager.h"
#include "UIDataMsg.h"
#include "Projectiles_Data_Packet.h"

class Level : public Screen
{
public:
	Level() {}
	Level(sf::RenderWindow* hwnd, Input* controller_0, GameState* gs);
	~Level();

	void update(float dt) override;
	void render() override;

private:
	//void initDebugMode();
	void initBackground();
	void initUI();
	void initLevel();
	void initPlayer();
	void initAsteroids();

	void updateAsteroids(float dt);
	void updateProjectiles(float dt);

	void renderAsteroids();
	void renderProjectiles();

	void beginDraw();
	void endDraw();

	void loadTexture();

	UI* ui;
	Player* player1;
	std::vector<Asteroid*> asteroids;
	std::vector<Projectile*> projectiles;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	// #### NETWORK STUFF ####
	NetworkManager* network;
	// For player prediction
	std::list<PlayerDataMsg*> playerMsgs;
	// For recv UI data into
	UIDataMsg* uidMsg;
	// For recv asteroid data into
	std::vector<AsteroidDataMsg*> asteroidMsgs;
	std::vector<ProjectileDataMsg*> projectileMsgs;

	Player_UI_Data_Packet playerUIpckt;
	Asteroids_Data_Packet asteroidsPckt;
	Projectiles_Data_Packet projectilesPckt;

	bool isConnected = false;
	bool haveRecvNetUpdate = false;
	bool isDebugMode;
	float localTotalGameTime;
	float syncedTotalGameTime = 0.0f;
	float networkUpdateTimer = 0.0f;
	bool firstRecv = false;
	bool timeSynced = false;
};