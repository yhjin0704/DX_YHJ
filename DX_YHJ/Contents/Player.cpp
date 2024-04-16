#include "PreCompile.h"
#include "Player.h"
#include "ContentsValue.h"
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

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Player);

	AtkDir->SetOrder(ERenderOrder::Player);
	AtkDir->SetPosition(FVector{ PlayerPos.X, PlayerPos.Y + 20.0f });

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
		AtkDir->SetAutoSize(1.0f, true);
	}
	else
	{
		AtkDir->SetSprite("spr_arrow_2.png");
		AtkDir->SetAutoSize(1.0f, true);
	}
}

void APlayer::ChangeMoveAimAtkDir()
{
	if (false == AHoloCursor::MouseAimOn)
	{
		switch (PlayerDir)
		{
		case EPlayerDir::N:
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, 90.0f });
			break;
		case EPlayerDir::NE:
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, 45.0f });
			break;
		case EPlayerDir::E:
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, 0.0f });
			break;
		case EPlayerDir::SE:
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, 315.0f });
			break;
		case EPlayerDir::S:
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, 270.0f });
			break;
		case EPlayerDir::SW:
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, 225.0f });
			break;
		case EPlayerDir::W:
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, 180.0f });
			break;
		case EPlayerDir::NW:
			AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, 135.0f });
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
		float angle = atan2f((ContentsValue::PlayLevelMousePos.Y - APlayer::PlayerPos.Y), (ContentsValue::PlayLevelMousePos.X - APlayer::PlayerPos.X)) * 180.0f / UEngineMath::PI;
		AtkDir->SetRotationDeg(FVector{ 0.0f, 0.0f, angle });

		if (270.0f <= angle || 90.0f > angle)
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Left);
		}
	}
}