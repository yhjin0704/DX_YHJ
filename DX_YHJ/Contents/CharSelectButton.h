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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	USpriteRenderer* SelectWhite;
	UCollision* Collision;

	bool IsSelect = false;
};

