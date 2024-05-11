#pragma once
#include <EngineCore/Actor.h>

class AShopUI : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AShopUI();
	~AShopUI();

	// delete Function
	AShopUI(const AShopUI& _Other) = delete;
	AShopUI(AShopUI&& _Other) noexcept = delete;
	AShopUI& operator=(const AShopUI& _Other) = delete;
	AShopUI& operator=(AShopUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

