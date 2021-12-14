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
#include "NetworkManager.h"

// CONSTRUCTOR / DESTRUCTOR
NetworkManager::NetworkManager()
{
    /*playerDataRecv = new PlayerDataMsg;
    UIMsg = new UIDataMsg;

    playerDataRecv = nullptr;
    UIMsg = nullptr;*/
}

NetworkManager::~NetworkManager()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Player_UI_Data_Packet NetworkManager::receivePlayerUIPacket()
{
    if (selector.wait())
    {
        if (selector.isReady(tcpSocket))
        {
            if (printDataToConsole)
            {
                std::cout << "\n############### PLAYER AND UI DATA ###############\n\n";
            }

            if (tcpSocket.receive(&playerUIpckt, sizeof(Player_UI_Data_Packet), received) != sf::Socket::Done)
            {
                std::cout << "Client side error receiving ta using TCP!\n";
                return playerUIpckt;
            }

            if(printDataToConsole)
            {
                 std::cout << "Client side received: " << received << " bytes\n";

                 std::cout << "Score: " << playerUIpckt.uiData.score << "\n";
                 
                 std::cout << "Player " << playerUIpckt.playerData.playerID << "\n"
                           << "Msg time sent: " << playerUIpckt.playerData.timeSent << '\n'
                           << "Player X: " << playerUIpckt.playerData.x << '\n'
                           << "Player Y: " << playerUIpckt.playerData.y << '\n';
                 
                 std::cout << "\n############### PLAYER AND UI DATA END ###############\n";
            }
        }
    }

    return playerUIpckt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Asteroids_Data_Packet NetworkManager::recevieAsteroidPacket()
{
    if (selector.wait())
    {
        if (selector.isReady(tcpSocket))
        {
            if (printDataToConsole)
            {
                std::cout << "\n############### ASTEROID VECTOR SIZE DATA ###############\n\n";
            }

            // Carry out a recv of the asteroid data msg vector size, this is just a single int
            if (tcpSocket.receive(&asteroidsPckt.asteroidDataMsgSize, sizeof(int), received) != sf::Socket::Done)
            {
                std::cout << "Client side error receiving asteroids msgs vector size using TCP!\n";
                return asteroidsPckt;
            }

            if (printDataToConsole)
            {
                std::cout << "Asteroid data msg vector size: " << asteroidsPckt.asteroidDataMsgSize << '\n';

                std::cout << "\n############### ASTEROID VECTOR SIZE DATA END ###############\n";
            }
                
            int size = asteroidsPckt.asteroidDataMsgSize;

            if (printDataToConsole)
            {
                std::cout << "\n############### ALL ASTEROID DATA ###############\n";
            }

            if (size == 0 && printDataToConsole)
            {
               std::cout << "\n############### NO ASTEROID DATA TO RECEIVE ###############\n\n";
            }

            // Clear the old data
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

                if (printDataToConsole)
                {
                    std::cout << "\n############### ASTEROID " << asteroidsPckt.asteroidDataMsgs[i]->asteroidID << " MSG DATA ###############\n\n";

                    //Print out to make sure what has been recvd is the same data
                    std::cout << "Asteroid ID: " << asteroidsPckt.asteroidDataMsgs[i]->asteroidID << '\n'
                              << "Msg time sent: " << asteroidsPckt.asteroidDataMsgs[i]->timeSent << '\n'
                              << "Asteroid X: " << asteroidsPckt.asteroidDataMsgs[i]->x << '\n'
                              << "Asteroid Y: " << asteroidsPckt.asteroidDataMsgs[i]->y << '\n'
                              << "Bytes received: " << received << "\n";

                    std::cout << "\n############### ASTEROID " << asteroidsPckt.asteroidDataMsgs[i]->asteroidID << " MSG DATA END ###############\n";
                }
            }

            // Finally set the size in the Asteroid Data Packet to be the correct size
            asteroidsPckt.asteroidDataMsgSize = asteroidsPckt.asteroidDataMsgs.size();
        }
    }

    return asteroidsPckt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Projectiles_Data_Packet NetworkManager::recevieProjectilesPacket()
{
    if (selector.wait())
    {
        if (selector.isReady(tcpSocket))
        {
            if (printDataToConsole)
            {
                std::cout << "\n############### PROJECTILE VECTOR SIZE DATA ###############\n\n";
            }
            
            // Carry out a recv of the projectile data msg vector size, this is just a single int
            if (tcpSocket.receive(&projectilesPckt.projectileDataMsgSize, sizeof(int), received) != sf::Socket::Done)
            {
                std::cout << "Client side error receiving projectile msgs vector size using TCP!\n";
                return projectilesPckt;
            }

            if (printDataToConsole)
            {
                std::cout << "Projectile data msg vector size: " << projectilesPckt.projectileDataMsgSize << '\n';

                std::cout << "\n############### PROJECTILE VECTOR SIZE DATA END ###############\n";
            }

            int size = projectilesPckt.projectileDataMsgSize;

            if (printDataToConsole)
            {
                std::cout << "\n############### ALL PROJECTILE DATA ###############\n";
            }

            if (size == 0 && printDataToConsole)
            {
                std::cout << "\n############### NO PROJECTILE DATA TO RECEIVE ###############\n\n";
            }

            // Clear old data
            projectilesPckt.projectileDataMsgs.clear();

            // Carry out a loop to recv all projectile data from the packet
            for (int i = 0; i < size; ++i)
            {
                ProjectileDataMsg* projectileMsg = new ProjectileDataMsg;

                // Carry out a recv of the projectile data msg
                if (tcpSocket.receive(projectileMsg, sizeof(ProjectileDataMsg), received) != sf::Socket::Done)
                {
                    std::cout << "Client side error receiving projectile msgs using TCP!\n";
                    return projectilesPckt;
                }

                projectilesPckt.projectileDataMsgs.push_back(projectileMsg);

                if (printDataToConsole)
                {
                    std::cout << "\n############### PROJECTILE " << projectilesPckt.projectileDataMsgs[i]->projectileID << " MSG DATA ###############\n\n";

                    // Print out to make sure what has been recvd is the same data
                    std::cout << "Projectile ID: " << projectilesPckt.projectileDataMsgs[i]->projectileID << '\n'
                              << "Msg time sent: " << projectilesPckt.projectileDataMsgs[i]->timeSent << '\n'
                              << "Projectile X: " << projectilesPckt.projectileDataMsgs[i]->x << '\n'
                              << "Projectile Y: " << projectilesPckt.projectileDataMsgs[i]->y << '\n'
                              << "Bytes received: " << received << "\n";

                    std::cout << "\n############### PROJECTILE " << projectilesPckt.projectileDataMsgs[i]->projectileID << " MSG DATA END ###############\n";
                }
            }

            // Finally set the size in the Projectile Data Packet to be the correct size
            projectilesPckt.projectileDataMsgSize = projectilesPckt.projectileDataMsgs.size();
        }
    }

    return projectilesPckt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkManager::sendForEcho()
{
    // Send the value 1
    int value = 1;

    // Send, for the purposes of receiving an echo to gauge latency
    if (tcpSocket.send(&value, sizeof(int)) != sf::Socket::Done)
    {
        std::cout << "Error sending asteroid data msg size by TCP!\n";
        return;
    }

    std::cout << "Value " << value << " sent\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NetworkManager::receiveEcho()
{
    if (selector.wait())
    {
        if (selector.isReady(tcpSocket))
        {
            // Carry out a recv of the game state, this is just a single int
            if (tcpSocket.receive(&echo, sizeof(int), received) != sf::Socket::Done)
            {
                std::cout << "Client side error receiving echo using TCP!\n";
                return -1;
            }
        }
    }

    // This SHOULD be the value 2
    return echo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NetworkManager::receiveGameState()
{
    if (selector.wait(sf::seconds(0.001)))
    {
        if (selector.isReady(tcpSocket))
        {
            // Carry out a recv of the game state, this is just a single int
            if (tcpSocket.receive(&gameState, sizeof(int), received) != sf::Socket::Done)
            {
                std::cout << "Client side error receiving game state using TCP!\n";
                return -1;
            }
        }
    }

    return gameState;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////