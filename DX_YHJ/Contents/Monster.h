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

	USpriteRenderer* GetSavedRenderer()
	{
		return SavedRenderer;
	}

	UCollision* GetCollosion()
	{
		return Collision;
	}

	UCollision* GetOverCheckCollision()
	{
		return OverCheckCollision;
	}

	float GetHp()
	{
		return Hp;
	}

	float GetAtk()
	{
		return Atk;
	}

	void SetHp(float _Hp)
	{
		Hp = _Hp;
	}

	void SetSpeed(float _Speed)
	{
		Speed = _Speed;
		CalSpeed = ContentsValue::BaseSpeed * Speed;
	}

	void SetMonsterStatus(float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _WillTimeOutDestroy, float _TimeOutDelay);

	FVector CreateGroupToPlayerDir();

	void SetToPlayerDir(FVector _ToPlayerDir)
	{
		ToPlayerDir = _ToPlayerDir;
	}

	void SetTimeOutDestoryDelay(float _TimeOutDestoryDelay)
	{
		TimeOutDestoryDelay = _TimeOutDestoryDelay;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* Root;

	USpriteRenderer* Renderer;
	USpriteRenderer* SavedRenderer;
	UCollision* Collision;
	UCollision* OverCheckCollision;

	FVector Dir = FVector::Zero;
	FVector ToPlayerDir;

	std::string Name = "Shrimp";
	float Hp = 8.0f;
	float Atk = 2.0f;
	float Speed = 0.35f;
	float CalSpeed = ContentsValue::BaseSpeed * Speed;
	float Exp = 6.0f;

	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	bool IsContectPlayer = false;

	bool IsSaved = false;
	EEngineDir SavedDir = EEngineDir::MAX;
	float RendererAlpha = 1.0f;

	bool WillTimeOutDestory = false;
	float TimeOutDestoryDelay = 20.0f;
	
	virtual void Move(float _DeltaTime, EMonsterMoveType _MoveType = EMonsterMoveType::Follow);

	void CheckPosComparePlayer();

	void CheckOverPlayer();

	void CheckSaved();
	void Saved(float _DeltaTime);

	void TimeOutDestory(float _DeltaTime);
private:

};