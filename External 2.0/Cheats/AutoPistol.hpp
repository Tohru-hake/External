#pragma once
#include "../Components/LocalPlayer.hpp"
#include "../Components/Entity.hpp"
#include "../Memory/Memory.hpp"
#include <thread> 
#include <chrono>
#include "TriggerBot.hpp"

namespace autopistol
{
	extern bool bAutopistol;
	void init();
}