#pragma once
#include <EngineCore/GameMode.h>
#include "HoloCursor.h"
#include "Player.h"
#include "NomalMonster.h"
#include "PlayBackGround.h"

struct FIntPoint
{
	union
	{
		struct
		{
			int X;
			int Y;
		};

		__int64 Key;
	};
};

class APlayGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	static std::shared_ptr<APlayer> MainPlayer;

	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	std::shared_ptr<APlayer> GetMainPlayer();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

	std::vector<std::shared_ptr<APlayBackGround>> BackGroundVector;

	std::shared_ptr<AHoloCursor> Cursor;
	std::shared_ptr<APlayer> Player;

	float4 IndexToCenterPos(FIntPoint _Index);
	FIntPoint PosToIndex(float4 _Pos);

	void InfinityGroundCheck();

	// 몬스터 스폰 관련
	std::shared_ptr<ANomalMonster> SpawnNomalMonster(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType = EMonsterMoveType::Follow);

	template<typename BossType>
	std::shared_ptr<BossType> SpawnBossMonster(std::string _Name);

	float4 RandomLocation(bool _Group);
	void RandomSpawnNomalMonster(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group, int _Quantity);

	void SpawnNomalMonsterTimeSet(float _DeltaTime, float _SpawnBegin, float _SpawnEnd, float _Term, float& _SpawnTerm, std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group = false, int _Quantity = 1);
	
	template<typename BossType>
	void SpawnBossMonsterTimeSet(float _SpawnBegin, std::string _Name);

	void PlayDebugText();

private:
	FIntPoint CurIndex;

	float4 GroupMonsterPos;
	bool GroupSpawn = false;

	float PlayTime = 0;

	float SpawnTerm1 = 0;
	float SpawnTerm2 = 0;
	float SpawnTerm3 = 0;
	float SpawnTerm4 = 0;
	float SpawnTerm5 = 0;

};

