#pragma once
#include <EngineCore/Actor.h>

class AExpObject : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AExpObject();
	~AExpObject();

	// delete Function
	AExpObject(const AExpObject& _Other) = delete;
	AExpObject(AExpObject&& _Other) noexcept = delete;
	AExpObject& operator=(const AExpObject& _Other) = delete;
	AExpObject& operator=(AExpObject&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
};

