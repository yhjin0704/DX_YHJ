#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "ContentsEnum.h"

class USpriteRenderer;
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	USpriteRenderer* AtkDir;
	std::shared_ptr<UCamera> Camera;

	float4 Color;
	float Angle;

	std::string Name = "Kronii";
	EPlayerDir PlayerDir = EPlayerDir::E;
	int Hp = 100;
	float Atk = 1;
	float Speed = 200.0f;
	float LineSpeed = Speed * 0.75f;

	void CreatePlayerAnimation(std::string _Name);

	void CheckMouseAimMode();
	void ChangeMoveAimAtkDir();
	void ChangeMouseAimAtkDir();

	//State
	void StateInit();

	void Die(float _DeltaTime);

	void Idle(float _DeltaTime);

	void RunStart();
	void Run(float _DeltaTime);

	void KeyMove(float _DeltaTime, float4 _Dir, float _Speed);
	void KeyLineMove(float _DeltaTime, float4 _Dir1, float4 _Dir2);
};