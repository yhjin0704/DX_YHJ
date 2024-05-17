#pragma once
#include "Melee.h"

// Ό³Έν :
class AWamy : public AMelee
{
	GENERATED_BODY(AMelee)

public:
	// constrcuter destructer
	AWamy();
	~AWamy();

	// delete Function
	AWamy(const AWamy& _Other) = delete;
	AWamy(AWamy&& _Other) noexcept = delete;
	AWamy& operator=(const AWamy& _Other) = delete;
	AWamy& operator=(AWamy&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckHit();

private:
	UCollision* Collision;

	AMonster* HitMonster;
	bool IsMonsterHit = false;
};

