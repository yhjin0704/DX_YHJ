#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class ABackGround : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ABackGround();
	~ABackGround();

	// delete Function
	ABackGround(const ABackGround& _Other) = delete;
	ABackGround(ABackGround&& _Other) noexcept = delete;
	ABackGround& operator=(const ABackGround& _Other) = delete;
	ABackGround& operator=(ABackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* Renderer;

	float4 Color;

private:
};

