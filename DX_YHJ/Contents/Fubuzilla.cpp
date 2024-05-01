#include "PreCompile.h"
#include "Fubuzilla.h"
#include "Player.h"

AFubuzilla::AFubuzilla()
{
	Collision->SetScale({ 16.0f * ContentsValue::MultipleSize, 16.0f * ContentsValue::MultipleSize });
	Collision->SetPosition({ GetActorLocation().X, GetActorLocation().Y + (10.0f * ContentsValue::MultipleSize) });

	SavedRenderer->SetPosition({ GetActorLocation().X, GetActorLocation().Y + (50.0f * ContentsValue::MultipleSize) });

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
}

void AFubuzilla::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (false == IsSaved)
	{
		Move(_DeltaTime);

		if (0 > Dir.X)
		{
			Renderer->SetDir(EEngineDir::Left);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Right);
		}

		CheakSaved();
		CheckHit();
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