#include "PreCompile.h"
#include "TitleBackGround.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

ATitleBackGround::ATitleBackGround()
{
	FadeRenderer = CreateDefaultSubObject<USpriteRenderer>("FadeRenderer");

	InputOn();
}

ATitleBackGround::~ATitleBackGround()
{
}

void ATitleBackGround::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(ContentsValue::WindowSize.X, ContentsValue::WindowSize.Y));

	Renderer->SetSprite("Title_0.png");
	Renderer->SetAutoSize(1.0f, true);

	FadeRenderer->SetSprite("TiltleBlack.png");
	FadeRenderer->SetAutoSize(1.0f, true);
	FadeRenderer->SetMulColor({1.0f, 1.0f, 1.0f, 0.0f});
}

void ATitleBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	switch (Sequence)
	{
	case 0:
		CheckTitleTime += _DeltaTime;
		if (1.0f < CheckTitleTime)
		{
			FadeOut(_DeltaTime);
			if (false == IsFadeOut)
			{
				++Sequence;
			}
		}
		//if (true == IsDown(' '))
		//{
		//	FadeSequence = 0;
		//	FadeRenderer->SetMulColor(FVector::One);
		//	Sequence = 2;
		//}
		break;
	case 1:
		TitleChange(_DeltaTime, "Title_1.png");
		if (true == IsAnykeyDown())
		{
			FadeSequence = 0;
			FadeRenderer->SetMulColor(FVector::One);
			Sequence = 2;
		}
		break;
	case 2:
		TitleChange(_DeltaTime, "Title_2.png");
		if (true == IsAnykeyDown())
		{
			GEngine->ChangeLevel("LobbyLevel");
		}
		break;
	case 3:
		TitleChange(_DeltaTime, "Title_3.png");
		if (true == IsAnykeyDown())
		{
			GEngine->ChangeLevel("LobbyLevel");
		}
		break;
	case 4:
		TitleChange(_DeltaTime, "Title_4.png");
		if (true == IsAnykeyDown())
		{
			GEngine->ChangeLevel("LobbyLevel");
		}
		break;
	case 5:
		TitleChange(_DeltaTime, "Title_5.png");
		if (true == IsAnykeyDown())
		{
			GEngine->ChangeLevel("LobbyLevel");
		}
		break;
	case 6:
		TitleChange(_DeltaTime, "Title_6.png");
		if (true == IsAnykeyDown())
		{
			GEngine->ChangeLevel("LobbyLevel");
		}
		break;
	case 7:
		TitleChange(_DeltaTime, "Title_7.png");
		if (true == IsAnykeyDown())
		{
			GEngine->ChangeLevel("LobbyLevel");
		}
		break;
	case 8:
		GEngine->ChangeLevel("LobbyLevel");
		break;
	default:
		break;
	}
}

void ATitleBackGround::TitleChange(float _DeltaTime, std::string _SpriteName, float _Time)
{
	switch (FadeSequence)
	{
	case 0:
		Renderer->SetSprite(_SpriteName);
		++FadeSequence;
		break;
	case 1:
		FadeIn(_DeltaTime);
		if (false == IsFadeIn)
		{
			CheckTitleTime = 0.0f;
			++FadeSequence;
		}
		break;
	case 2:
		CheckTitleTime += _DeltaTime;
		if (_Time < CheckTitleTime)
		{
			++FadeSequence;
		}
		break;
	case 3:
		FadeOut(_DeltaTime);
		if (false == IsFadeOut)
		{
			FadeSequence = 0;
			++Sequence;
		}
		break;
	default:
		break;
	}
}

void ATitleBackGround::FadeIn(float _DeltaTime)
{
	
	if (0.0f <= FadeAlpha)
	{
		IsFadeIn = true;
		FadeAlpha -= _DeltaTime;
		FadeRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, FadeAlpha });
	}
	else
	{
		IsFadeIn = false;
	}
}

void ATitleBackGround::FadeOut(float _DeltaTime)
{
	if (1.0f >= FadeAlpha)
	{
		IsFadeOut = true;
		FadeAlpha += _DeltaTime;
		FadeRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, FadeAlpha });
	}
	else
	{
		IsFadeOut = false;
	}
}
