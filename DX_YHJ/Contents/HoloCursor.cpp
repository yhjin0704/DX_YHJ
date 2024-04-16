#include "PreCompile.h"
#include "HoloCursor.h"

float4 AHoloCursor::CursorPos = FVector::Zero;

AHoloCursor::AHoloCursor()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Root);
	Renderer->SetupAttachment(Root);
	InputOn();
}

AHoloCursor::~AHoloCursor()
{
}

void AHoloCursor::BeginPlay()
{
	Super::BeginPlay();

	CursorOFf();
	Renderer->SetSprite("spr_GameCursor_0.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Cursor);

	CursorPos = GEngine->EngineWindow.GetScreenMousePos();
}

void AHoloCursor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true != MouseAimOn && true == IsDown(VK_LBUTTON))
	{
		CursorOFf();
		Renderer->SetSprite("spr_GameCursor1_0.png");
		MouseAimOn = true;

	}
	else if (true == MouseAimOn && true == IsDown(VK_LBUTTON))
	{
		CursorOFf();
		Renderer->SetSprite("spr_GameCursor_0.png");
		MouseAimOn = false;
	}
}

void AHoloCursor::CursorOFf()
{
	ShowCursor(FALSE);
}
