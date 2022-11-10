#include "Includes.hpp"
#include <thread>
// application entry point

void close()
{
	while (true)
	{
		LocalPlayer::setLocalPlayer();
		//this ^ is done to update local player 24/7 instead of just on init
		//this allows us to always have an accurate localplayer if we switch maps/teams/server ect.


		if (GetAsyncKeyState(VK_F10))
		{
			//Close handle to csgo.exe to prevent memory leaks :)
			CloseHandle(hProc);
			exit(45);
		}
	}
}



INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show)
{
	// allocate this program a console
	if (!AllocConsole()) {
		return FALSE;
	}

	// redirect stream IO
	FILE* file{ nullptr };
	freopen_s(&file, "CONIN$", "r", stdin);
	freopen_s(&file, "CONOUT$", "w", stdout);
	freopen_s(&file, "CONOUT$", "w", stderr);

	std::thread InitialThread(init);
	//wait for the intital thread to finish before continuing
	InitialThread.join();
	
	std::thread SetLocalThread(LocalPlayer::setLocalPlayer);
	//wait
	SetLocalThread.join();

	std::thread BhopThread(bhop::init);
	std::thread TriggerThread(triggerbot::init);
	std::thread AimbotThread(Aimbot::init);
	std::thread RecoilCrosshairThread(RecoilCrosshair::init);
	std::thread OverlayThread(Overlay::init, instance, cmd_show);
	std::thread AutoPistolThread(autopistol::init);
	std::thread Knifebot(Knifebot::init);

	std::thread closeThread(close);
	// wait for the closeThread. This will ensure main never aborts.
	closeThread.join(); 
}