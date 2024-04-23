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
}

void AKiaraWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == Renderer->IsActive())
	{
		if (true == Renderer->IsCurAnimationEnd())
		{
		}
		else
		{
		}
	}
	else
	{
		if (0 < Delay)
		{
			Dir = float4::DegToDir(Angle);
			Dir.X = 0.0f;
			SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y });
			AddActorLocation(Dir * 200.0f);
		}
		else
		{
		}
	}

}

void AKiaraWeapon::MoveAimDir()
{
	AMelee::MoveAimDir();
}

void AKiaraWeapon::MouseAimDir()
{
	AMelee::MouseAimDir();
}