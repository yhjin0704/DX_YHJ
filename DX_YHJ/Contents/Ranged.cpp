#include "PreCompile.h"
#include "Ranged.h"
#include "Bullet.h"

ARanged::ARanged()
{
}

ARanged::~ARanged()
{
}

void ARanged::BeginPlay()
{
	Super::BeginPlay();
}

void ARanged::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Delay -= _DeltaTime;
}

void ARanged::CreateBullet()
{
}