#include <windows.h>
#include "../Memory/Memory.hpp"
#include "Entity.hpp"
#include "../Offsets/csgo.hpp"

DWORD Entity::getEntBase(int index)
{
	return rpm<DWORD>(baseAddress + hazedumper::signatures::dwEntityList + (index * 0x10));
}

int	Entity::getEntHp(DWORD playerBase)
{
	return rpm<int>(playerBase + hazedumper::netvars::m_iHealth);
}

bool Entity::isAlive(DWORD playerBase)
{
	if (getEntHp(playerBase) > 0 && getEntHp(playerBase) <= 100)
		return true;
	return false;
}

int	Entity::getEntTeam(DWORD playerBase)
{
	return rpm<int>(playerBase + hazedumper::netvars::m_iTeamNum);
}

bool Entity::isValid(DWORD playerBase)
{
	auto dormant = rpm<bool>(playerBase + hazedumper::signatures::m_bDormant);
	if ((Entity::isAlive(playerBase) && Entity::getEntTeam(playerBase) != 0) && !dormant)
		return true;
	return false;
}

bool Entity::isDormant(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::signatures::m_bDormant);
}


bool Entity::getSpotted(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::netvars::m_bSpotted);
}

bool Entity::getSpottedByMask(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::netvars::m_bSpottedByMask);
}

Vector3	Entity::getEntPos(DWORD playerBase)
{
	return rpm<Vector3>(playerBase + hazedumper::netvars::m_vecOrigin);
}

char* Entity::getEntName(DWORD playerBase)
{
	return rpm<char*>(playerBase + hazedumper::netvars::m_szCustomName);
}

DWORD Entity::getEntBoneMatrix(DWORD playerBase)
{
	return rpm<DWORD>(playerBase + hazedumper::netvars::m_dwBoneMatrix);
}

Vector3 Entity::getEntEyePos(DWORD playerBase)
{
	return ((Entity::getEntPos(playerBase)) + (rpm<Vector3>(playerBase + hazedumper::netvars::m_vecViewOffset)));
}

bool Entity::getEntScoped(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::netvars::m_bIsScoped);
}

bool Entity::getEntDefusing(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::netvars::m_bIsDefusing);
}

bool Entity::getEntReloading(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::netvars::m_bInReload);
}

bool Entity::getEntHelmet(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::netvars::m_bHasHelmet);
}

bool Entity::getEntDefuser(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::netvars::m_bHasDefuser);
}

bool Entity::getEntImmunity(DWORD playerBase)
{
	return rpm<bool>(playerBase + hazedumper::netvars::m_bGunGameImmunity);
}

DWORD Entity::getActiveWeapon(DWORD playerBase)
{
	DWORD WeaponIndex = rpm<DWORD>(playerBase + hazedumper::netvars::m_hActiveWeapon) & 0xFFF;
	return rpm<DWORD>((baseAddress + hazedumper::signatures::dwEntityList + WeaponIndex * 0x10) - 0x10);
}

////Uses ClassID
//bool Entity::isWeaponNonAim(int classID)
//{
//	if (classID == CKnife || classID == CKnifeGG || classID == CFlashbang || classID == CHEGrenade || classID == CSmokeGrenade
//		|| classID == CMolotovGrenade || classID == CDecoyGrenade || classID == CIncendiaryGrenade || classID == CC4)
//		return true;
//	return false;
//}

//Uses iItemDefinitionIndex
bool Entity::isWeaponNonAim(int iWeaponID)
{
	if (   iWeaponID == weapon::WEAPON_KNIFE	
		|| iWeaponID == weapon::WEAPON_KNIFE_BAYONET
		|| iWeaponID == weapon::WEAPON_KNIFE_BUTTERFLY
		|| iWeaponID == weapon::WEAPON_KNIFE_FALCHION
		|| iWeaponID == weapon::WEAPON_KNIFE_FLIP
		|| iWeaponID == weapon::WEAPON_KNIFE_GUT
		|| iWeaponID == weapon::WEAPON_KNIFE_KARAMBIT
		|| iWeaponID == weapon::WEAPON_KNIFE_M9_BAYONET
		|| iWeaponID == weapon::WEAPON_KNIFE_PUSH
		|| iWeaponID == weapon::WEAPON_KNIFE_T
		|| iWeaponID == weapon::WEAPON_KNIFE_SURVIVAL_BOWIE
		|| iWeaponID == weapon::WEAPON_KNIFE_TACTICAL
		|| iWeaponID == weapon::WEAPON_FLASHBANG
		|| iWeaponID == weapon::WEAPON_HEGRENADE
		|| iWeaponID == weapon::WEAPON_SMOKEGRENADE
		|| iWeaponID == weapon::WEAPON_MOLOTOV
		|| iWeaponID == weapon::WEAPON_DECOY
		|| iWeaponID == weapon::WEAPON_C4
		|| iWeaponID == weapon::WEAPON_INCGRENADE)
	{
		std::cout << "knife";
		return true;
	}

	return false;
}

////Uses ClassID
//bool Entity::isWeaponPistol(int classID)
//{
//	if (classID == CDEagle || classID == CWeaponElite || classID == CWeaponFiveSeven || classID == CWeaponGlock
//		|| classID == CWeaponP228 || classID == CWeaponUSP || classID == CWeaponTec9 || classID == CWeaponTaser || classID == CWeaponHKP2000 || classID == CWeaponP250)
//		return true;
//
//	return false;
//}

////Uses ClassID
//bool Entity::isWeaponSniper(int classID)
//{
//	if (classID == CWeaponAWP || classID == CWeaponSSG08 || classID == CWeaponG3SG1 || classID == CWeaponSCAR20)
//		return true;
//
//	return false;
//}

int	Entity::getEntClassID(DWORD entity)
{
	int one = rpm<int>(entity + 0x8);
	int two = rpm<int>(one + 2 * 0x4);
	int three = rpm<int>(two + 0x1);
	return rpm<int>(three + 0x14);
}

Vector3	Entity::getEntBonePos(DWORD playerBase, int boneID)
{
	Matrix3x4_t boneMatrix = rpm<Matrix3x4_t>(Entity::getEntBoneMatrix(playerBase) + boneID * 0x30);

	return{
		boneMatrix.Matrix[0][3],
		boneMatrix.Matrix[1][3],
		boneMatrix.Matrix[2][3]
	};
}

int Entity::getEntAmmo(DWORD playerBase)
{
	auto weapon = Entity::getActiveWeapon(playerBase);
	return rpm<int>(weapon + hazedumper::netvars::m_iClip1);
}