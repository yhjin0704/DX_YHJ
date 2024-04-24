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

void AMelee::SetKnifeTypeMeleeLocation(float _DistanceFromPlayer)
{
	Dir = float4::DegToDir(Angle);
	Dir.Z = 0.0f;

	SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y + (20.0f * ContentsValue::MultipleSize) });
	AddActorLocation(Dir * _DistanceFromPlayer * ContentsValue::MultipleSize);
}