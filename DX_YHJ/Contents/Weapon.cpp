#include "PreCompile.h"
#include "Weapon.h"

AWeapon::AWeapon()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::MAX);

	SetRoot(Root);
}

AWeapon::~AWeapon()
{
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(ERenderOrder::Weapon);
	
}

void AWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == Renderer->IsActive())
	{
		if (true == Renderer->IsCurAnimationEnd())
		{
			Renderer->SetActive(false);
		}
		else
		{
			int a = 0;
		}
	}
	else
	{
		Angle = PlayerAngle;
		if (0 < Delay)
		{
			Renderer->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			Delay -= _DeltaTime;
		}
		else
		{
			Delay = AtkTime;
			Renderer->SetActive(true);
		}
	}
}

void AWeapon::SetPlayerStat(EPlayerDir _PlayerDir, float _Angle, float _Atk, float _CriRate, float _AtkTime)
{
	PlayerDir = _PlayerDir;
	PlayerAngle = _Angle;
	Atk = _Atk;
	CriRate = _CriRate;
	AtkTime = _AtkTime;
}

void AWeapon::MoveAimDir()
{
	switch (PlayerDir)
	{
	case EPlayerDir::N:
		break;
	case EPlayerDir::NE:
		break;
	case EPlayerDir::E:
		break;
	case EPlayerDir::SE:
		break;
	case EPlayerDir::S:
		break;
	case EPlayerDir::SW:
		break;
	case EPlayerDir::W:
		break;
	case EPlayerDir::NW:
		break;
	default:
		break;
	}
}

void AWeapon::MouseAimDir()
{

}