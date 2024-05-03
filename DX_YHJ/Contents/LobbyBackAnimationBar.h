#pragma once
#include <Enginecore/Actor.h>

class USpriteRenderer;
class ALobbyBackAnimationBar : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALobbyBackAnimationBar();
	~ALobbyBackAnimationBar();

	// delete Function
	ALobbyBackAnimationBar(const ALobbyBackAnimationBar& _Other) = delete;
	ALobbyBackAnimationBar(ALobbyBackAnimationBar&& _Other) noexcept = delete;
	ALobbyBackAnimationBar& operator=(const ALobbyBackAnimationBar& _Other) = delete;
	ALobbyBackAnimationBar& operator=(ALobbyBackAnimationBar&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Move(float _DeltaTime);

private:
	USpriteRenderer* Renderer;

	float Speed = 0.5f;
};

