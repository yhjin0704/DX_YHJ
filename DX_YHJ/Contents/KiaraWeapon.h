#pragma once
#include "Melee.h"

class AKiaraWeapon : public AMelee
{
	GENERATED_BODY(AMelee)

public:
	// constrcuter destructer
	AKiaraWeapon();
	~AKiaraWeapon();

	// delete Function
	AKiaraWeapon(const AKiaraWeapon& _Other) = delete;
	AKiaraWeapon(AKiaraWeapon&& _Other) noexcept = delete;
	AKiaraWeapon& operator=(const AKiaraWeapon& _Other) = delete;
	AKiaraWeapon& operator=(AKiaraWeapon&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckHit();

private:
	UCollision* CollisionR0;
	UCollision* CollisionR1;
	UCollision* CollisionC0;

	AMonster* HitMonster;
	bool IsMonsterHit = false;
};

