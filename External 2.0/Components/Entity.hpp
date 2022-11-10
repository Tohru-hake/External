#pragma once
#include <windows.h>
#include "../Math/Math.hpp"

//SHIT
typedef struct {
	float Matrix[3][4];
} Matrix3x4_t;
#pragma once

namespace weapon
{
    enum ItemDefinitionIndex
    {
        ITEM_NONE = 0,
        WEAPON_DEAGLE = 1,
        WEAPON_ELITE = 2,
        WEAPON_FIVESEVEN = 3,
        WEAPON_GLOCK = 4,
        WEAPON_AK47 = 7,
        WEAPON_AUG = 8,
        WEAPON_AWP = 9,
        WEAPON_FAMAS = 10,
        WEAPON_G3SG1 = 11,
        WEAPON_GALILAR = 13,
        WEAPON_M249 = 14,
        WEAPON_M4A1 = 16,
        WEAPON_MAC10 = 17,
        WEAPON_P90 = 19,
        WEAPON_UMP45 = 24,
        WEAPON_XM1014 = 25,
        WEAPON_BIZON = 26,
        WEAPON_MAG7 = 27,
        WEAPON_NEGEV = 28,
        WEAPON_SAWEDOFF = 29,
        WEAPON_TEC9 = 30,
        WEAPON_TASER = 31,
        WEAPON_HKP2000 = 32,
        WEAPON_MP7 = 33,
        WEAPON_MP9 = 34,
        WEAPON_NOVA = 35,
        WEAPON_P250 = 36,
        WEAPON_SCAR20 = 38,
        WEAPON_SG553 = 39,
        WEAPON_SSG08 = 40,
        WEAPON_KNIFE = 42,
        WEAPON_FLASHBANG = 43,
        WEAPON_HEGRENADE = 44,
        WEAPON_SMOKEGRENADE = 45,
        WEAPON_MOLOTOV = 46,
        WEAPON_DECOY = 47,
        WEAPON_INCGRENADE = 48,
        WEAPON_C4 = 49,
        WEAPON_KNIFE_T = 59,
        WEAPON_M4A1_SILENCER = 60,
        WEAPON_USP_SILENCER = 61,
        WEAPON_CZ75A = 63,
        WEAPON_REVOLVER = 64,
        WEAPON_KNIFE_BAYONET = 500,
        WEAPON_KNIFE_FLIP = 505,
        WEAPON_KNIFE_GUT = 506,
        WEAPON_KNIFE_KARAMBIT = 507,
        WEAPON_KNIFE_M9_BAYONET = 508,
        WEAPON_KNIFE_TACTICAL = 509,
        WEAPON_KNIFE_FALCHION = 512,
        WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
        WEAPON_KNIFE_BUTTERFLY = 515,
        WEAPON_KNIFE_PUSH = 516,
        GLOVE_T_SIDE = 5028,
        GLOVE_CT_SIDE = 5029,
        GLOVE_SPORTY = 5030,
        GLOVE_SLICK = 5031,
        GLOVE_LEATHER_WRAP = 5032,
        GLOVE_MOTORCYCLE = 5033,
        GLOVE_SPECIALIST = 5034,
        MAX_ITEMDEFINITIONINDEX
    };
}


//Flags
#define FL_ON_GROUND                     257
#define FL_ON_GROUND_CROUCHED             263
#define FL_IN_AIR_STAND                    256
#define FL_IN_AIR_MOVING_TO_STAND         258
#define FL_ON_GROUND_MOVING_TO_STAND     259
#define FL_IN_AIR_MOVING_TO_CROUCH         260
#define FL_ON_GROUND_MOVING_TO_CROUCH     261
#define FL_IN_AIR_CROUCHED                 262
#define FL_IN_WATER                     1280
#define FL_IN_PUDDLE                     1281
#define FL_IN_WATER_CROUCHED             1286
#define FL_IN_PUDDLE_CROUCHED             1287
#define FL_PARTIALGROUND (1 << 18)

//Team IDs
#define TEAM_ID_GOTV 1
#define TEAM_ID_T 2
#define TEAM_ID_CT 3

//Actual shit
namespace Entity
{

	//Entity return functions
	extern DWORD			getEntBase(int index);											//Get the base address of the entity at provided index
	extern bool				isAlive(DWORD playerBase);										//Check if entity is alive 
	extern bool				isValid(DWORD playerBase);										//Checks if entity is a player
	extern bool				isDormant(DWORD playerBase);									//Checks if entity is dormant
	extern bool				getSpotted(DWORD playerBase);									//Get the spotted bool (Red dot on radar, its a bool so 1 = Spotted and 0 = Not spotted)
	extern bool				getSpottedByMask(DWORD playerBase);								//Get the spotted bool (Red dot on radar, its a bool so 1 = Spotted and 0 = Not spotted)
	extern int				getEntHp(DWORD playerBase);										//Return the health of the entity
	extern int				getEntTeam(DWORD playerBase);									//Get the team ID of the entity
	extern Vector3			getEntPos(DWORD playerBase);									//Get the entity pos
	extern char*			getEntName(DWORD playerBase);									//Get the entity name
	extern Vector3			getEntEyePos(DWORD playerBase);									//Get the entity bone pos
    extern Vector3			getEntEyeAngle(DWORD playerBase);									//Get the entity eye angle
	extern DWORD		    getEntBoneMatrix(DWORD playerBase);								//Get the entity bone matrix
	extern bool				getEntScoped(DWORD playerBase);									//Get the entity scope state - true if they are scoped
	extern bool				getEntDefusing(DWORD playerBase);								//Get the entity defusing state - true if they are defusing
	extern bool				getEntReloading(DWORD playerBase);								//Get the entity reloading state - true if they are reloading
	extern bool				getEntHelmet(DWORD playerBase);									//Get the entity helmet state - true if they have one
	extern bool				getEntDefuser(DWORD playerBase);								//Get the entity defuser state - true if they have one
	extern bool				getEntImmunity(DWORD playerBase);								//Get the entity immunity state - true if they are in gun game immunity
	extern DWORD			getActiveWeapon(DWORD playerBase);								//Get the base address of their active weapon entity
	//extern bool				isWeaponPistol(int classID);								//Get the weapon id and see if it is a pistol
	//extern bool				isWeaponSniper(int iWeaponID);								//Get the weapon id and see if it is a sniper
	extern bool				isWeaponNonAim(int iWeaponID);									//Get the weapon id and see if it is aimbot worthy
    extern bool             isWeaponKnife(int iWeaponID);

	extern int				getEntClassID(DWORD entity);									//Get the entity class id
	extern Vector3			getEntBonePos(DWORD playerBase, int boneID);					//Get the position of the desired bone of the entity
	extern int				getEntAmmo(DWORD playerBase);
}