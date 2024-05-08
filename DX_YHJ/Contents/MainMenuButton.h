#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/TextWidget.h>

class USpriteRenderer;
class AMainMenuButton : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AMainMenuButton();
	~AMainMenuButton();

	// delete Function
	AMainMenuButton(const AMainMenuButton& _Other) = delete;
	AMainMenuButton(AMainMenuButton&& _Other) noexcept = delete;
	AMainMenuButton& operator=(const AMainMenuButton& _Other) = delete;
	AMainMenuButton& operator=(AMainMenuButton&& _Other) noexcept = delete;

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	UCollision* Collision;
	UTextWidget* Text;

	bool IsCursorOn = false;
	bool IsSelect = false;

	void CollisionCheck();

	void SelectChange();
};

