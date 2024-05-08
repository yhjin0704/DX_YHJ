#pragma once
#include <EngineCore/Actor.h>

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	UCollision* Collision;

	bool IsCursorOn = false;

	void CollisionCheck();

	void SelectChange();
};

