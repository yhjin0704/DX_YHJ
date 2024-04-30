#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Image.h>

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* ExpBar = nullptr;
	UImage* HpBar = nullptr;
	UImage* Money = nullptr;
	UImage* KillCount = nullptr;
};
