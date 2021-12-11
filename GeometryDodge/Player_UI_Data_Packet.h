#pragma once
#include "UIDataMsg.h"
#include "PlayerDataMsg.h"
#include "AsteroidDataMsg.h"

struct Player_UI_Data_Packet
{
	// UI DATA
	UIDataMsg uiData;

	// PLAYER DATA
	PlayerDataMsg playerData;
};