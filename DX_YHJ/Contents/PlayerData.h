#pragma once
#include <EngineCore/Actor.h>

class APlayerData : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayerData();
	~APlayerData();

	// delete Function
	APlayerData(const APlayerData& _Other) = delete;
	APlayerData(APlayerData&& _Other) noexcept = delete;
	APlayerData& operator=(const APlayerData& _Other) = delete;
	APlayerData& operator=(APlayerData&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};
