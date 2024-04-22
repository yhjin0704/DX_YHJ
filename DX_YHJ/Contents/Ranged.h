#pragma once
#include "Weapon.h"

class ARanged : public AWeapon
{
	GENERATED_BODY(AActor)

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
	bool IsMultiShot = false;

private:

};

