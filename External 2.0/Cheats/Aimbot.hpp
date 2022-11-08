#pragma once
#include "../Math/Math.hpp"
#include "../Components/LocalPlayer.hpp"
#include "../Components/Entity.hpp"
#include <iostream>



namespace Aimbot
{
	extern Vector3 AimPosition;
	extern bool bEnabled;
	extern int AimKey;
	extern float fFov;
	extern float fSmoothing;
	extern const char* hitboxes[2];
	extern const char* current_hitbox;

	extern Vector3 angle;

	extern bool bRecoil;
	extern float fRecoilX;
	extern float fRecoilY;



	void Aimbot();
	void init();
}