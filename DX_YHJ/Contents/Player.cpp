#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
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

	CreatePlayerAnimation("Kronii");
	CreatePlayerAnimation("Ame");

	Renderer->SetOrder(ERenderOrder::Player);

	AtkDir->SetSprite("spr_arrow_1.png");
	AtkDir->SetAutoSize(1.0f, true);
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
}

void APlayer::CreatePlayerAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.1f, true, 0, 3);
	Renderer->CreateAnimation(_Name + "_Run", _Name, 0.1f, true, 4, 9);
}

void APlayer::CheckMouseAimMode()
{
	if (true == AHoloCursor::MouseAimOn)
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