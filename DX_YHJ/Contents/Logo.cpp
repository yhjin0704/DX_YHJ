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
	Renderer->SetAutoSize(0.4f, true);
	Renderer->SetPosition(FVector({ 350.0f, 125.0f }));
	Renderer->SetOrder(ERenderOrder::UI);
}

void ALogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Move(_DeltaTime);
}

void ALogo::Move(float _DeltaTime)
{
	if (0.0f <= MoveTime && MoveTime < 1.5f)
	{
		UpSpeed -= _DeltaTime * 2.0f;
		Renderer->AddPosition(MoveDir * UpSpeed * _DeltaTime);
		DownSpeed = 1.0f;
	}
	else if (1.5f <= MoveTime && MoveTime < 3.0f)
	{
		DownSpeed -= _DeltaTime * 2.0f;
		Renderer->AddPosition(MoveDir * -1 * DownSpeed * _DeltaTime);
		UpSpeed = 1.0f;
	}
	else
	{
		MoveTime = 0.0f;
	}

	MoveTime += _DeltaTime;
}