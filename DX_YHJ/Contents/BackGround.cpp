#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ABackGround::ABackGround()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ABackGround::~ABackGround()
{
}

void ABackGround::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->SetOrder(ERenderOrder::BackGround);
}

void ABackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
