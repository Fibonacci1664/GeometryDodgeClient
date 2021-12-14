/*
 * This is the Network Manager class and handles
 *		- Connects to Server.
 *      - Receives all incoming data and returns this to the Observer and by extension the Level.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2021.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <queue>
#include "PlayerDataMsg.h"
#include "AsteroidDataMsg.h"
#include "UIDataMsg.h"
#include "Player_UI_Data_Packet.h"
#include "Asteroids_Data_Packet.h"
#include "Projectiles_Data_Packet.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
extern sf::IpAddress SERVERIP;
extern bool printDataToConsole;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void connectToServer(int playerNumber);

	void sendForEcho();

	Player_UI_Data_Packet receivePlayerUIPacket();
	Asteroids_Data_Packet recevieAsteroidPacket();
	Projectiles_Data_Packet recevieProjectilesPacket();
	int receiveEcho();
	int receiveGameState();

private:
	//sf::IpAddress SERVERIP = "127.0.0.1";
	//sf::IpAddress SERVERIP = "192.168.1.118";
	unsigned short SERVERPORT = 5555;
	std::size_t received;
	sf::TcpSocket tcpSocket;
	sf::SocketSelector selector;

	Player_UI_Data_Packet playerUIpckt;
	Asteroids_Data_Packet asteroidsPckt;
	Projectiles_Data_Packet projectilesPckt;
	int gameState;
	int echo;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////