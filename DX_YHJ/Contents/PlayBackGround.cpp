#include "PreCompile.h"
#include "PlayBackGround.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

APlayBackGround::APlayBackGround()
{
}

APlayBackGround::~APlayBackGround()
{
}

void APlayBackGround::BeginPlay()
{
	Super::BeginPlay();

	// 내부에서 샘플러도 같이 찾을
	Renderer->SetSprite("Holo_Stage_1_Back_Ground.png");

}

void APlayBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
