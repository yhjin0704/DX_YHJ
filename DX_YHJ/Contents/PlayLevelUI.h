#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Image.h>
#include <EngineCore/TextWidget.h>

class APlayLevelUI : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayLevelUI();
	~APlayLevelUI();

	// delete Function
	APlayLevelUI(const APlayLevelUI& _Other) = delete;
	APlayLevelUI(APlayLevelUI&& _Other) noexcept = delete;
	APlayLevelUI& operator=(const APlayLevelUI& _Other) = delete;
	APlayLevelUI& operator=(APlayLevelUI&& _Other) noexcept = delete;

	void SetPlayTime(float _PlayTime)
	{
		PlayTime = lround(_PlayTime);
	}

	void StartSetting();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* CharacterImage = nullptr;
	UImage* CharacterFrame = nullptr;

	UImage* ExpBarFrame = nullptr;

	UImage* HpHUD = nullptr;
	UImage* HpBarFrame = nullptr;
	UImage* HpBar = nullptr;
	UTextWidget* HpText = nullptr;

	UImage* EquipUIFrame = nullptr;
	UImage* Weapon = nullptr;
	UImage* Item = nullptr;

	UImage* MoneyIcon = nullptr;
	UTextWidget* MoneyText = nullptr;
	UImage* KillCountIcon = nullptr;
	UTextWidget* KillCountText = nullptr;

	UImage* StageText = nullptr;
	UTextWidget* PlayTimeUI = nullptr;

	std::string PlayerName = "";
	int Money = 0;
	int KillCount = 0;
	int PlayTime = 0;

	void HpUpdate();
	void MoneyUpdate();
	void KillCountUpdate();
	void TimeUpdate();
};
