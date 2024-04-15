#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"

AMonster::AMonster()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetPivot(EPivot::BOT);

	SetRoot(Renderer);
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	CreateMonsterAnimation("Shrimp");
	CreateMonsterAnimation("Deadbeat");
	CreateMonsterAnimation("Takodachi");
	CreateMonsterAnimation("Baerat");

	Renderer->SetAutoSize(1.0f, true);
	Renderer->ChangeAnimation(Name);
	Renderer->SetOrder(ERenderOrder::Monster);
}


void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector MonsterPos = GetActorLocation();


	FVector MonsterDir = APlayer::PlayerPos - MonsterPos;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();
	AddActorLocation(MonsterDirNormal * _DeltaTime * Speed);
	if (MonsterPos.X > APlayer::PlayerPos.X)
	{
		Renderer->SetDir(EEngineDir::Left);
	}
	else
	{
		Renderer->SetDir(EEngineDir::Right);
	}


}

void AMonster::CreateMonsterAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.1f, true, 0, 2);
}