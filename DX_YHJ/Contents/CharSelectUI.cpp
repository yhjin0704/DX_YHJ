#include "PreCompile.h"
#include "CharSelectUI.h"
#include "ContentsValue.h"

ACharSelectUI::ACharSelectUI()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	SelectTextBox = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SelectTextBox->SetupAttachment(Root);

	BackCharL = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	BackCharL->SetupAttachment(Root);

	BackCharR = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	BackCharR->SetupAttachment(Root);

	ExplanationBox0 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	ExplanationBox0->SetupAttachment(Root);

	ExplanationBox1 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	ExplanationBox1->SetupAttachment(Root);

	ExplanationBox2 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	ExplanationBox2->SetupAttachment(Root);

	ExplanationFrame = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	ExplanationFrame->SetupAttachment(Root);

	CharAnimation = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	CharAnimation->SetupAttachment(Root);

	SetRoot(Root);
}

ACharSelectUI::~ACharSelectUI()
{
}

void ACharSelectUI::BeginPlay()
{
	Super::BeginPlay();

	CreateCharAnimation("Ame");
	CreateCharAnimation("Aqua");
	CreateCharAnimation("Ayame");
	CreateCharAnimation("AZKiPortrait");
	CreateCharAnimation("Kiara"); 
	CreateCharAnimation("Kronii");

	SelectTextBox->SetSprite("menu_charselecLocked_0.png");
	SelectTextBox->SetScale({ 1000.0f * ContentsValue::MultipleSize, 25.0f * ContentsValue::MultipleSize });
	SelectTextBox->SetPosition({ 0.0f, 157.5f * ContentsValue::MultipleSize });
	SelectTextBox->SetOrder(ERenderOrder::UI);

	BackCharL->SetSprite("spr_Title_" + SelectCharName + ".png");
	BackCharL->SetAutoSize(2.0f * ContentsValue::MultipleSize, true);
	BackCharL->SetPosition({ -280.0f * ContentsValue::MultipleSize, 0.0f });
	BackCharL->SetOrder(ERenderOrder::BackUI);
	BackCharL->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

	BackCharR->SetSprite("spr_Title_" + SelectCharName + ".png");
	BackCharR->SetAutoSize(2.0f * ContentsValue::MultipleSize, true);
	BackCharR->SetDir(EEngineDir::Left);
	BackCharR->SetPosition({ 280.0f * ContentsValue::MultipleSize, 0.0f });
	BackCharR->SetOrder(ERenderOrder::BackUI);
	BackCharR->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

	ExplanationBox0->SetSprite("menu_charselecLocked_0.png");
	ExplanationBox0->SetScale({ 225.0f * ContentsValue::MultipleSize, 125.0f * ContentsValue::MultipleSize });
	ExplanationBox0->SetPosition({ -200.0f * ContentsValue::MultipleSize, -100.0f * ContentsValue::MultipleSize,-10.0f * ContentsValue::MultipleSize });
	ExplanationBox0->SetOrder(ERenderOrder::UI);

	ExplanationBox1->SetSprite("menu_charselecLocked_0.png");
	ExplanationBox1->SetScale({ 225.0f * ContentsValue::MultipleSize, 125.0f * ContentsValue::MultipleSize });
	ExplanationBox1->SetPosition({ 0.0f,-100.0f * ContentsValue::MultipleSize,-10.0f * ContentsValue::MultipleSize });
	ExplanationBox1->SetOrder(ERenderOrder::UI);

	ExplanationBox2->SetSprite("menu_charselecLocked_0.png");
	ExplanationBox2->SetScale({ 225.0f * ContentsValue::MultipleSize,125.0f * ContentsValue::MultipleSize });
	ExplanationBox2->SetPosition({ 200.0f * ContentsValue::MultipleSize, -100.0f * ContentsValue::MultipleSize,-10.0f * ContentsValue::MultipleSize });
	ExplanationBox2->SetOrder(ERenderOrder::UI);

	ExplanationFrame->SetSprite("menu_charselecLocked_1.png");
	ExplanationFrame->SetAutoSize(0.5f * ContentsValue::MultipleSize, true);
	ExplanationFrame->SetPosition({ 0.0f, -100.0f * ContentsValue::MultipleSize, -10.0f * ContentsValue::MultipleSize });
	ExplanationFrame->SetOrder(ERenderOrder::UIFrame);

	CharAnimation->SetAutoSize(4.0f, true);
	CharAnimation->SetPosition({ -240.0f * ContentsValue::MultipleSize, -75.0f * ContentsValue::MultipleSize });
	CharAnimation->SetOrder(ERenderOrder::FrontUI);

	CharAnimation->ChangeAnimation(SelectCharName + "_Idle");

	SelectText = CreateWidget<UTextWidget>(GetWorld(), "SelectText");
	SelectText->AddToViewPort(EUIOrder::Text);
	SelectText->SetScale(ContentsValue::MultipleSize * 15);
	SelectText->SetFont("Galmuri14");
	SelectText->SetColor(Color8Bit::White);
	SelectText->SetPosition(FVector(0.f, 315.f));
	SelectText->SetText("아이돌을 선택하세요");
}

void ACharSelectUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ChangeSelectCharAnimation();
}

void ACharSelectUI::CreateCharAnimation(std::string _Name)
{
	CharAnimation->CreateAnimation(_Name + "_Idle", _Name, 0.1f, true, 0, 3);
	CharAnimation->CreateAnimation(_Name + "_Run", _Name, 0.1f, true, 4, 9);
}

void ACharSelectUI::ChangeSelectCharAnimation()
{
	if (CharAnimation->IsCurAnimationEnd())
	{
		switch (Count)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			CharAnimation->ChangeAnimation(SelectCharName + "_Run");
			Count++;
			break;
		case 5:
		case 6:
			CharAnimation->ChangeAnimation(SelectCharName + "_Idle");
			Count++;
			break;
		case 7:
			Count = 0;
			break;
		default:
			break;
		}
	}
}