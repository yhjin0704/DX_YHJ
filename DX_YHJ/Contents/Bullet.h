#pragma once
#include "Weapon.h"

class ABullet : public AWeapon
{
	GENERATED_BODY(AWeapon)

public:
	// constrcuter destructer
	ABullet();
	~ABullet();

	// delete Function
	ABullet(const ABullet& _Other) = delete;
	ABullet(ABullet&& _Other) noexcept = delete;
	ABullet& operator=(const ABullet& _Other) = delete;
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	
};

