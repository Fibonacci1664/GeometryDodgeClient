#pragma once
#include "ProjectileDataMsg.h"
#include <vector>

struct Projectiles_Data_Packet
{
	int projectileDataMsgSize = 0;
	std::vector<ProjectileDataMsg*> projectileDataMsgs;
};