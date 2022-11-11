#include "AutoPistol.hpp"
#include "../Util/KeyArray.hpp"
#include "Overlay.hpp"
bool autopistol::bAutopistol = false;

void autopistol::init()
{
	while (true) // Run forever.
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (!Overlay::FindTopWindow(pID))
			continue;

		if (Overlay::bMenuVisible)
			continue;

		if (!autopistol::bAutopistol)
			continue;

		if (GetAsyncKeyState(KeyCodes[triggerbot::TriggerKey]))
			continue;

		if (!GetAsyncKeyState(VK_LBUTTON))
			continue;

		// because of multi-threading we can freely sleep things :)


		LocalPlayer::forceAttack(100);
	}
}