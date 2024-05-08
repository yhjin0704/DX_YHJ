#include "PreCompile.h"
#include "MainMenuButton.h"

AMainMenuButton::AMainMenuButton()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::MAX);
	Renderer->SetOrder(ERenderOrder::UI);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale({ 170.0f * ContentsValue::MultipleSize, 25.0f * ContentsValue::MultipleSize });
	Collision->SetCollisionGroup(ECollisionOrder::UIButton);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

AMainMenuButton::~AMainMenuButton()
{
}

void AMainMenuButton::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("hud_OptionButton_0.png");
	Renderer->SetAutoSize(0.5f * ContentsValue::MultipleSize, true);
}

void AMainMenuButton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CollisionCheck();
	SelectChange();
}

void AMainMenuButton::CollisionCheck()
{
	Collision->CollisionEnter(ECollisionOrder::Cursor, [=](std::shared_ptr<UCollision> _Collison)
		{
			IsCursorOn = true;
		}
	);
	Collision->CollisionExit(ECollisionOrder::Cursor, [=](std::shared_ptr<UCollision> _Collison)
		{
			IsCursorOn = false;
		}
	);
}

void AMainMenuButton::SelectChange()
{
	if (true == IsCursorOn)
	{
		Renderer->SetSprite("hud_OptionButton_1.png");
		Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	}
	else
	{
		Renderer->SetSprite("hud_OptionButton_0.png");
		Renderer->SetAutoSize(0.9f * ContentsValue::MultipleSize, true);
	}
}