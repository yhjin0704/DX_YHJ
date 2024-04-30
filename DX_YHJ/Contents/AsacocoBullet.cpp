#include "PreCompile.h"
#include "AsacocoBullet.h"
#include "Monster.h"

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

			Monster->Destroy();
			//Monster->GetEnemyData().Hp -= UMagicWand::Data.Damage;
		}
	);
}