#include "PreCompile.h"
#include "HoloCursor.h"
#include "ContentsValue.h"

float4 AHoloCursor::CursorPos = FVector::Zero;
bool AHoloCursor::MouseAimOn = false;

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
	Renderer->SetAutoSize(ContentsValue::MultipleSize * 0.5f, true);
	Renderer->SetOrder(ERenderOrder::Cursor);

	CursorPos = GEngine->EngineWindow.GetScreenMousePos();
}

void AHoloCursor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if ("PlayLevel" == GetWorld()->GetName())
	{
		ChangeAimMode();
		CheckAimMode();
	}
}

void AHoloCursor::CursorOFf()
{
	ShowCursor(FALSE);
}

void AHoloCursor::ChangeAimMode()
{
	if (true == IsDown(VK_LBUTTON))
	{
		if (true != MouseAimOn) 
		{
			MouseAimOn = true;
		}
		else
		{
			MouseAimOn = false;
		}
	}
}

void AHoloCursor::CheckAimMode()
{
	if (true != MouseAimOn)
	{
		CursorOFf();
		Renderer->SetSprite("spr_GameCursor_0.png");
		Renderer->SetPivot(EPivot::LEFTTOP);
	}
	else
	{
		CursorOFf();
		Renderer->SetSprite("spr_GameCursor1_0.png");
		Renderer->SetPivot(EPivot::MAX);
	}
}