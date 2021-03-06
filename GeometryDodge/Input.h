/*
 * This class controls all aspects of Input including:
 *		- Keyboard, which keys pressed/released.
 *		- Mouse, buttons pressed & position.
 *
 * Original @author D. Green.
 *
 * ? D. Green. 2021.
 */

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // INCLUDES
#pragma once
#include<iostream>
#include <SFML/System/Vector2.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Input
{
private:
	// Mouse structure, store mouse relevant information.
	struct Mouse
	{
		int x, y;
		bool left, right;
	};

public:
	Input();
	~Input();

	// Function for setting controller button as pressed, released and checking current state.
	void setButtonState(int buttonIndex, bool state);
	bool isButtonDown(int button);

	// Functions for setting joystick positions
	void setLeftStick(float xAxis, float yAxis);
	sf::Vector2f getLeftStick();

	// Functions for setting key as pressed, released and checking current state.
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);

	// Functions are mouse input, including getting and setting current position and mouse button presses.
	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	int getMouseX();
	int getMouseY();
	void setMouseLDown(bool down);
	bool isMouseLDown();
	void setMouseRDown(bool down);
	bool isMouseRDown();

private:
	// Array of booleans representing buttons and keys (pressed = true, released = false).
	bool buttons[32]{ false };
	bool keys[256]{ false };
	sf::Vector2f leftStickPos;

	// Mouse variable.
	Mouse mouse;
};
