#include "PreCompile.h"
#include "LobbyBackAnimationBar.h"

ALobbyBackAnimationBar::ALobbyBackAnimationBar()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	SetRoot(Root);
}

ALobbyBackAnimationBar::~ALobbyBackAnimationBar()
{
}

void ALobbyBackAnimationBar::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(700.0f, 300.0f, 100.0f));
	Renderer->SetSprite("menu_charselec_bar_0.png");
	Renderer->SetScale(FVector{ 1.0f,3.5f });
	Renderer->SetPosition(FVector{ 1.5f,0.0f });
	Renderer->SetOrder(ERenderOrder::BackObject);
	Renderer->SetRotationDeg({ 0.0f,0.0f,-10.0f });
	Renderer->SetMulColor(float4{ 1.0f, 1.0f, 1.0f, 0.7f });

	DelayCallBack(8.0f, [=]()
		{
			Destroy();
		});
}

void ALobbyBackAnimationBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Move(_DeltaTime);
}

void ALobbyBackAnimationBar::Move(float _DeltaTime)
{
	Renderer->AddPosition(FVector::Left * _DeltaTime * Speed);
}
