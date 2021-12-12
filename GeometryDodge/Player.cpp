#include "Player.h"
#include <iostream>

Player::Player(int playerNum, sf::RenderWindow* hwnd) : playerNum(playerNum), window(hwnd)
{
	position = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	speed = 700.0f;
	echoRecvd = false;
	localTotalGameTime = 0.0f;

	initPlayer();
	initGhost();
}

Player::~Player()
{

}

void Player::connect(int playerNumber)
{
	network = new NetworkManager();
	network->connectToServer(playerNumber);
}

Player_UI_Data_Packet Player::receivePlayerUIPacket()
{
	playerUIpckt = network->receivePlayerUIPacket();

	return playerUIpckt;
}

Asteroids_Data_Packet Player::recevieAsteroidPacket()
{
	asteroidsPckt = network->recevieAsteroidPacket();

	return asteroidsPckt;
}

Projectiles_Data_Packet Player::recevieProjectilesPacket()
{
	projectilesPckt = network->recevieProjectilesPacket();

	return projectilesPckt;
}

int Player::receiveGameState()
{
	return network->receiveGameState();
}

void Player::update(float dt, PlayerDataMsg* pdm)
{
	// Update the player with data from server
	playerSprite.setPosition(sf::Vector2f(pdm->x, pdm->y));
	collisionBox = sf::FloatRect(playerSprite.getPosition().x - size.x * 0.4f, playerSprite.getPosition().y - size.y * 0.4f, size.x * 0.8f, size.y * 0.8f);
}

void Player::initPlayer()
{
	// Techinacally none of these values below really matter, as they are just initialiser values
	// Make sure the rendered values are from the network updates
	loadTexture();
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	size = playerTexture.getSize();
	playerSprite.setOrigin(size.x * 0.5f, size.y * 0.5f);
	playerSprite.setPosition(sf::Vector2f(640.0f, 640.0f));
	playerSprite.setScale(0.75f, 0.75f);
	collisionBox = sf::FloatRect(playerSprite.getPosition().x - size.x * 0.4f, playerSprite.getPosition().y - size.y * 0.4f, size.x * 0.8f, size.y * 0.8f);
}

void Player::initGhost()
{
	// Start the ghost in exactly the same position as the player
	playerGhostSprite.setTexture(playerTexture);
	playerGhostSprite.setColor(sf::Color(255, 255, 255, 128));
	playerGhostSprite.setOrigin(size.x * 0.5f, size.y * 0.5f);
	playerGhostSprite.setPosition(sf::Vector2f(645.0f, 645.0f));
	playerGhostSprite.setScale(0.75f, 0.75f);
}

void Player::loadTexture()
{
	if (!playerTexture.loadFromFile("res/gfx/ships/altShip_" + std::to_string(playerNum) + ".png"))
	{
		std::cout << "Error loading ship texture " << playerNum << '\n';
	}
}

void Player::runPredition(float gameTime, std::list<PlayerDataMsg*> playerMsgs)
{
	// Clear any old data, so we don't accumulate old data we don't need.
	plyrMsgs.clear();

	// Copy from list into vec, for ease of indexing
	for (auto it = playerMsgs.begin(); it != playerMsgs.end(); ++it)
	{
		plyrMsgs.push_back(*it);
	}

	float predictedX = -1.0f;
	float predictedY = -1.0f;

	const int msize = plyrMsgs.size();

	const PlayerDataMsg* msg0 = plyrMsgs[size_t(msize) - 1];		// Latest msg
	const PlayerDataMsg* msg1 = plyrMsgs[size_t(msize) - 2];

	sf::Vector2f predictedVec = linearPrediction(gameTime, msg0, msg1);// , msg2);

	predictedX = predictedVec.x;
	predictedY = predictedVec.y;

	if (printDataToConsole)
	{
		std::cout << "\n############### PLAYER PREDICTIONS ###############\n";

		std::cout << "\n\tPLAYER POSITION RECEIVED - X: " << msg0->x << ", Y: " << msg0->y << '\n'
				  << "\tTIME RECEIVED: " << msg0->timeSent << '\n';

		printf("\n\tPLAYER PREDICTED POSITION: (%.2f, %.2f), Time = %.2f\n", predictedX, predictedY, gameTime);

		std::cout << "\n############### PLAYER PREDICTIONS END ###############\n";
	}

	// Ghost is for visualising the prediction actually working
	playerGhostSprite.setPosition(sf::Vector2f(predictedX, predictedY));

	// Use this to set the actual player to the predicted position
	//playerSprite.setPosition(sf::Vector2f(predictedX, predictedY));
}

sf::Vector2f Player::linearPrediction(float gameTime, const PlayerDataMsg* msg0, const PlayerDataMsg* msg1)
{
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	// LINEAR MODEL (VEL ONLY) using s = vt
	sf::Vector2f deltaPos = sf::Vector2f(msg0->x - msg1->x, msg0->y - msg1->y);
	float deltaTime = msg0->timeSent - msg1->timeSent;
	sf::Vector2f speed = sf::Vector2f((deltaPos.x / deltaTime), (deltaPos.y / deltaTime));
	sf::Vector2f displacement = speed * deltaTime;

	sf::Vector2f nextPos = sf::Vector2f(msg0->x + displacement.x, msg0->y + displacement.y);

	predictedX = nextPos.x;
	predictedY = nextPos.y;

	return sf::Vector2f(predictedX, predictedY);
}

sf::Sprite* Player::getPlayerSprite()
{
	return &playerSprite;
}

sf::Sprite* Player::getPlayerGhost()
{
	return &playerGhostSprite;
}

sf::Vector2u* Player::getPlayerSize()
{
	return &size;
}

sf::FloatRect Player::getCollisionBox()
{
	return collisionBox;
}

void Player::setCollisionBox(float x, float y, float width, float height)
{
	collisionBox = sf::FloatRect(x, y, width, height);
}

int Player::getPlayerScore()
{
	return 0;
}

void Player::setPlayerScore(int newScore)
{
	playerScore = newScore;
}
