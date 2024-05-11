#include "PreCompile.h"
#include "PlayLevelUI.h"
#include "PlayGameMode.h"

APlayLevelUI::APlayLevelUI()
{
	
}

APlayLevelUI::~APlayLevelUI()
{
}

void APlayLevelUI::BeginPlay()
{
	Super::BeginPlay();
	CharacterImage = CreateWidget<UImage>(GetWorld(), "CharacterImage");
	CharacterImage->AddToViewPort(EUIOrder::PlayInfo);
	CharacterImage->SetAutoSize(ContentsValue::MultipleSize, true);
	CharacterImage->SetPosition(FVector(-590.f, 288.f));

	CharacterFrame = CreateWidget<UImage>(GetWorld(), "CharacterFrame");
	CharacterFrame->AddToViewPort(EUIOrder::Frame);
	CharacterFrame->SetSprite("HUDCharacterFrame.png");
	CharacterFrame->SetAutoSize(ContentsValue::MultipleSize, true);
	CharacterFrame->SetPosition(FVector(-587.f, 293.f));

	ExpBarBack = CreateWidget<UImage>(GetWorld(), "ExpBarBack");
	ExpBarBack->AddToViewPort(EUIOrder::Frame);
	ExpBarBack->SetSprite("hud_expbar_bg_0.png");
	ExpBarBack->SetAutoSize(ContentsValue::MultipleSize, true);
	ExpBarBack->SetPosition(FVector(5.0f * ContentsValue::MultipleSize, 170.0f * ContentsValue::MultipleSize));

	HpHUD = CreateWidget<UImage>(GetWorld(), "HpHUD");
	HpBar = CreateWidget<UImage>(GetWorld(), "HpBar");

	Money = CreateWidget<UImage>(GetWorld(), "Money");
	KillCount = CreateWidget<UImage>(GetWorld(), "KillCount");

	StageText = CreateWidget<UImage>(GetWorld(), "StageText");
	PlayTime = CreateWidget<UImage>(GetWorld(), "PlayTime");

}

void APlayLevelUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayLevelUI::StartSetting()
{
	PlayerName = APlayGameMode::MainPlayer->GetName();
	CharacterImage->SetSprite("spr_" + PlayerName + "Portrait_0.png");
}