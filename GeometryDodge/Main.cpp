// THIS IS THE NEW CLIENT

// THIS RECVS DATA FROM THE SEVER AND SIMPLY MIRRORS WHAT IS HAPPENING SERVER SIDE

// NEED TO CARRY OUT PLAYER PREDICTION ON THIS SIDE

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Application.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{
    std::srand(std::time(nullptr));

    Application app(WINDOW_WIDTH, WINDOW_HEIGHT);
    app.run();

	return 0;
}