#include "PreCompile.h"
#include "Fubuzilla.h"
#include "Player.h"

AFubuzilla::AFubuzilla()
{
	LaserRenderer = CreateDefaultSubObject<USpriteRenderer>("LaserRenderer");
	LaserRenderer->SetupAttachment(Root);
	LaserRenderer->SetAutoSize(5.0f * ContentsValue::MultipleSize, true);
	LaserRenderer->SetOrder(ERenderOrder::Weapon);

	LaserCollision = CreateDefaultSubObject<UCollision>("Collision");
	LaserCollision->SetupAttachment(Root);
	LaserCollision->SetCollisionGroup(ECollisionOrder::Monster);
	LaserCollision->SetCollisionType(ECollisionType::Rect);
	LaserCollision->SetScale({ 450.0f * 5.0f * ContentsValue::MultipleSize, 20.0f * 5.0f * ContentsValue::MultipleSize });

	UseLaserCheckCollision = CreateDefaultSubObject<UCollision>("Collision");
	UseLaserCheckCollision->SetupAttachment(Root);
	UseLaserCheckCollision->SetCollisionGroup(ECollisionOrder::ZoneCheck);
	UseLaserCheckCollision->SetCollisionType(ECollisionType::Rect);
	UseLaserCheckCollision->SetScale({ 4800.0f * ContentsValue::MultipleSize, 216.0f * ContentsValue::MultipleSize });
	UseLaserCheckCollision->SetPosition({ GetActorLocation().X, GetActorLocation().Y + (72.0f * ContentsValue::MultipleSize) });

	LaserRenderer->SetActive(false);
	LaserCollision->SetActive(false);

	SavedRenderer->SetPosition({ GetActorLocation().X, GetActorLocation().Y + (50.0f * ContentsValue::MultipleSize) });

	Collision->SetScale({ 96.0f * ContentsValue::MultipleSize, 96.0f * ContentsValue::MultipleSize });

	OverCheckCollision->SetScale({ 192.0f * ContentsValue::MultipleSize, 120.0f * ContentsValue::MultipleSize });
	OverCheckCollision->SetPosition({ GetActorLocation().X, GetActorLocation().Y + (78.0f * ContentsValue::MultipleSize) });

	Name = "Fubuzilla";
	Hp = 8000.0f;
	Atk = 15.0f;
	Speed = 0.8f;
	CalSpeed = ContentsValue::BaseSpeed * Speed;
	Exp = 2000.0f;
}

AFubuzilla::~AFubuzilla()
{

}

void AFubuzilla::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("Fubuzilla", "Fubuzilla", 0.1f, true, 0, 11);
	Renderer->SetAutoSize(3.0f * ContentsValue::MultipleSize, true);
	Renderer->ChangeAnimation("Fubuzilla");

	LaserRenderer->CreateAnimation("FubuLaserBefore", "FubuLaser", 0.1f, false, 0, 23);
	LaserRenderer->CreateAnimation("FubuLaserAfter", "FubuLaser", 0.1f, false, 24, 33);
	LaserRenderer->ChangeAnimation("FubuLaserBefore");
}

void AFubuzilla::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (false == IsSaved)
	{
		Move(_DeltaTime);

		UseLaserCheck();

		if (0 > Dir.X)
		{
			Renderer->SetDir(EEngineDir::Left);

			FVector DirLeftPos = { (32.0f * ContentsValue::MultipleSize), (50.0f * ContentsValue::MultipleSize) };
			Collision->SetPosition(DirLeftPos);

			UseLaser(EEngineDir::Left);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Right);

			FVector DirRightPos = { (32.0f * ContentsValue::MultipleSize), (50.0f * ContentsValue::MultipleSize) };
			Collision->SetPosition(DirRightPos);
			
			UseLaser(EEngineDir::Right);
		}
		CheakSaved();
	}
	else
	{
		Saved(_DeltaTime);
	}
}

void AFubuzilla::Move(float _DeltaTime)
{
	Dir = APlayer::PlayerColPos - GetActorLocation();
	Dir = Dir.Normalize2DReturn();

	AddActorLocation(Dir * _DeltaTime * CalSpeed);
}

void AFubuzilla::UseLaserCheck()
{
	UseLaserCheckCollision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			IsUseLaser = true;
		}
	);

	UseLaserCheckCollision->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			IsUseLaser = true;
		}
	);
}

void AFubuzilla::UseLaser(EEngineDir _Dir)
{
	if (true == IsUseLaser)
	{
		LaserRenderer->SetActive(true);
		LaserRenderer->SetDir(_Dir);
		if (EEngineDir::Right == _Dir)
		{
			LaserRenderer->SetPosition({ (1200.0f * ContentsValue::MultipleSize), (80.0f * ContentsValue::MultipleSize) });
			LaserCollision->SetPosition({ (1200.0f * ContentsValue::MultipleSize), (80.0f * ContentsValue::MultipleSize) });
		}
		else if (EEngineDir::Left == _Dir)
		{
			LaserRenderer->SetPosition({ (-1200.0f * ContentsValue::MultipleSize), (80.0f * ContentsValue::MultipleSize) });
			LaserCollision->SetPosition({ (-1200.0f * ContentsValue::MultipleSize), (80.0f * ContentsValue::MultipleSize) });
		}
		
		switch (Laser)
		{
		case ELaser::Stay:
			LaserRenderer->ChangeAnimation("FubuLaserBefore");
			Laser = ELaser::Ready;
			break;
		case ELaser::Ready:
			if (true == LaserRenderer->IsCurAnimationEnd())
			{
				LaserRenderer->ChangeAnimation("FubuLaserAfter");
				LaserCollision->SetActive(true);
				Laser = ELaser::Shot;
			}
			break;
		case ELaser::Shot:
			if (true == LaserRenderer->IsCurAnimationEnd())
			{
				LaserRenderer->SetActive(false);
				LaserCollision->SetActive(false);
				Laser = ELaser::Stay;
				IsUseLaser = false;
			}
			break;
		default:
			break;
		}
	}
}