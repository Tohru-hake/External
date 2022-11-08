#include "LocalPlayer.hpp"
#include "../Memory/Memory.hpp"
#include "../Offsets/csgo.hpp"

DWORD LocalPlayer::LocalBaseaddress = 0;

DWORD LocalPlayer::getLocalPlayer()
{
	return LocalPlayer::LocalBaseaddress;
}

void LocalPlayer::setLocalPlayer()
{
	LocalPlayer::LocalBaseaddress = rpm<DWORD>(baseAddress + hazedumper::signatures::dwLocalPlayer);
}

int LocalPlayer::getLocalFlags()
{
	return rpm<int>(LocalPlayer::getLocalPlayer() + hazedumper::netvars::m_fFlags);
}

int LocalPlayer::getLocalHealth()
{
	return rpm<int>(LocalPlayer::getLocalPlayer() + hazedumper::netvars::m_iHealth);
}

int LocalPlayer::getLocalTeam()
{
	return rpm<int>(LocalPlayer::getLocalPlayer() + hazedumper::netvars::m_iTeamNum);
}

void LocalPlayer::forceJump(int waitTime)
{
	wpm<int>(1, baseAddress + hazedumper::signatures::dwForceJump);
	Sleep(waitTime);
	wpm<int>(0, baseAddress + hazedumper::signatures::dwForceJump);
}

int LocalPlayer::getLocalCrossID()
{
	return rpm<std::uint32_t>(LocalPlayer::getLocalPlayer() + hazedumper::netvars::m_iCrosshairId);
}

Vector3 LocalPlayer::getLocalPos()
{
	return rpm<Vector3>(LocalPlayer::getLocalPlayer() + hazedumper::netvars::m_vecOrigin);
}

ViewMatrix	LocalPlayer::getLocalViewMatrix()
{
	return rpm<ViewMatrix>(baseAddress + hazedumper::signatures::dwViewMatrix);
}

Vector3 LocalPlayer::getLocalViewOffset()
{
	return rpm<Vector3>(LocalPlayer::getLocalPlayer() + hazedumper::netvars::m_vecViewOffset);
}

Vector3 LocalPlayer::getLocalEyePos()
{
	return getLocalPos() + getLocalViewOffset();
}

Vector3 LocalPlayer::getLocalViewAngles()
{
	return rpm<Vector3>(clientState + hazedumper::signatures::dwClientState_ViewAngles);
}

void LocalPlayer::setLocalViewAngles(Vector3 angles)
{
	wpm<Vector3>(angles, clientState + hazedumper::signatures::dwClientState_ViewAngles);
}

Vector3 LocalPlayer::getLocalPunchAngles()
{
	return rpm<Vector3>(LocalPlayer::getLocalPlayer() + hazedumper::netvars::m_aimPunchAngle);
}

std::int32_t LocalPlayer::getLocalPlayerId()
{
	return rpm<std::int32_t>(clientState + hazedumper::signatures::dwClientState_GetLocalPlayer);
}