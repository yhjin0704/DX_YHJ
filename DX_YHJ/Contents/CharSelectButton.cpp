#include "PreCompile.h"
#include "CharSelectButton.h"
#include "LobbyGameMode.h"

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

	InputOn();
}

ACharSelectButton::~ACharSelectButton()
{
}

void ACharSelectButton::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("menu_charselecLocked2_0.png");
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->SetOrder(ERenderOrder::UI);

	SelectWhite->SetSprite("menu_charselect_White.png");
	SelectWhite->SetAutoSize(ContentsValue::MultipleSize, true);
	SelectWhite->SetOrder(ERenderOrder::FrontUI);
	SelectWhite->SetActive(false);
}

void ACharSelectButton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SelectWhiteFade(_DeltaTime);
	ColCheak();
}

void ACharSelectButton::Setting(std::string _Name)
{
	Name = _Name;
	Renderer->SetSprite("spr_" + _Name + "Portrait_0.png");
	IsPlayable = true;
}

void ACharSelectButton::SelectWhiteFade(float _DeltaTime)
{
	if (0.1f >= FadeAlpha)
	{
		IsFadeIn = true;
	}
	else if (0.5f <= FadeAlpha)
	{
		IsFadeIn = false;
	}

	if (true == IsFadeIn)
	{
		FadeAlpha += _DeltaTime * 2.0f;
		SelectWhite->SetMulColor({ 1.0f, 1.0f, 1.0f, FadeAlpha });
	}
	else
	{
		FadeAlpha -= _DeltaTime * 2.0f;
		SelectWhite->SetMulColor({ 1.0f, 1.0f, 1.0f, FadeAlpha });
	}
}

void ACharSelectButton::ColCheak()
{
	Collision->CollisionEnter(ECollisionOrder::Cursor, [=](std::shared_ptr<UCollision> _Collison)
		{
			IsCursorOn = true;

			SelectWhite->SetActive(true);

			if (true == IsPlayable)
			{
				ACharSelectUI::SelectCharName = Name;

				if (true == IsDown(VK_LBUTTON))
				{
					GEngine->ChangeLevel("PlayLevel");
				}
			}
		}
	);
	Collision->CollisionStay(ECollisionOrder::Cursor, [=](std::shared_ptr<UCollision> _Collison)
		{
			if (true == IsPlayable)
			{
				if (true == IsDown(VK_LBUTTON))
				{
					GEngine->ChangeLevel("PlayLevel");
				}
			}
		}
	);
	Collision->CollisionExit(ECollisionOrder::Cursor, [=](std::shared_ptr<UCollision> _Collison)
		{

			IsCursorOn = false;

			SelectWhite->SetActive(false);
		}
	);
}