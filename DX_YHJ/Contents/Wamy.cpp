#include "PreCompile.h"
#include "Wamy.h"
#include "Monster.h"

AWamy::AWamy()
{
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetScale({ 50.0f * ContentsValue::MultipleSize, 50.f * ContentsValue::MultipleSize });
	Collision->SetCollisionGroup(ECollisionOrder::Weapon);
	Collision->SetCollisionType(ECollisionType::Rect);
}

AWamy::~AWamy()
{
}

void AWamy::BeginPlay()
{
	Super::BeginPlay();

	Name = "Wamy";

	Renderer->CreateAnimation("Wamy", "Wamy", 0.05f);
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->ChangeAnimation("Wamy");

	SetKnifeTypeMeleeLocation(30.0f);
	
	Collision->SetActive(false);

}

void AWamy::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetKnifeTypeMeleeLocation(30.0f);

	if (true == Renderer->IsActive())
	{
		Collision->SetActive(true);
		Collision->SetPosition(Root->GetLocalPosition());
		Collision->AddPosition(Dir * ContentsValue::MultipleSize);
		Collision->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });

		CheckHit();
	}
	else
	{
		Collision->SetActive(false);
	}
}

void AWamy::CheckHit()
{
	Collision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			HitMonster = dynamic_cast<AMonster*>(_Collison->GetActor());
			IsMonsterHit = true;
		}
	);
	if (true == IsMonsterHit)
	{
		float Hp = HitMonster->GetHp();
		Hp -= Atk;
		HitMonster->SetHp(Hp);
		IsMonsterHit = false;
	}
}

