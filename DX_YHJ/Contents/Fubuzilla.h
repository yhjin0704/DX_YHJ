#pragma once
#include "Monster.h"

enum class ELaser
{
	Stay,
	Ready,
	Shot,
};

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
	USpriteRenderer* LaserRenderer;
	UCollision* LaserCollision;

	ELaser Laser = ELaser::Stay;
	bool IsUseLaser = false;

	void UseLaserCheck();
	void UseLaser(EEngineDir _Dir);
};

