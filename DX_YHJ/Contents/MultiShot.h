#pragma once
#include "Weapon.h"

class AMultiShot : public AWeapon
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AMultiShot();
	~AMultiShot();

	// delete Function
	AMultiShot(const AMultiShot& _Other) = delete;
	AMultiShot(AMultiShot&& _Other) noexcept = delete;
	AMultiShot& operator=(const AMultiShot& _Other) = delete;
	AMultiShot& operator=(AMultiShot&& _Other) noexcept = delete;

protected:

private:

};

