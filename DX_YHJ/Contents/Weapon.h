#pragma once
#include <EngineCore/Actor.h>
#include "Player.h"

class USpriteRenderer;
class AWeapon : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AWeapon();
	~AWeapon();

	// delete Function
	AWeapon(const AWeapon& _Other) = delete;
	AWeapon(AWeapon&& _Other) noexcept = delete;
	AWeapon& operator=(const AWeapon& _Other) = delete;
	AWeapon& operator=(AWeapon&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* Renderer;
	UCollision* Collision;

	int Level;

	virtual void MoveAimDir();
	virtual void MouseAimDir();

private:
};

