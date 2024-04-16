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
	CreateMonsterAnimation("KFP");

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
	AddActorLocation(MonsterDirNormal * _DeltaTime * CalSpeed);
	if (MonsterPos.X > APlayer::PlayerPos.X)
	{
		Renderer->SetDir(EEngineDir::Left);
	}
	else
	{
		Renderer->SetDir(EEngineDir::Right);
	}


}

void AMonster::SetMonsterStatus(float _Hp, float _Atk, float _Speed, float _Exp)
{
	Hp = _Hp;
	Atk = _Atk;
	Speed = _Speed;
	CalSpeed = 200.0f * Speed;
	Exp = _Exp;
}

void AMonster::CreateMonsterAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.1f, true, 0, 2);
}

