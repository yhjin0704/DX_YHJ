#include "PreCompile.h"
#include "Spider.h"
#include "Monster.h"

ASpider::ASpider()
{
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale({ 107.0f * ContentsValue::MultipleSize, 107.f * ContentsValue::MultipleSize });
	Collision->SetCollisionGroup(ECollisionOrder::Weapon);
	Collision->SetCollisionType(ECollisionType::CirCle);
}

ASpider::~ASpider()
{
}

void ASpider::BeginPlay()
{
	Super::BeginPlay();

	Name = "Spider";

	Renderer->SetSprite("Spider.png");
	Renderer->SetupAttachment(Root);
	Renderer->SetAutoSize(1.0f * ContentsValue::MultipleSize, true);
	Renderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	Renderer->SetOrder(ERenderOrder::DownWeapon);
	IsUseAniMelee = false;

	Collision->SetActive(true);
}

void ASpider::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetActorLocation(APlayer::PlayerPos);

	CheckHit(_DeltaTime);
}

void ASpider::CheckHit(float _DeltaTime)
{

	Collision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			HitMonster = dynamic_cast<AMonster*>(_Collison->GetActor());
			IsMonsterHit = true;
		}
	);
	Collision->CollisionStay(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			if (0.0f >= HitDelay)
			{
				HitMonster = dynamic_cast<AMonster*>(_Collison->GetActor());
				IsMonsterHit = true;
				HitDelay = 1.0f;
			}
		}
	);

	HitDelay -= _DeltaTime;

	if (true == IsMonsterHit)
	{
		float Hp = HitMonster->GetHp();
		Hp -= Atk / 3.0f;
		HitMonster->SetHp(Hp);
		IsMonsterHit = false;
	}
}