#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ALogo : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALogo();
	~ALogo();

	// delete Function
	ALogo(const ALogo& _Other) = delete;
	ALogo(ALogo&& _Other) noexcept = delete;
	ALogo& operator=(const ALogo& _Other) = delete;
	ALogo& operator=(ALogo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;

	float LogoMoveTime = 0;
	float4 LogoMoveDir = FVector::Down * 10.0f;
	float UpSpeed = 1.0f;
	float DownSpeed = 1.0f;

	void Move(float _DeltaTime);
};

