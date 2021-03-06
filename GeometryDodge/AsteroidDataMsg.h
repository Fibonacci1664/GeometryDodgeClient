/*
 * This is the AsteroidDataMsg struct and handles
 *		- Storing a single asteroids data
 *
 * Original @author D. Green.
 *
 * ? D. Green. 2021.
 */

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

struct AsteroidDataMsg
{
	// An ID number associated with the corrosponding asteroid
	int asteroidID;

	// The positional data of this asteroid
	float x;
	float y;

	// The time this msg was sent
	float timeSent;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////