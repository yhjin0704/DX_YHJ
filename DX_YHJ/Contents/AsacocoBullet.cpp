#include "PreCompile.h"
#include "AsacocoBullet.h"
#include "Monster.h"
#include "NomalMonster.h"

AAsacocoBullet::AAsacocoBullet()
{
	Renderer->SetSprite("Asacoco.png");
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);

	Collision->SetScale({ 15.0f * ContentsValue::MultipleSize, 15.0f * ContentsValue::MultipleSize });

	Angle = APlayGameMode::MainPlayer->GetAngle();
}

AAsacocoBullet::~AAsacocoBullet()
{
}

void AAsacocoBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AAsacocoBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	BulletSpeed = 500.0f;

	CheckHit();
}

void AAsacocoBullet::CheckHit()
{
	Collision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			AMonster* Monster = dynamic_cast<AMonster*>(_Collison->GetActor());

			float Hp = Monster->GetHp();
			Hp -= Atk;
			Monster->SetHp(Hp);
		}
	);

	Collision->CollisionStay(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			if (0.0f >= HitDelay)
			{
				AMonster* Monster = dynamic_cast<AMonster*>(_Collison->GetActor());

				float Hp = Monster->GetHp();
				Hp -= Atk;
				Monster->SetHp(Hp);

				HitDelay = 0.5f;
			}
		}
	);
}