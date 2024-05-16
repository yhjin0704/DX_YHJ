#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/TextWidget.h>

class APauseButton : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APauseButton();
	~APauseButton();

	// delete Function
	APauseButton(const APauseButton& _Other) = delete;
	APauseButton(APauseButton&& _Other) noexcept = delete;
	APauseButton& operator=(const APauseButton& _Other) = delete;
	APauseButton& operator=(APauseButton&& _Other) noexcept = delete;

	void AllActiveOff()
	{
		Renderer->SetActive(false);
		Collision->SetActive(false);
		Text->SetActive(false);
	}

	void AllActiveOn()
	{
		Renderer->SetActive(true);
		Collision->SetActive(true);
		Text->SetActive(true);
	}

	UImage* GetUImage()
	{
		return Renderer;
	}

	UTextWidget* GetTextWidget()
	{
		return Text;
	}

	bool GetIsCursorOn()
	{
		return IsCursorOn;
	}

	void SetIsCursorOn(bool _IsCursorOn)
	{
		IsCursorOn = _IsCursorOn;
	}

	void SetIsSelect(bool _IsSelect)
	{
		IsSelect = _IsSelect;
	}

	void SettingLocation()
	{
		Renderer->SetPosition(GetActorLocation());
		Text->SetPosition(GetActorLocation());
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* Renderer;
	UCollision* Collision;
	UTextWidget* Text;

	bool IsCursorOn = false;
	bool IsSelect = false;

	void CollisionCheck();

	void SelectChange();
};