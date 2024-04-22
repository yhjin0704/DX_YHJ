#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>
#include "HoloCursor.h"

float4 APlayer::PlayerPos = float4::Zero;

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	AtkDir = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	AtkDir->SetupAttachment(Root);
	AtkDir->SetPivot(EPivot::MAX);

	SetRoot(Root);

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerAnimation("Ame");
	CreatePlayerAnimation("Aqua");
	CreatePlayerAnimation("Ayame");
	CreatePlayerAnimation("AZKiPortrait");
	CreatePlayerAnimation("Kronii");

	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->SetOrder(ERenderOrder::Player);

	AtkDir->SetOrder(ERenderOrder::Player);
	AtkDir->SetPosition(FVector{ PlayerPos.X, PlayerPos.Y + (20.0f * ContentsValue::MultipleSize) });

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	PlayerPos = GetActorLocation();

	CheckMouseAimMode();
	ChangeMoveAimAtkDir();
	ChangeMouseAimAtkDir();
}

void APlayer::CreatePlayerAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.1f, true, 0, 3);
	Renderer->CreateAnimation(_Name + "_Run", _Name, 0.1f, true, 4, 9);
}

void APlayer::CheckMouseAimMode()
{
	if (false == AHoloCursor::MouseAimOn)
	{
		AtkDir->SetSprite("spr_arrow_1.png");
		AtkDir->SetAutoSize(ContentsValue::MultipleSize, true);
	}
	else
	{
		AtkDir->SetSprite("spr_arrow_2.png");
		AtkDir->SetAutoSize(ContentsValue::MultipleSize, true);
	}
}

void APlayer::ChangeMoveAimAtkDir()
{
	if (false == AHoloCursor::MouseAimOn)
	{
		switch (PlayerDir)
		{
		case EPlayerDir::N:
			Angle = 90.0f;
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::NE:
			Angle = 45.0f;
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::E:
			Angle = 0.0f;
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::SE:
			Angle = 315.0f;
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::S:
			Angle = 270.0f;
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::SW:
			Angle = 225.0f;
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::W:
			Angle = 180.0f;
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::NW:
			Angle = 135.0f;
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		default:
			break;
		}
	}
}

void APlayer::ChangeMouseAimAtkDir()
{
	if (true == AHoloCursor::MouseAimOn)
	{
		Angle = atan2f((ContentsValue::PlayLevelMousePos.Y - APlayer::PlayerPos.Y), (ContentsValue::PlayLevelMousePos.X - APlayer::PlayerPos.X)) * 180.0f / UEngineMath::PI;
		AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });

		if (-90.0f <= Angle && 90.0f > Angle)
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Left);
		}
	}
}