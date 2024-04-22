#pragma once
#include <EngineCore/Actor.h>
#include "ContentsEnum.h"
#include "ContentsValue.h"

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

	UCollision* GetCollosion()
	{
		return Collision;
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
	UCollision* Collision;

	FVector Dir = FVector::Zero;
	FVector ToPlayerDir;

	std::string Name = "Shrimp";
	float Hp = 8.0f;
	float Atk = 2.0f;
	float Speed = 0.35f;
	float CalSpeed = ContentsValue::BaseSpeed * Speed;
	float Exp = 6.0f;

	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	void CreateMonsterAnimation(std::string _Name, int _MaxIndex = 2);

	void Move(float _DeltaTime, EMonsterMoveType _MoveType);
	void CheckPosComparePlayer();
};