#include "PreCompile.h"
#include "Bullet.h"

ABullet::ABullet()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(ERenderOrder::Weapon);
	Renderer->SetPivot(EPivot::MAX);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::Weapon);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);

	SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y });

	Angle = APlayGameMode::MainPlayer->GetAngle();
}

ABullet::~ABullet()
{
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Renderer->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });

	Dir = float4::DegToDir(Angle);
	Dir.Z = 0.0f;

	AddActorLocation(Dir * _DeltaTime * BulletSpeed * ContentsValue::MultipleSize);
}

void ABullet::CheakTimeDestory(float _DeltaTime)
{
	TimeDestory -= _DeltaTime;
	if (0 > TimeDestory)
	{
		Destroy();
	}
}
