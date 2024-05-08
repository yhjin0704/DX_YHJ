#include "PreCompile.h"
#include "HoloCursor.h"
#include "PlayGameMode.h"
#include "ContentsValue.h"

float4 AHoloCursor::CursorPos = FVector::Zero;
bool AHoloCursor::MouseAimOn = false;

AHoloCursor::AHoloCursor()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::Cursor);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->SetScale({ 1.0f * ContentsValue::MultipleSize, 1.0f * ContentsValue::MultipleSize });

	SetRoot(Root);

	InputOn();
}

AHoloCursor::~AHoloCursor()
{
}

void AHoloCursor::BeginPlay()
{
	Super::BeginPlay();

	CursorOFf();

	Renderer = CreateWidget<UImage>(GetWorld(), "HoloCursor");
	Renderer->SetSprite("spr_GameCursor_0.png");
	Renderer->SetAutoSize(ContentsValue::MultipleSize * 0.5f, true);
	Renderer->AddToViewPort(10);
}

void AHoloCursor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CursorPos = GEngine->EngineWindow.GetScreenMousePos();
	FVector CursorScreenPos = { CursorPos.X - (ContentsValue::WindowSize.X / 2.0f), -CursorPos.Y + (ContentsValue::WindowSize.Y / 2.0f) };

	if ("PlayLevel" == GetWorld()->GetName())
	{
		if (true != APlayGameMode::IsPause)
		{
			ChangeAimMode();
		}

		Collision->SetPosition(ContentsValue::PlayLevelMousePos);
	}
	else
	{
		Collision->SetPosition(CursorScreenPos);
	}

	if (true == APlayGameMode::IsPause)
	{
		MouseAimOn = false;
	}
	
	CheckAimMode(CursorScreenPos);
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

void AHoloCursor::CheckAimMode(FVector _CursorPos)
{
	if (true != MouseAimOn)
	{
		CursorOFf();
		Renderer->SetSprite("spr_GameCursor_0.png");
		Renderer->SetPosition(_CursorPos);
	}
	else
	{
		CursorOFf();
		Renderer->SetSprite("spr_GameCursor1_0.png");
		Renderer->SetPosition(_CursorPos);
	}
	
}