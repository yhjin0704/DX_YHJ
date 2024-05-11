#pragma once
#include <EngineCore/Actor.h>

class APauseUI : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APauseUI();
	~APauseUI();

	// delete Function
	APauseUI(const APauseUI& _Other) = delete;
	APauseUI(APauseUI&& _Other) noexcept = delete;
	APauseUI& operator=(const APauseUI& _Other) = delete;
	APauseUI& operator=(APauseUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

