#pragma once
#include "Weapon.h"

class AMelee : public AWeapon
{
	GENERATED_BODY(AWeapon)

public:
	// constrcuter destructer
	AMelee();
	~AMelee();

	// delete Function
	AMelee(const AMelee& _Other) = delete;
	AMelee(AMelee&& _Other) noexcept = delete;
	AMelee& operator=(const AMelee& _Other) = delete;
	AMelee& operator=(AMelee&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetKnifeTypeMeleeLocation(float _DistanceFromPlayer);

private:

};

