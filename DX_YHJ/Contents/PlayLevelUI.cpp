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
	CharacterImage = CreateWidget<UImage>(GetWorld(), "HUDCharacter");

	CharacterFrame = nullptr;

	ExpBar = nullptr;
	ExpBarFrame = nullptr;

	HpBar = nullptr;
	HpBarFrame = nullptr;

	Money = nullptr;
	KillCount = nullptr;

	StageText = nullptr;
	PlayTime = nullptr;

}

void APlayLevelUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}