#pragma once
#include "Weapon.h"

class ARanged : public AWeapon
{
	GENERATED_BODY(AWeapon)

public:
	// constrcuter destructer
	ARanged();
	~ARanged();

	// delete Function
	ARanged(const ARanged& _Other) = delete;
	ARanged(ARanged&& _Other) noexcept = delete;
	ARanged& operator=(const ARanged& _Other) = delete;
	ARanged& operator=(ARanged&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	bool IsMultiShot = false;

	void CreateBullet();

private:

};

