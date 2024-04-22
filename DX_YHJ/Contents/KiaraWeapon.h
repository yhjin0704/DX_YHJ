#pragma once
#include "Melee.h"

class AKiaraWeapon : public AMelee
{
	GENERATED_BODY(AActor)

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

	void MoveAimDir() override;
	void MouseAimDir() override;

private:

};

