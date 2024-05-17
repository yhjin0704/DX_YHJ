#include "PreCompile.h"
#include "ExpObject.h"
#include "PlayGameMode.h"

AExpObject::AExpObject()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	SetRoot(Root);
}


AExpObject::~AExpObject()
{
}

void AExpObject::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("spr_EXP_0.png");
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
}

void AExpObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Renderer->SetOrder(500 - static_cast<int>(GetActorLocation().Y - APlayGameMode::MainPlayer->GetActorLocation().Y));
}