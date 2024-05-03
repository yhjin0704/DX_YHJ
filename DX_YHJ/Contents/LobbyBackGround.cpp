#include "PreCompile.h"
#include "LobbyBackGround.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

ALobbyBackGround::ALobbyBackGround()
{
}

ALobbyBackGround::~ALobbyBackGround()
{
}

void ALobbyBackGround::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(ContentsValue::WindowSize.X, ContentsValue::WindowSize.Y, 100.0f));

	Renderer->SetSprite("menu_charselecBG_0.png");
}

void ALobbyBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}