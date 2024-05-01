#pragma once
#include "Monster.h"

class AFubuzilla : public AMonster
{
	GENERATED_BODY(AMonster)

public:
	// constrcuter destructer
	AFubuzilla();
	~AFubuzilla();

	// delete Function
	AFubuzilla(const AFubuzilla& _Other) = delete;
	AFubuzilla(AFubuzilla&& _Other) noexcept = delete;
	AFubuzilla& operator=(const AFubuzilla& _Other) = delete;
	AFubuzilla& operator=(AFubuzilla&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Move(float _DeltaTime);
};

