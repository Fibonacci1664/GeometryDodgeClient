#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
    /*playerDataRecv = new PlayerDataMsg;
    UIMsg = new UIDataMsg;

    playerDataRecv = nullptr;
    UIMsg = nullptr;*/
}

NetworkManager::~NetworkManager()
{
   /* if (playerDataRecv)
    {
        delete playerDataRecv;
        playerDataRecv = nullptr;
    }*/
}

void NetworkManager::connectToServer(int observerNum)
{
    // Create TCP  
    sf::Time timeout = sf::seconds(10.0f);
    sf::Socket::Status socketStatus = tcpSocket.connect(SERVERIP, SERVERPORT, timeout);

    if (socketStatus != sf::Socket::Done)
    {
        std::cout << "Not connected!\n";
    }
    else
    {
        std::cout << "Observer: " << observerNum << " has connected to server port number : " << SERVERPORT
            << "\nFrom local port number: " << tcpSocket.getLocalPort()
            << "\nAnd Server IP number: " << tcpSocket.getRemoteAddress() << '\n';
    }

    selector.add(tcpSocket);
}

Player_UI_Data_Packet NetworkManager::receivePlayerUIPacket()
{
    if (selector.wait())
    {
        if (selector.isReady(tcpSocket))
        {
            std::cout << "\n############### PLAYER AND UI DATA ###############\n\n";

            if (tcpSocket.receive(&playerUIpckt, sizeof(Player_UI_Data_Packet), received) != sf::Socket::Done)
            {
                std::cout << "Client side error receiving ta using TCP!\n";
                return playerUIpckt;
            }

            //std::cout << "Client side received: " << received << " bytes\n";

            std::cout << "Score: " << playerUIpckt.uiData.score << "\n";

            std::cout << "Player " << playerUIpckt.playerData.playerID << "\n"
                << "Msg time sent: " << playerUIpckt.playerData.timeSent << '\n'
                << "Player X: " << playerUIpckt.playerData.x << '\n'
                << "Player Y: " << playerUIpckt.playerData.y << '\n';

            std::cout << "\n############### PLAYER AND UI DATA END ###############\n";
        }
    }

    return playerUIpckt;
}

Asteroids_Data_Packet NetworkManager::recevieAsteroidPacket()
{
    //sf::seconds(0.01f)

    if (selector.wait())
    {
        if (selector.isReady(tcpSocket))
        {
            std::cout << "\n############### ASTEROID VECTOR SIZE DATA ###############\n\n";

            // Carry out a recv of the asteroid data msg vector size, this is just a single int
            if (tcpSocket.receive(&asteroidsPckt.asteroidDataMsgSize, sizeof(int), received) != sf::Socket::Done)
            {
                std::cout << "Client side error receiving asteroids msgs vector size using TCP!\n";
                return asteroidsPckt;
            }
            else
            {
                std::cout << "Asteroid data msg vector size: " << asteroidsPckt.asteroidDataMsgSize << '\n';
            }

            std::cout << "\n############### ASTEROID VECTOR SIZE DATA END ###############\n";

            int size = asteroidsPckt.asteroidDataMsgSize;

            std::cout << "\n############### ALL ASTEROID DATA ###############\n";

            if (size == 0)
            {
                std::cout << "\n############### NO ASTEROID DATA TO RECEIVE ###############\n\n";
            }

            // As we recv the latest 5 msgs everytime we need to clear the old data before repopulating the vec
            // Otherwise we end up with duplicates.
            asteroidsPckt.asteroidDataMsgs.clear();

            // Carry out a loop to recv all asteroid data from the packet
            for (int i = 0; i < size; ++i)
            {
                AsteroidDataMsg* asteroidMsg = new AsteroidDataMsg;

                // Carry out a recv of the asteroid data msg
                if (tcpSocket.receive(asteroidMsg, sizeof(AsteroidDataMsg), received) != sf::Socket::Done)
                {
                    std::cout << "Client side error receiving asteroids msgs using TCP!\n";
                    return asteroidsPckt;
                }

                asteroidsPckt.asteroidDataMsgs.push_back(asteroidMsg);

                std::cout << "\n############### ASTEROID " << asteroidsPckt.asteroidDataMsgs[i]->asteroidID << " MSG DATA ###############\n\n";

                // Print out to make sure what has been recvd is the same data
                std::cout << "Asteroid ID: " << asteroidsPckt.asteroidDataMsgs[i]->asteroidID << '\n'
                          << "Msg time sent: " << asteroidsPckt.asteroidDataMsgs[i]->timeSent << '\n'
                          << "Asteroid X: " << asteroidsPckt.asteroidDataMsgs[i]->x << '\n'
                          << "Asteroid Y: " << asteroidsPckt.asteroidDataMsgs[i]->y << '\n'
                          << "Bytes received: " << received << "\n";

                std::cout << "\n############### ASTEROID " << asteroidsPckt.asteroidDataMsgs[i]->asteroidID << " MSG DATA END ###############\n";
            }

            // Finally set the size in the Asteroid Data Packet to be the correct size
            asteroidsPckt.asteroidDataMsgSize = asteroidsPckt.asteroidDataMsgs.size();
        }
    }

    return asteroidsPckt;
}

//UIDataMsg* NetworkManager::receiveUIData()
//{
//    if (selector.wait(sf::seconds(0.01f)))
//    {
//        if (selector.isReady(tcpSocket))
//        {
//            std::cout << "About to recv UI data\n";
//
//            if (tcpSocket.receive(UIMsg, sizeof(UIDataMsg), received) != sf::Socket::Done)
//            {
//                std::cout << "Client side error receiving UI Data using TCP!\n";
//                return UIMsg;
//            }
//
//            std::cout << "Client side received: " << received << " bytes\n";
//
//            std::cout << "Score: " << UIMsg->score << '\n';
//        }
//    }
//
//    return UIMsg;
//}
//
//PlayerDataMsg* NetworkManager::receivePlayerData()
//{
//    if (selector.wait(sf::seconds(0.01f)))
//    {
//        if (selector.isReady(tcpSocket))
//        {
//            std::cout << "About to recv player data\n";
//
//            if (tcpSocket.receive(playerDataRecv, sizeof(PlayerDataMsg), received) != sf::Socket::Done)
//            {
//                std::cout << "Client side error receiving Player Data using TCP!\n";
//                return playerDataRecv;
//            }
//
//            std::cout << "Client side received: " << received << " bytes\n";
//
//            std::cout << "Player ID: " << playerDataRecv->playerID << '\n'
//                << "Msg time sent: " << playerDataRecv->timeSent << '\n'
//                << "Player X: " << playerDataRecv->x << '\n'
//                << "Player Y: " << playerDataRecv->y << '\n';
//        }
//    }
//
//    return playerDataRecv;
//}

//GameWorldData NetworkManager::receiveGameWorldData()
//{
//    GameWorldData gameDataRecv;
// //   sf::SocketSelector selector;
// //   selector.add(tcpSocket);
//
// //   std::cout << "About to wait on socket game world data Client Side\n";
//
//	//// Make the selector wait for data on any socket
// //   if (selector.wait())
// //   {
// //       if (selector.isReady(tcpSocket))
// //       {
// //           std::cout << "About to recv game world data Client Side\n";
//
// //           if (tcpSocket.receive(&gameDataRecv, sizeof(GameWorldData), received) != sf::Socket::Done)
// //           {
// //               std::cout << "Client side error receiving Game World Data using TCP!\n";
// //               return gameDataRecv;
// //           }
//
// //           std::cout << "Client side received game world data: " << received << " bytes\n";
//
// //           std::cout << "Asteroid ID: " << gameDataRecv.asteroidID << '\n'
// //               << "Msg time sent: " << gameDataRecv.timeSent << '\n'
// //               << "Asteroid X: " << gameDataRecv.x << '\n'
// //               << "Asteroid Y: " << gameDataRecv.y << '\n';
// //       }
// //   }
//
//    std::cout << "About to recv game world data Client Side\n";
//
//    tcpSocket.setBlocking(false);
//
//    if (tcpSocket.receive(&gameDataRecv, sizeof(GameWorldData), received) != sf::Socket::Done)
//    {
//        std::cout << "Client side error receiving Game World Data using TCP!\n";
//        return gameDataRecv;
//    }
//
//    std::cout << "Client side received game world data: " << received << " bytes\n";
//
//    std::cout << "Asteroid ID: " << gameDataRecv.asteroidID << '\n'
//        << "Msg time sent: " << gameDataRecv.timeSent << '\n'
//        << "Asteroid X: " << gameDataRecv.x << '\n'
//        << "Asteroid Y: " << gameDataRecv.y << '\n';
//
//    return gameDataRecv;
//}
