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
}

void AWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AWeapon::MoveAimDir()
{
}

void AWeapon::MouseAimDir()
{
}