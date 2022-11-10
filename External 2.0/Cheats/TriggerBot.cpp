#include "TriggerBot.hpp"
#include "Overlay.hpp"
#include "../Util/KeyArray.hpp"
bool triggerbot::bTriggerEnabled = false;
int triggerbot::TriggerKey = 0;
int triggerbot::iMinDelay = 1;
int triggerbot::iMaxDelay = 50;

bool triggerbot::ShouldTriggerbot(const int crosshairId)
{

	if (triggerbot::iMinDelay > triggerbot::iMaxDelay)
	{
		triggerbot::iMaxDelay = triggerbot::iMinDelay;
	}

	if (Overlay::bMenuVisible)
		return false;

	if (!triggerbot::bTriggerEnabled)
		return false;

	if (!GetAsyncKeyState(KeyCodes[triggerbot::TriggerKey]))
		return false;

	const uintptr_t player = rpm<std::uintptr_t>(baseAddress + hazedumper::signatures::dwEntityList + (crosshairId - 1) * 0x10);

	if (Entity::getEntTeam(player) == LocalPlayer::getLocalTeam())
		return false;

	if (!Entity::isAlive(player))
		return false;

	if (!crosshairId || crosshairId > 64)
		return false;


	//TODO: WEAPONS.
	return true;
}

void triggerbot::init()
{
	while (true) // Run forever.
	{
		if (!ShouldTriggerbot(LocalPlayer::getLocalCrossID()))
			continue;

		// because of multi-threading we can freely sleep things :)
		int randNum = rand() % (triggerbot::iMaxDelay - triggerbot::iMinDelay + 1) + triggerbot::iMinDelay;
		std::this_thread::sleep_for(std::chrono::milliseconds(randNum));

		INPUT iNPUT = { 0 };
		iNPUT.type = INPUT_MOUSE;
		iNPUT.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &iNPUT, sizeof(iNPUT));
		ZeroMemory(&iNPUT, sizeof(iNPUT));

		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		iNPUT.type = INPUT_MOUSE;
		iNPUT.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &iNPUT, sizeof(iNPUT));
	}
}