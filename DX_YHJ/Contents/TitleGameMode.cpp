#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include <EngineCore/Camera.h>

ATitleGameMode::ATitleGameMode()
{
	InputOn();
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<ATitleLogo>("TitleLogo");
	GetWorld()->SpawnActor<ATitleBackGround>("TitleBackGround");

	Cursor = GetWorld()->SpawnActor<AHoloCursor>("Cursor");
	AHoloCursor::CursorPos = GEngine->EngineWindow.GetScreenMousePos();
	Cursor->SetActorLocation(FVector{ AHoloCursor::CursorPos.X - 1280.0f, AHoloCursor::CursorPos.Y - 360.0f });
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AHoloCursor::CursorPos = GEngine->EngineWindow.GetScreenMousePos();
	AHoloCursor::MouseAimOn = false;
	Cursor->SetActorLocation(FVector{ AHoloCursor::CursorPos.X - 640.0f, (AHoloCursor::CursorPos.Y - 360.0f) * -1.0f });

	if (true == IsAnykeyDown())
	{
		GEngine->ChangeLevel("PlayLevel");
	}
}

void ATitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}