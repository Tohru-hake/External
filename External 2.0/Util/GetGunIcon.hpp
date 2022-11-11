#include "../Components/Entity.hpp"
#include "../Components/LocalPlayer.hpp"

const char* GetGunIcon(int pWeapon)
{
	switch (pWeapon)
	{
	case weapon::WEAPON_DEAGLE:
		return "Desert Eagle";
	case weapon::WEAPON_ELITE:
		return "Dual Berettas";
	case weapon::WEAPON_FIVESEVEN:
		return "Five-SeveN";
	case weapon::WEAPON_GLOCK:
		return "Glock-18";
	case weapon::WEAPON_HKP2000:
		return "P2000";
	case weapon::WEAPON_P250:
		return "P250";
	case weapon::WEAPON_USP_SILENCER:
		return "USP-S";
	case weapon::WEAPON_TEC9:
		return "Tec-9";
	case weapon::WEAPON_CZ75A:
		return "CZ75-Auto";
	case weapon::WEAPON_REVOLVER:
		return "R8 Revolver";
	case weapon::WEAPON_MAC10:
		return "MAC-10";
	case weapon::WEAPON_UMP45:
		return "UMP-45";
	case weapon::WEAPON_BIZON:
		return "PP-Bizon";
	case weapon::WEAPON_MP5:
		return "MP5-SD";
	case weapon::WEAPON_MP7:
		return "MP7";
	case weapon::WEAPON_MP9:
		return "MP9";
	case weapon::WEAPON_P90:
		return "P90";
	case weapon::WEAPON_GALILAR:
		return "Galil AR";
	case weapon::WEAPON_FAMAS:
		return "FAMAS";
	case weapon::WEAPON_M4A1:
		return "M4A4";
	case weapon::WEAPON_M4A1_SILENCER:
		return "M4A1-S";
	case weapon::WEAPON_AUG:
		return "AUG";
	case weapon::WEAPON_SG553:
		return "SG 553";
	case weapon::WEAPON_AK47:
		return "AK-47";
	case weapon::WEAPON_G3SG1:
		return "G3SG1";
	case weapon::WEAPON_SCAR20:
		return "SCAR-20";
	case weapon::WEAPON_AWP:
		return "AWP";
	case weapon::WEAPON_SSG08:
		return "SSG 08";
	case weapon::WEAPON_XM1014:
		return "XM1014";
	case weapon::WEAPON_SAWEDOFF:
		return "Sawed-Off";
	case weapon::WEAPON_MAG7:
		return "MAG-7";
	case weapon::WEAPON_NOVA:
		return "Nova";
	case weapon::WEAPON_NEGEV:
		return "Negev";
	case weapon::WEAPON_M249:
		return "M249";
	case weapon::WEAPON_TASER:
		return "Zeus x27";
	case weapon::WEAPON_KNIFE:
	case weapon::WEAPON_KNIFE_T:
	case weapon::WEAPON_KNIFE_BAYONET:
	case weapon::WEAPON_KNIFE_FLIP:
	case weapon::WEAPON_KNIFE_GUT:
	case weapon::WEAPON_KNIFE_KARAMBIT:
	case weapon::WEAPON_KNIFE_M9_BAYONET:
	case weapon::WEAPON_KNIFE_TACTICAL:
	case weapon::WEAPON_KNIFE_FALCHION:
	case weapon::WEAPON_KNIFE_SURVIVAL_BOWIE:
	case weapon::WEAPON_KNIFE_BUTTERFLY:
	case weapon::WEAPON_KNIFE_PUSH:
		return "Knife";
	case weapon::WEAPON_FLASHBANG:
		return "Flashbang";
	case weapon::WEAPON_HEGRENADE:
		return "HE Grenade";
	case weapon::WEAPON_SMOKEGRENADE:
		return "Smoke Grenade";
	case weapon::WEAPON_MOLOTOV:
	case weapon::WEAPON_INCGRENADE:
		return "Molotov";
	case weapon::WEAPON_DECOY:
		return "Decoy Grenade";
	case weapon::WEAPON_C4:
		return "Bomb";
	}
};