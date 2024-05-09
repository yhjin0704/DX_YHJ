#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/TextWidget.h>

class ACharSelectUI : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ACharSelectUI();
	~ACharSelectUI();

	// delete Function
	ACharSelectUI(const ACharSelectUI& _Other) = delete;
	ACharSelectUI(ACharSelectUI&& _Other) noexcept = delete;
	ACharSelectUI& operator=(const ACharSelectUI& _Other) = delete;
	ACharSelectUI& operator=(ACharSelectUI&& _Other) noexcept = delete;

	void SetSelectCharName(std::string _SelectCharName)
	{
		SelectCharName = _SelectCharName;
	}

	void AllActiveOff()
	{
		SelectTextBox->SetActive(false);
		SelectText->SetActive(false);
		BackCharL->SetActive(false);
		BackCharR->SetActive(false);
		ExplanationBox0->SetActive(false);
		ExplanationBox1->SetActive(false);
		ExplanationBox2->SetActive(false);
		ExplanationFrame->SetActive(false);
		CharAnimation->SetActive(false);
	}

	void AllActiveOn()
	{
		SelectTextBox->SetActive(true);
		SelectText->SetActive(true);
		BackCharL->SetActive(true);
		BackCharR->SetActive(true);
		ExplanationBox0->SetActive(true);
		ExplanationBox1->SetActive(true);
		ExplanationBox2->SetActive(true);
		ExplanationFrame->SetActive(true);
		CharAnimation->SetActive(true);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string SelectCharName = "Kiara";

	USpriteRenderer* SelectTextBox;
	UTextWidget* SelectText;

	USpriteRenderer* BackCharL;
	USpriteRenderer* BackCharR;

	USpriteRenderer* ExplanationBox0;
	USpriteRenderer* ExplanationBox1;
	USpriteRenderer* ExplanationBox2;

	USpriteRenderer* ExplanationFrame;

	USpriteRenderer* CharAnimation;
	int Count = 0;

	void CreateCharAnimation(std::string _Name);
	void ChangeSelectCharAnimation();
};

