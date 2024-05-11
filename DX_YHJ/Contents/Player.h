#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "ContentsEnum.h"

class AWeapon;
class USpriteRenderer;
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	static float4 PlayerColPos;
	static float4 PlayerPos;

	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager State;

	void SetName(std::string _Name)
	{
		Name = _Name;
	}

	EPlayerDir GetPlayerDir()
	{
		return PlayerDir;
	}

	float GetAngle()
	{
		return Angle;
	}

	float GetHp()
	{
		return Hp;
	}

	float GetAtk()
	{
		return Atk;
	}

	float GetAtkTime()
	{
		return AtkTime;
	}

	float GetSpeed()
	{
		return Speed;
	}

	template<typename WeaponType>
	void AddWeapon(std::string _Name)
	{
		std::shared_ptr<AWeapon> Weapon = GetWorld()->SpawnActor<WeaponType>(_Name);
		VPlayerWeapons.push_back(Weapon);
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	USpriteRenderer* ShadowRenderer;
	UCollision* Collision;

	USpriteRenderer* AtkDir;
	std::shared_ptr<UCamera> Camera;

	float4 Color;
	float Angle;

	std::string Name = "Kronii";
	EPlayerDir PlayerDir = EPlayerDir::E;
	float MaxHp = 100.0f;
	float Hp = 100.0f;
	float Atk = 1;
	float CriRate = 0.05f;
	float Haste = 0.0f;
	float AtkTime = 1.0f;
	float Speed = 1.0f;
	float CalSpeed = ContentsValue::BaseSpeed * Speed;
	float LineSpeed = CalSpeed * 0.75f;
	float Exp = 0;

	std::vector<std::shared_ptr<AWeapon>> VPlayerWeapons;
	std::vector<std::shared_ptr<AWeapon>>::iterator VPlayerWeaponsIter = VPlayerWeapons.begin();

	float HitDelay = 0.0f;

	void CreatePlayerAnimation(std::string _Name);

	void CalStatus();

	void CheckMouseAimMode();
	void ChangeMoveAimAtkDir();
	void ChangeMouseAimAtkDir();

	void CheckHit(float _DeltaTime);

	//State
	void StateInit();

	void Die(float _DeltaTime);

	void Idle(float _DeltaTime);

	void RunStart();
	void Run(float _DeltaTime);

	void KeyMove(float _DeltaTime, float4 _Dir, float _Speed);
	void KeyLineMove(float _DeltaTime, float4 _Dir1, float4 _Dir2);
};