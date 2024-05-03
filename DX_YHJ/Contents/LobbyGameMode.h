#pragma once
#include <EngineCore/GameMode.h>
#include "HoloCursor.h"
#include "LobbyBackAnimationBar.h"

// Ό³Έν :
class ALobbyGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ALobbyGameMode();
	~ALobbyGameMode();

	// delete Function
	ALobbyGameMode(const ALobbyGameMode& _Other) = delete;
	ALobbyGameMode(ALobbyGameMode&& _Other) noexcept = delete;
	ALobbyGameMode& operator=(const ALobbyGameMode& _Other) = delete;
	ALobbyGameMode& operator=(ALobbyGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);


private:
	std::shared_ptr<AHoloCursor> Cursor;

	std::list<std::shared_ptr<ALobbyBackAnimationBar>> LBar;

	float DelaySpawnBar = 0.0f;

	void SpawnBackBar(float _DeltaTime);
};

