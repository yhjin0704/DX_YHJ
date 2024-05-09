#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ACharSelectButton : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ACharSelectButton();
	~ACharSelectButton();

	// delete Function
	ACharSelectButton(const ACharSelectButton& _Other) = delete;
	ACharSelectButton(ACharSelectButton&& _Other) noexcept = delete;
	ACharSelectButton& operator=(const ACharSelectButton& _Other) = delete;
	ACharSelectButton& operator=(ACharSelectButton&& _Other) noexcept = delete;

	void AllActiveOff()
	{
		Renderer->SetActive(false);
		SelectWhite->SetActive(false);
		Collision->SetActive(false);
	}

	void AllActiveOn()
	{
		Renderer->SetActive(true);
		Collision->SetActive(true);
	}

	void SetName(std::string _Name)
	{
		Name = _Name;
	}

	void Setting(std::string _Name);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	USpriteRenderer* SelectWhite;
	UCollision* Collision;

	std::string Name = "";

	bool IsCursorOn = false;
	bool IsSelect = false;
};

