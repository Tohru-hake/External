#pragma once
#include <Windows.h>
#include "../Components/LocalPlayer.hpp"
#include "../Components/Entity.hpp"
#include "../Includes.hpp"
#include <thread> 
#include <chrono>

namespace bhop
{
	extern bool bBhopEnabled;
	extern int iMinDelay;
	extern int iMaxDelay;
	void init();
}