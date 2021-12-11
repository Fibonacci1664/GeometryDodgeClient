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

extern sf::IpAddress SERVERIP;

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void connectToServer(int playerNumber);
	Player_UI_Data_Packet receivePlayerUIPacket();
	Asteroids_Data_Packet recevieAsteroidPacket();
	/*UIDataMsg* receiveUIData();
	PlayerDataMsg* receivePlayerData();*/
	//GameWorldData receiveGameWorldData();

private:
	//sf::IpAddress SERVERIP = "127.0.0.1";
	//sf::IpAddress SERVERIP = "192.168.1.118";
	unsigned short SERVERPORT = 5555;
	//std::queue<PlayerDataMsg> playerData;
	std::size_t received;
	sf::TcpSocket tcpSocket;
	sf::SocketSelector selector;


	/*UIDataMsg* UIMsg;
	PlayerDataMsg* playerDataRecv;*/
	Player_UI_Data_Packet playerUIpckt;
	Asteroids_Data_Packet asteroidsPckt;
};

