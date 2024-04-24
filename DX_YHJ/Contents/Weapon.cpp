#include "PreCompile.h"
#include "Weapon.h"

AWeapon::AWeapon()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
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
}

void AWeapon::SetPlayerStat(EPlayerDir _PlayerDir, float _Angle, float _Atk, float _CriRate, float _AtkTime)
{
	PlayerDir = _PlayerDir;
	PlayerAngle = _Angle;
	Atk = _Atk;
	CriRate = _CriRate;
	AtkTime = _AtkTime;
}