#include "PreCompile.h"
#include "KiaraWeapon.h"

AKiaraWeapon::AKiaraWeapon()
{
	CollisionR0 = CreateDefaultSubObject<UCollision>("Collision");
	//CollisionR0->SetupAttachment(Root);
	CollisionR0->SetScale({ 50.0f * ContentsValue::MultipleSize, 50.f * ContentsValue::MultipleSize });

	CollisionR0->SetCollisionGroup(ECollisionOrder::Weapon);
	CollisionR0->SetCollisionType(ECollisionType::Rect);
}

AKiaraWeapon::~AKiaraWeapon()
{
}

void AKiaraWeapon::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("KiaraAttack", "KiaraAttack", 0.05f);
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->ChangeAnimation("KiaraAttack");

	SetKnifeTypeMeleeLocation(35.0f);
	CollisionR0->SetActive(false);
}

void AKiaraWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetKnifeTypeMeleeLocation(35.0f);

	if (true == Renderer->IsActive())
	{
		CollisionR0->SetActive(true);
		CollisionR0->SetPosition(Root->GetLocalPosition());
		CollisionR0->AddPosition(Dir * 50.0f * ContentsValue::MultipleSize);
	}
	else
	{
		CollisionR0->SetActive(false);
	}
}
