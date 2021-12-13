/*
 * This is the Observer class and handles
 *		- Initialisation of player object including:
 *				*	Loading textures.
 *				*	Setting up sprite and collision boxes.
 *		- Creation of a network manager.
 *		- Connection to the network.
 *		- Moving/updating player object.
 *		- Carrying out player object prediction.
 *		- Receiving all data from the network
 *
 * Original @author D. Green.
 *
 * © D. Green. 2021.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "PlayerDataMsg.h"
#include "AsteroidDataMsg.h"
#include "NetworkManager.h"
#include "UIDataMsg.h"
#include "Player_UI_Data_Packet.h"
#include "Asteroids_Data_Packet.h"
#include <list>
#include "Projectiles_Data_Packet.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
extern bool printDataToConsole;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Observer
{
public:
	//Observer() {}
	Observer(int playerNum, sf::RenderWindow* hwnd);
	~Observer();

	void connect(int playerNumber);
	void update(float dt, PlayerDataMsg* pdm);

	Player_UI_Data_Packet receivePlayerUIPacket();
	Asteroids_Data_Packet recevieAsteroidPacket();
	Projectiles_Data_Packet recevieProjectilesPacket();
	int receiveGameState();

	void runPredition(float gameTime, std::list<PlayerDataMsg*> playerMsgs);
	
	sf::Sprite* getPlayerSprite();
	sf::Sprite* getPlayerGhost();
	sf::Vector2u* getPlayerSize();
	sf::FloatRect getCollisionBox();
	void setCollisionBox(float x, float y, float width, float height);
	int getPlayerScore();
	void setPlayerScore(int newScore);
	
private:
	sf::Vector2f linearPrediction(float gameTime, const PlayerDataMsg* msg0, const PlayerDataMsg* msg1);
	void initPlayer();
	void initGhost();
	void loadTexture();

	sf::RenderWindow* window;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Sprite playerGhostSprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2u size;
	sf::FloatRect collisionBox;
	std::vector<PlayerDataMsg*> plyrMsgs;

	// ###################################### NETWORK STUFF ######################################
	NetworkManager* network;
	Player_UI_Data_Packet playerUIpckt;
	Asteroids_Data_Packet asteroidsPckt;
	Projectiles_Data_Packet projectilesPckt;
	// ###################################### NETWORK STUFF END ##################################

	unsigned short SERVERPORT = 5555;
	float localTotalGameTime;
	int playerNum;
	float speed;
	int playerScore;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////