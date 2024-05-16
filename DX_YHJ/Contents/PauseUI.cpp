#include "PreCompile.h"
#include "PauseUI.h"

APauseUI::APauseUI()
{
}

APauseUI::~APauseUI()
{
}

void APauseUI::BeginPlay()
{
	Super::BeginPlay();

	PauseBack = CreateWidget<UImage>(GetWorld(), "PuaseBack");
	PauseBack->AddToViewPort(EUIOrder::PauseBack);
	PauseBack->SetSprite("menu_charselecLocked_0.png");
	PauseBack->SetAutoSize(ContentsValue::MultipleSize * 15.0f, true);
	PauseBack->SetPosition(FVector(0.f, 0.f));
	PauseBack->SetActive(false);

	PauseText = CreateWidget<UImage>(GetWorld(), "PausedText");
	PauseText->AddToViewPort(EUIOrder::PauseText);
	PauseText->SetSprite("Paused.png");
	PauseText->SetAutoSize(ContentsValue::MultipleSize / 2.0f, true);
	PauseText->SetPosition(FVector(0.f, 200.f));
	PauseText->SetActive(false);

	PauseFrame = CreateWidget<UImage>(GetWorld(), "SetBack");
	PauseFrame->AddToViewPort(EUIOrder::PauseFrame);
	PauseFrame->SetSprite("hud_pausemenu_0.png");
	PauseFrame->SetAutoSize(ContentsValue::MultipleSize, true);
	PauseFrame->SetPosition(FVector(0.f, 0.f));
	PauseFrame->SetActive(false);

	for (int i = 0; i < 1; i++)
	{
		std::shared_ptr<APauseButton> PauseButton = GetWorld()->SpawnActor<APauseButton>("PauseButton");
		PauseButton->SetActorLocation({ 0.0f, 120.0f - (60.0f * i) });
		PauseButton->AllActiveOff();
		VPauseButton.push_back(PauseButton);
	}
	{
		VPauseButton[0]->SettingLocation();
		VPauseButton[0]->GetTextWidget()->SetText("³ª°¡±â");
	}
}

void APauseUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}