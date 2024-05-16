#pragma once
#include <EngineCore/Actor.h>
#include "PauseButton.h"

class APauseUI : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APauseUI();
	~APauseUI();

	// delete Function
	APauseUI(const APauseUI& _Other) = delete;
	APauseUI(APauseUI&& _Other) noexcept = delete;
	APauseUI& operator=(const APauseUI& _Other) = delete;
	APauseUI& operator=(APauseUI&& _Other) noexcept = delete;

	void AllActiveOff()
	{
		PauseBack->SetActive(false);
		PauseText->SetActive(false);
		PauseFrame->SetActive(false);
		for (VPauseButtonIter = VPauseButton.begin(); VPauseButtonIter != VPauseButton.end(); ++VPauseButtonIter)
		{
			std::shared_ptr<APauseButton> PauseButton = *VPauseButtonIter;
			PauseButton->AllActiveOff();
		}
	}

	void AllActiveOn()
	{
		PauseBack->SetActive(true);
		PauseText->SetActive(true);
		PauseFrame->SetActive(true);
		for (VPauseButtonIter = VPauseButton.begin(); VPauseButtonIter != VPauseButton.end(); ++VPauseButtonIter)
		{
			std::shared_ptr<APauseButton> PauseButton = *VPauseButtonIter;
			PauseButton->AllActiveOn();
		}
	}

	int GetVPauseButtonSize()
	{
		return VPauseButton.size();
	}

	bool GetVPauseButtonIsCursorOn(int _VectorNum)
	{
		return VPauseButton[_VectorNum]->GetIsCursorOn();
	}

	void SetVPauseButtonIsSelect(int _VectorNum, bool _IsSelect)
	{
		VPauseButton[_VectorNum]->SetIsSelect(_IsSelect);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* PauseBack = nullptr;
	UImage* PauseText = nullptr;
	UImage* PauseFrame = nullptr;
	std::vector<std::shared_ptr<APauseButton>> VPauseButton;
	std::vector<std::shared_ptr<APauseButton>>::iterator VPauseButtonIter = VPauseButton.begin();
};

