#include "Bhop.hpp"
bool bhop::bBhopEnabled = false;
int bhop::iMinDelay = 1;
int bhop::iMaxDelay = 50;

void bhop::init()
{
	while (true)
	{
		if (bhop::iMinDelay > bhop::iMaxDelay)
		{
			bhop::iMaxDelay = iMinDelay;
		}

		if (!bBhopEnabled)
			continue;

		//If we're holding space and we're on the ground
		if (!GetAsyncKeyState(VK_SPACE))
			continue;

		if (LocalPlayer::getLocalFlags() != FL_ON_GROUND)
			continue;

		// because of multi-threading we can freely sleep things :)
		int randNum = rand() % (bhop::iMaxDelay - bhop::iMinDelay + 1) + bhop::iMinDelay;
		std::this_thread::sleep_for(std::chrono::milliseconds(randNum));

		LocalPlayer::forceJump();		
	}	
}