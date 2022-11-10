#pragma once

#include <windows.h>
#include "../Math/Math.hpp"
#include "../Util/WorldToScreen.hpp"

namespace LocalPlayer
{
	//Localplayer return functions
	extern DWORD			getLocalPlayer();												//Get the local player base address
	extern int				getLocalFlags();												//Get the local player flags
	extern int				getLocalHealth();												//Get the local player health
	extern int				getLocalCrossID();												//Get the local player crosshair ID
	extern int				getLocalTeam();													//Get the local player team ID
	extern Vector3		    getLocalPos();													//Get the local player pos
	extern ViewMatrix		getLocalViewMatrix();											//Get the view matrix
	extern Vector3			getLocalViewOffset();											//Get the view offset
	extern Vector3			getLocalEyePos();												//Get the origin of the eyes
	extern Vector3			getLocalViewAngles();											//Get the local player view angles
	extern Vector3		    getLocalPunchAngles();											//Get the local player punch angles (recoil)
	extern std::int32_t		getLocalPlayerId();												//Get the local player id
	extern int				getLocalWeapon();												//Get the local weapon id
	extern float			getAccuracyPenalty();											//Get the local weapon spread
	extern std::int32_t		getShotsFired();												//Get when the client shoots
	//Void functions 
	extern void				forceJump(int waitTime = 35);									//Force the local player to jump
	extern void				forceAttack(int waitTime = 5);									//Force the local player to attack
	extern void				setLocalPlayer();												//Set the local player base address
	extern void				setLocalViewAngles(Vector3 angles);								//Set the local player view angles
	

	extern DWORD			LocalBaseaddress;												//Localplayer base address
}