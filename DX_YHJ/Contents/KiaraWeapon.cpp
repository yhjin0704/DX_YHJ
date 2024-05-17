#include "PreCompile.h"
#include "KiaraWeapon.h"
#include "Monster.h"

AKiaraWeapon::AKiaraWeapon()
{
	CollisionR0 = CreateDefaultSubObject<UCollision>("Collision");
	//CollisionR0->SetupAttachment(Root);
	CollisionR0->SetScale({ 50.0f * ContentsValue::MultipleSize, 50.f * ContentsValue::MultipleSize });

	CollisionR0->SetCollisionGroup(ECollisionOrder::Weapon);
	CollisionR0->SetCollisionType(ECollisionType::RotRect);

	CollisionR1 = CreateDefaultSubObject<UCollision>("Collision");
	//CollisionR0->SetupAttachment(Root);
	CollisionR1->SetScale({ 50.0f * ContentsValue::MultipleSize, 50.f * ContentsValue::MultipleSize });

	CollisionR1->SetCollisionGroup(ECollisionOrder::Weapon);
	CollisionR1->SetCollisionType(ECollisionType::RotRect);
}

AKiaraWeapon::~AKiaraWeapon()
{
}

void AKiaraWeapon::BeginPlay()
{
	Super::BeginPlay();

	Name = "KiaraWeapon";

	Renderer->CreateAnimation("KiaraAttack", "KiaraAttack", 0.05f);
	Renderer->SetAutoSize(1.0f * ContentsValue::MultipleSize, true);
	Renderer->ChangeAnimation("KiaraAttack");

	SetKnifeTypeMeleeLocation(35.0f);
	CollisionR0->SetActive(false);
	CollisionR1->SetActive(false);
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

		CollisionR0->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });

		CollisionR1->SetActive(false);
		CollisionR1->SetPosition(Root->GetLocalPosition());
		CollisionR1->AddPosition(Dir * 50.0f * ContentsValue::MultipleSize);

		//CollisionR1->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });

		CheckHit();
	}
	else
	{
		CollisionR0->SetActive(false);
		CollisionR1->SetActive(false);
	}
}

void AKiaraWeapon::CheckHit()
{
	
	CollisionR0->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			HitMonster = dynamic_cast<AMonster*>(_Collison->GetActor());
			IsMonsterHit = true;
			/*float Hp = HitMonster->GetHp();
			Hp -= Atk;
			HitMonster->SetHp(Hp);*/
		}
	);
	CollisionR1->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
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