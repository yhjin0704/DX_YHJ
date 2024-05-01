#pragma once
#include <EngineCore/Actor.h>
#include "Player.h"
#include "PlayGameMode.h"

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

	std::string GetName()
	{
		return Name;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* Root;

	USpriteRenderer* Renderer;

	std::string Name = "";

	EPlayerDir PlayerDir = EPlayerDir::E;
	float4 Dir = float4::Zero;
	float PlayerAngle;
	float Angle = 0.0f;
	float Atk = 18.0f;
	float CriRate;
	float AtkTime;
	float Delay = 1.0f;

	int Level;

	//virtual void CheckHit();

private:
};

