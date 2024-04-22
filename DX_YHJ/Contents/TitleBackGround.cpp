#include "PreCompile.h"
#include "TitleBackGround.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

ATitleBackGround::ATitleBackGround()
{
}

ATitleBackGround::~ATitleBackGround()
{
}

void ATitleBackGround::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(ContentsValue::WindowSize.X, ContentsValue::WindowSize.Y, 100.0f));

	Renderer->SetSprite("menu_charselecBG_0.png");
}

void ATitleBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}