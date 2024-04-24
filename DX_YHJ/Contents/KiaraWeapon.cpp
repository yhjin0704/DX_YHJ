#include "PreCompile.h"
#include "KiaraWeapon.h"

AKiaraWeapon::AKiaraWeapon()
{
}

AKiaraWeapon::~AKiaraWeapon()
{
}

void AKiaraWeapon::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("KiaraAttack", "KiaraAttack", 0.1f);
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->ChangeAnimation("KiaraAttack");

	Dir = float4::DegToDir(Angle);
	Dir.Z = 0.0f;
	SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y + (20.0f * ContentsValue::MultipleSize) });
	AddActorLocation(Dir * 50.0f * ContentsValue::MultipleSize);
}

void AKiaraWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Dir = float4::DegToDir(Angle);
	Dir.Z = 0.0f;
	SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y + (20.0f * ContentsValue::MultipleSize )});
	AddActorLocation(Dir * 50.0f * ContentsValue::MultipleSize);

}

void AKiaraWeapon::MoveAimDir()
{
	AMelee::MoveAimDir();
}

void AKiaraWeapon::MouseAimDir()
{
	AMelee::MouseAimDir();
}