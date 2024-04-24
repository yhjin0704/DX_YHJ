#pragma once
#include <EngineCore/Actor.h>
#include "Player.h"

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

	void SetPlayerStat(EPlayerDir _PlayerDir, float _Angle, float _Atk, float _CriRate, float _AtkTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	APlayer* Player;

	USpriteRenderer* Renderer;
	UCollision* Collision;

	EPlayerDir PlayerDir = EPlayerDir::E;
	float4 Dir = float4::Zero;
	float PlayerAngle;
	float Angle = 0.0f;
	float Atk;
	float CriRate;
	float AtkTime;
	float Delay = 1.0f;

	int Level;

	virtual void MoveAimDir();
	virtual void MouseAimDir();

private:
};

