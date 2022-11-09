#include "Aimbot.hpp"
#include "../Util/KeyArray.hpp"
#include "Overlay.hpp"

bool Aimbot::bEnabled = false;
float Aimbot::fFov = 5.f;
float Aimbot::fSmoothing = 3.f;
int Aimbot::AimKey = 0;
const char* Aimbot::current_hitbox = NULL;
const char* Aimbot::hitboxes[2] = { "Head", "Pelvis" };
Vector3 Aimbot::AimPosition;
Vector3 Aimbot::angle;

bool Aimbot::bRecoil = true;
float Aimbot::fRecoilX = 0.5f;
float Aimbot::fRecoilY = 0.5f;


Vector3 CalcAngle(
	const Vector3& localPosition,
	const Vector3& enemyPosition,
	const Vector3& viewAngles) noexcept
{
	return ((enemyPosition - localPosition).ToAngle() - viewAngles);
}

void Aimbot::Aimbot()
{
	Vector3 bestAngle = { };

	for (int i = 1; i < 32; i++)
	{
		const DWORD Base = Entity::getEntBase(i);

		if (Overlay::bMenuVisible)
			continue;

		if (!Aimbot::bEnabled)
			continue;

		if (Entity::isWeaponNonAim(LocalPlayer::getLocalWeapon()))
			continue;

		if (!Base)
			continue;

		if (!Entity::isValid(Base))
			continue;

		if (Entity::getEntTeam(Base) == LocalPlayer::getLocalTeam())
			continue;

		if (!(Entity::getSpottedByMask(Base) & (1 << LocalPlayer::getLocalPlayerId())))
			continue;

		if (!GetAsyncKeyState(KeyCodes[Aimbot::AimKey]))
			continue;


		if (Aimbot::current_hitbox == hitboxes[0])
		{
			Aimbot::AimPosition = Entity::getEntBonePos(Base, 8);
		}

		if (Aimbot::current_hitbox == hitboxes[1])
		{
			Aimbot::AimPosition = Entity::getEntBonePos(Base, 4);
		}

		if (Aimbot::bRecoil)
		{
			float modpunchangleX = LocalPlayer::getLocalPunchAngles().x * Aimbot::fRecoilX;
			float modpunchangleY = LocalPlayer::getLocalPunchAngles().y * Aimbot::fRecoilY;
			float punchZ = LocalPlayer::getLocalPunchAngles().z;

			auto newPunch = Vector3
			{
				modpunchangleX,
				modpunchangleY,
				punchZ
			};

			Aimbot::angle = CalcAngle(
				LocalPlayer::getLocalEyePos(),
				AimPosition,
				LocalPlayer::getLocalViewAngles() + (newPunch * 2)
			);
		}
		else
		{
			Aimbot::angle = CalcAngle(
				LocalPlayer::getLocalEyePos(),
				AimPosition,
				LocalPlayer::getLocalViewAngles()
			);
		}
		

		const float fov = std::hypot(Aimbot::angle.x, Aimbot::angle.y);

		if (fov < Aimbot::fFov)
		{
			bestAngle = Aimbot::angle;
		}

		if (!bestAngle.IsZero())
		{
			LocalPlayer::setLocalViewAngles(LocalPlayer::getLocalViewAngles() + bestAngle / (Aimbot::fSmoothing * 100.f));
		}
	}
}

void Aimbot::init()
{
	while (true)
	{
		Aimbot();
		
	}
}