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

	Renderer->SetSprite("Holo_Stage_1_Back_Ground.png");

}

void APlayBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
