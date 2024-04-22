#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class AWeapon : public AActor
{
	GENERATED_BODY(AActor)

public:
	friend class APlayer;

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

	float4 Dir = float4::Zero;

	int Level;

	virtual void MoveAimDir();
	virtual void MouseAimDir();

private:
};

