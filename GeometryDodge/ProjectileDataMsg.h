#pragma once

struct ProjectileDataMsg
{
	// An ID number associated with the corrosponding projectile
	int projectileID;

	// The positional data of this projectile
	float x;
	float y;

	// The time this msg was sent
	float timeSent;
};