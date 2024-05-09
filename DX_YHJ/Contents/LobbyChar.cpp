#include "PreCompile.h"
#include "LobbyChar.h"
#include <EngineBase/EngineRandom.h>
#include "ContentsValue.h"

ALobbyChar::ALobbyChar()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	MoveMaxTime = UEngineRandom::MainRandom.RandomFloat(1.2f, 1.8f);

	SetRoot(Root);
}

ALobbyChar::~ALobbyChar()
{
}

void ALobbyChar::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyChar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Move(_DeltaTime);
}

void ALobbyChar::Setting(std::string _Image, FVector _Pos, int _RenderOrder)
{
	/*std::string Separator = "_";
	std::string PngSeparator = ".";

	int cur_position = 10;
	int position = _Image.find(Separator, cur_position);
	cur_position = position + 1;
	int len = position - cur_position;
	
	std::string Result = _Image.substr(cur_position, len);

	cur_position = 0;
	position = Result.find(PngSeparator, cur_position);
	len = position - cur_position;
	
	Result = Result.substr(cur_position, len);
	
	int Order = std::stoi(Result) + 2;*/

	Renderer->SetSprite(_Image);
	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->SetPosition(_Pos);
	Renderer->SetOrder(_RenderOrder + 2);
}

void ALobbyChar::Move(float _DeltaTime)
{
	if (0.0f <= MoveTime && MoveTime < MoveMaxTime)
	{
		UpSpeed -= _DeltaTime * 2.0f;
		Renderer->AddPosition(MoveDir * UpSpeed * _DeltaTime);
		DownSpeed = 3.0f;
	}
	else if (MoveMaxTime <= MoveTime && MoveTime < (MoveMaxTime * 2.0f))
	{
		DownSpeed -= _DeltaTime * 2.0f;
		Renderer->AddPosition(MoveDir * -1 * DownSpeed * _DeltaTime);
		UpSpeed = 3.0f;
	}
	else
	{
		MoveTime = 0.0f;
	}

	MoveTime += _DeltaTime;
}