#include "PreCompile.h"
#include "PauseButton.h"

APauseButton::APauseButton()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);

	SetRoot(Root);
}

APauseButton::~APauseButton()
{
}

void APauseButton::BeginPlay()
{
	Super::BeginPlay();

	Renderer = CreateWidget<UImage>(GetWorld(), "PuaseButton");
	Renderer->AddToViewPort(EUIOrder::PauseObject);
	Renderer->SetSprite("hud_Button_0.png");
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);

	Collision->SetScale({ 90.0f * ContentsValue::MultipleSize, 25.0f * ContentsValue::MultipleSize });
	Collision->SetCollisionGroup(ECollisionOrder::UIButton);
	Collision->SetCollisionType(ECollisionType::Rect);

	Text = CreateWidget<UTextWidget>(GetWorld(), "Text");
	Text->AddToViewPort(EUIOrder::PauseText);
	Text->SetScale(ContentsValue::MultipleSize * 10.0f);
	Text->SetFont("Galmuri9");
	Text->SetColor(Color8Bit::White);
}

void APauseButton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//Collision->SetPosition(GetActorLocation());

	CollisionCheck();
	SelectChange();
}

void APauseButton::CollisionCheck()
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

void APauseButton::SelectChange()
{
	if (true == IsSelect)
	{
		Renderer->SetSprite("hud_Button_1.png");
		Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
		Text->SetColor(Color8Bit::Black);
	}
	else
	{
		Renderer->SetSprite("hud_Button_0.png");
		Renderer->SetAutoSize(1.2f * ContentsValue::MultipleSize, true);
		Text->SetColor(Color8Bit::White);
	}
}