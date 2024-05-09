#include "PreCompile.h"
#include "CharSelectButton.h"

ACharSelectButton::ACharSelectButton()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	SelectWhite = CreateDefaultSubObject<USpriteRenderer>("SelectWhite");
	SelectWhite->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetScale({ 42.5f * ContentsValue::MultipleSize, 40.0f * ContentsValue::MultipleSize });
	Collision->SetCollisionGroup(ECollisionOrder::UIButton);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->SetupAttachment(Root);

	SetRoot(Root);
}

ACharSelectButton::~ACharSelectButton()
{
}

void ACharSelectButton::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("menu_charselecLocked2_0.png");
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->SetOrder(ERenderOrder::FrontUI);

	SelectWhite->SetSprite("menu_charselect_White.png");
	SelectWhite->SetAutoSize(ContentsValue::MultipleSize, true);
	SelectWhite->SetOrder(ERenderOrder::FrontUI);
	SelectWhite->SetActive(false);
}

void ACharSelectButton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Collision->CollisionEnter(ECollisionOrder::Cursor, [=](std::shared_ptr<UCollision> _Collison)
		{
			IsCursorOn = true;

			SelectWhite->SetActive(true);
		}
	);
	Collision->CollisionExit(ECollisionOrder::Cursor, [=](std::shared_ptr<UCollision> _Collison)
		{
			
			IsCursorOn = false;

			SelectWhite->SetActive(false);
		}
	);
}

void ACharSelectButton::Setting(std::string _Name)
{
	Name = _Name;
	Renderer->SetSprite("spr_" + _Name + "Portrait_0.png.png");
}