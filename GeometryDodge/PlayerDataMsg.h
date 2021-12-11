#pragma once

struct PlayerDataMsg
{
	// An ID number for this msg, used for sorting
	//int msgID;

	// An ID number associated with the corrosponding player
	int playerID;

	// The positional data of this player
	float x;
	float y;

	// The time this msg was sent
	float timeSent;
};