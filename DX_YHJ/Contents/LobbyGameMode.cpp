#include "PreCompile.h"
#include "LobbyGameMode.h"
#include "LobbyBackGround.h"
#include <EngineCore/Camera.h>

ALobbyGameMode::ALobbyGameMode()
{
	InputOn();
}

ALobbyGameMode::~ALobbyGameMode()
{
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<ALobbyBackGround>("LobbyBackGround");

	Cursor = GetWorld()->SpawnActor<AHoloCursor>("Cursor");

	std::shared_ptr<ALobbyBackAnimationBar> InitialBackBar = GetWorld()->SpawnActor<ALobbyBackAnimationBar>("Bar");
	LBar.push_back(InitialBackBar);
}

void ALobbyGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsAnykeyDown())
	{
		GEngine->ChangeLevel("PlayLevel");
	}
}

void ALobbyGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ALobbyGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ALobbyGameMode::SpawnBackBar(float _DeltaTime)
{
	if (0.1f <= DelaySpawnBar)
	{
		std::shared_ptr<ALobbyBackAnimationBar> Bar = GetWorld()->SpawnActor<ALobbyBackAnimationBar>("Bar");
		LBar.push_back(Bar);
		DelaySpawnBar = 0.0f;
	}
	DelaySpawnBar += _DeltaTime;
}
