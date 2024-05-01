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

	float GetHp()
	{
		return Hp;
	}

	void SetHp(float _Hp)
	{
		Hp = _Hp;
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

	UDefaultSceneComponent* Root;

	USpriteRenderer* Renderer;
	USpriteRenderer* SavedRenderer;
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

	bool IsSaved = false;
	EEngineDir SavedDir = EEngineDir::MAX;
	float RendererAlpha = 1.0f;
	
	void CheckPosComparePlayer();

	virtual void CheckHit();

	virtual void CheakSaved();
	virtual void Saved(float _DeltaTime);
private:

};