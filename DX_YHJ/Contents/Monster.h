#pragma once
#include <EngineCore/Actor.h>
#include "ContentsEnum.h"

class USpriteRenderer;
class AMonster : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void SetName(std::string _Name)
	{
		Name = _Name;
	}

	USpriteRenderer* GetRenderer()
	{
		return Renderer;
	}

	void SetMonsterStatus(float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType);

	FVector CreateGroupToPlayerDir();

	void SetToPlayerDir(FVector _ToPlayerDir)
	{
		ToPlayerDir = _ToPlayerDir;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	FVector PlayerLocation;
	FVector Dir = FVector::Zero;
	FVector ToPlayerDir;

	std::string Name = "Shrimp";
	float Hp = 8.0f;
	float Atk = 2.0f;
	float Speed = 0.35f;
	float CalSpeed = 300.0f * Speed;
	float Exp = 6.0f;

	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	void CreateMonsterAnimation(std::string _Name);

	void Move(float _DeltaTime, EMonsterMoveType _MoveType);
	void CheckPosComparePlayer();
};

