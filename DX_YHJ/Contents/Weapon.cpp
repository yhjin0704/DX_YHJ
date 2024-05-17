#include "PreCompile.h"
#include "Weapon.h"
#include "PlayGameMode.h"

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

	Atk = APlayGameMode::MainPlayer->GetAtk();
}