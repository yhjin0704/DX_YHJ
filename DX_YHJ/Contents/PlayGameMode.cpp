#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "PlayBackGround.h"
#include <EngineCore/Camera.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	float4 MapScale = UEngineTexture::FindRes("Holo_Stage_1_Back_Ground.png")->GetScale();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(2560.f / 2.0f, -2560.f / 2.0f, -500.0f));

	{
		std::shared_ptr<APlayer> Actor = GetWorld()->SpawnActor<APlayer>("Player");

		float4 ImageScale = {64.0f, 64.0f, 0.0f};

		Actor->SetActorScale3D(ImageScale);
		Actor->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 1000.0f });
	}

	{
		std::shared_ptr<APlayBackGround> BackGround = GetWorld()->SpawnActor<APlayBackGround>("PlayBackGround");

		float4 ImageScale = MapScale;

		BackGround->SetActorScale3D(ImageScale);
		BackGround->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}