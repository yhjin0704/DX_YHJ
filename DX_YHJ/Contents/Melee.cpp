#include "PreCompile.h"
#include "Melee.h"

AMelee::AMelee()
{
}

AMelee::~AMelee()
{
}

void AMelee::BeginPlay()
{
	Super::BeginPlay();
}

void AMelee::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMelee::MoveAimDir()
{
	AWeapon::MoveAimDir();
}

void AMelee::MouseAimDir()
{
	AWeapon::MouseAimDir();
}