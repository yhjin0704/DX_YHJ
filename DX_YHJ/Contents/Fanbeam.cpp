#include "PreCompile.h"
#include "Fanbeam.h"
#include "Monster.h"
#include "PlayGameMode.h"

AFanbeam::AFanbeam()
{
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::Weapon);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->SetScale({ 466.0f * ContentsValue::MultipleSize, 51.0f * ContentsValue::MultipleSize });
	Collision->SetActive(false);

}

AFanbeam::~AFanbeam()
{
}

void AFanbeam::BeginPlay()
{
	Super::BeginPlay();

	Name = "Fanbeam";

	Renderer->CreateAnimation("Fanbeam", "Fanbeam", 0.05f, false, 0, 9);
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->ChangeAnimation("Fanbeam");
}

void AFanbeam::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UseLaser(APlayGameMode::MainPlayer->GetRenderer()->GetDir());
	//공격이 보일때
	if (true == Renderer->IsActive())
	{
		//공격 애니메이션이 종료된 직후
		if (true == Renderer->IsCurAnimationEnd())
		{
			Renderer->SetActive(false);
			Collision->SetActive(false);
		}
		else
		{
			int a = 0;
		}
	}
	else // 공격이 실행되지 않을 때
	{
		if (0 < Delay) // 공격 쿨이 돌기 전
		{
			Renderer->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			Delay -= _DeltaTime;
		}
		else // 공격 시작
		{
			Delay = APlayGameMode::MainPlayer->GetAtkTime();
			Renderer->SetActive(true);
			Collision->SetActive(true);
		}
	}
}

void  AFanbeam::UseLaser(EEngineDir _Dir)
{
	if (EEngineDir::Right == _Dir)
	{
		Renderer->SetPosition({ (233.0f * ContentsValue::MultipleSize), (51.0f * ContentsValue::MultipleSize) });
		Collision->SetPosition({ (233.0f * ContentsValue::MultipleSize), (51.0f * ContentsValue::MultipleSize) });
	}
	else if (EEngineDir::Left == _Dir)
	{
		Renderer->SetPosition({ (-233.0f * ContentsValue::MultipleSize), (51.0f * ContentsValue::MultipleSize) });
		Collision->SetPosition({ (-233.0f * ContentsValue::MultipleSize), (51.0f * ContentsValue::MultipleSize) });
	}
}

void AFanbeam::CheckHit()
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

