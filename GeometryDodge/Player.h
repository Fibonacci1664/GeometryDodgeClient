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

extern bool printDataToConsole;

class Player
{
public:
	Player() {}
	Player(int playerNum, sf::RenderWindow* hwnd);
	~Player();

	void connect(int playerNumber);
	void update(float dt, PlayerDataMsg* pdm);

	Player_UI_Data_Packet receivePlayerUIPacket();
	Asteroids_Data_Packet recevieAsteroidPacket();
	Projectiles_Data_Packet recevieProjectilesPacket();
	int receiveGameState();

	void runPredition(float gameTime, std::list<PlayerDataMsg*> playerMsgs);
	sf::Vector2f linearPrediction(float gameTime, const PlayerDataMsg* msg0, const PlayerDataMsg* msg1);// , const PlayerDataMsg* msg2);
	
	sf::Sprite* getPlayerSprite();
	sf::Sprite* getPlayerGhost();
	sf::Vector2u* getPlayerSize();
	sf::FloatRect getCollisionBox();
	void setCollisionBox(float x, float y, float width, float height);
	int getPlayerScore();
	void setPlayerScore(int newScore);
	
private:
	
	void initPlayer();
	void initGhost();
	void loadTexture();

	Input* input;
	sf::RenderWindow* window;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Sprite playerGhostSprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2u size;
	sf::FloatRect collisionBox;
	std::vector<PlayerDataMsg*> plyrMsgs;

	// #### NETWORK STUFF ####
	NetworkManager* network;
	UIDataMsg* UIMsg;
	PlayerDataMsg* playerDataRecv;
	AsteroidDataMsg asteroidMsg;
	Player_UI_Data_Packet playerUIpckt;
	Asteroids_Data_Packet asteroidsPckt;
	Projectiles_Data_Packet projectilesPckt;

	unsigned short SERVERPORT = 5555;
	float localTotalGameTime;
	int playerNum;
	float speed;
	bool echoRecvd;
	int playerScore = 0;
};