#include "PreCompile.h"
#include "PlayLevelUI.h"

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

	CharacterFrame = CreateWidget<UImage>(GetWorld(), "CharacterFrame");

	ExpBarBack = CreateWidget<UImage>(GetWorld(), "ExpBarBack");

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