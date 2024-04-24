#include "PreCompile.h"
#include "Weapon.h"

AWeapon::AWeapon()
{
}

AWeapon::~AWeapon()
{
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AWeapon::SetPlayerStat(EPlayerDir _PlayerDir, float _Angle, float _Atk, float _CriRate, float _AtkTime)
{
	PlayerDir = _PlayerDir;
	PlayerAngle = _Angle;
	Atk = _Atk;
	CriRate = _CriRate;
	AtkTime = _AtkTime;
}