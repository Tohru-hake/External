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


int hexadecimalToDecimal(std::string hexVal)
{
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--) {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;
}

#include <sstream>
int LocalPlayer::getLocalWeapon()
{
	std::uintptr_t iCurWeaponAdr = rpm<std::uintptr_t>(LocalPlayer::getLocalPlayer() + hazedumper::netvars::m_hActiveWeapon) & 0xFFF;
	std::uintptr_t iBase = rpm<std::uintptr_t>(baseAddress + hazedumper::signatures::dwEntityList + (iCurWeaponAdr - 1) * 0x10);
	int id = rpm <int>(iBase + hazedumper::netvars::m_iItemDefinitionIndex);

    std::stringstream ss;
    ss << id;
    std::string str = ss.str();

    return id;
	//return  hexadecimalToDecimal(str);
}