#include "Knifebot.hpp"
#include <thread>
#include <chrono>
#include "../Util/WorldToScreen.hpp"


int distance(Vector3 a, Vector3 b) {
	double distance;

	distance = sqrt(((int)a.x - (int)b.x) * ((int)a.x - (int)b.x) +
		((int)a.y - (int)b.y) * ((int)a.y - (int)b.y) +
		((int)a.z - (int)b.z) * ((int)a.z - (int)b.z));

	return (int)abs(round(distance));
}

void Knifebot::init()
{
	bool back = false;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (!Entity::isWeaponKnife(LocalPlayer::getLocalWeapon()))
			continue;

		for (int i = 1; i < 64; i++)
		{
			const DWORD Base = Entity::getEntBase(i);

			const uintptr_t player = rpm<std::uintptr_t>(baseAddress + hazedumper::signatures::dwEntityList + (LocalPlayer::getLocalCrossID() - 1) * 0x10);

			const auto EnemyPos = Entity::getEntPos(Base);
			const auto EnemyHP = Entity::getEntHp(player);
			const auto EnemyEye = Entity::getEntEyeAngle(player);
			const auto localEye = LocalPlayer::getLocalViewAngles();
			if (!Entity::isValid(Base))
				continue;

			if (Entity::getEntTeam(Base) == LocalPlayer::getLocalTeam())
				continue;

			Vector3 screen;
			if (!WorldToScreen(Entity::getEntBonePos(Base, 4), screen, LocalPlayer::getLocalViewMatrix()))
				continue;

			if (EnemyEye.y > (localEye.y + 120.f))
			{
				back = false;
			}
			else
			{
				back = true;
			}

			if (distance(LocalPlayer::getLocalPos(), EnemyPos) <= 65 && (back || EnemyHP <= 55)) {

				INPUT iNPUT = { 0 };
				iNPUT.type = INPUT_MOUSE;
				iNPUT.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
				SendInput(1, &iNPUT, sizeof(iNPUT));
				ZeroMemory(&iNPUT, sizeof(iNPUT));

				std::this_thread::sleep_for(std::chrono::milliseconds(5));

				iNPUT.type = INPUT_MOUSE;
				iNPUT.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
				SendInput(1, &iNPUT, sizeof(iNPUT));
			}
			else if (distance(LocalPlayer::getLocalPos(), EnemyPos) <= 82 && EnemyHP > 55 && !back) {

				//std::cout << "Im alive!" << std::endl;

				INPUT iNPUT = { 0 };
				iNPUT.type = INPUT_MOUSE;
				iNPUT.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				SendInput(1, &iNPUT, sizeof(iNPUT));
				ZeroMemory(&iNPUT, sizeof(iNPUT));

				std::this_thread::sleep_for(std::chrono::milliseconds(5));

				iNPUT.type = INPUT_MOUSE;
				iNPUT.mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SendInput(1, &iNPUT, sizeof(iNPUT));
			}
		}
	}
}