#include "PreCompile.h"
#include "NomalMonster.h"
#include "Player.h"

ANomalMonster::ANomalMonster()
{
}

ANomalMonster::~ANomalMonster()
{
}

void ANomalMonster::BeginPlay()
{
	Super::BeginPlay();

	CreateMonsterAnimation("Shrimp");
	CreateMonsterAnimation("Deadbeat");
	CreateMonsterAnimation("Takodachi");
	CreateMonsterAnimation("KFP");

	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->ChangeAnimation(Name);
}

void ANomalMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (false == IsSaved)
	{
		Move(_DeltaTime, MoveType);

		Collision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
			{
				IsContectPlayer = true;
			}
		);
		Collision->CollisionExit(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
			{
				IsContectPlayer = false;
			}
		);

		if (false == IsContectPlayer)
		{
			if (0 > Dir.X)
			{
				Renderer->SetDir(EEngineDir::Left);
			}
			else
			{
				Renderer->SetDir(EEngineDir::Right);
			}
		}

		CheckSaved();
	}
	else
	{
		Saved(_DeltaTime);
	}
}

void ANomalMonster::CreateMonsterAnimation(std::string _Name, int _MaxIndex)
{
	Renderer->CreateAnimation(_Name, _Name, 0.1f, true, 0, _MaxIndex);
}