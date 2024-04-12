#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("Kronii Idle", "Kronii", 0.1f, true, 0, 3);
	Renderer->CreateAnimation("Kronii Run", "Kronii", 0.1f, true, 4, 9);

	StateInit();
	Renderer->SetOrder(ERenderOrder::Player);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}