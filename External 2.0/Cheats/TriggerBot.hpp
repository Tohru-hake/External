#pragma once
#include "../Components/LocalPlayer.hpp"
#include "../Components/Entity.hpp"
#include "../Memory/Memory.hpp"
#include <thread> 
#include <chrono>
#include "Aimbot.hpp"

namespace triggerbot
{
	extern bool bTriggerEnabled;
	extern int TriggerKey;
	extern int iMinDelay;
	extern int iMaxDelay;

	bool ShouldTriggerbot(const int crosshairId);

	void init();
}