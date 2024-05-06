#include "PreCompile.h"
#include "Logo.h"

ALogo::ALogo()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	SetRoot(Root);
}

ALogo::~ALogo()
{
}


void ALogo::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("holocure.png");
	Renderer->SetAutoSize(0.2f, true);
	Renderer->SetPosition(FVector({ 450.0f, 225.0f }));
	Renderer->SetOrder(ERenderOrder::UI);
}

void ALogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Move(_DeltaTime);
}

void ALogo::Move(float _DeltaTime)
{
	if (0.0f <= LogoMoveTime && LogoMoveTime < 1.3f)
	{
		UpSpeed -= _DeltaTime;
		Renderer->AddPosition(LogoMoveDir * UpSpeed * _DeltaTime);
		DownSpeed = 1.0f;
	}
	else if (1.3f <= LogoMoveTime && LogoMoveTime < 2.6f)
	{
		DownSpeed -= _DeltaTime;
		Renderer->AddPosition(LogoMoveDir * -1 * DownSpeed * _DeltaTime);
		UpSpeed = 1.0f;
	}
	else
	{
		LogoMoveTime = 0.0f;
	}

	LogoMoveTime += _DeltaTime;
}