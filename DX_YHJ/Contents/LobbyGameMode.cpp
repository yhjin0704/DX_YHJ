#include "PreCompile.h"
#include "LobbyGameMode.h"
#include "LobbyBackGround.h"
#include <EngineCore/Camera.h>
#include <format>

ALobbyGameMode::ALobbyGameMode()
{
	InputOn();
}

ALobbyGameMode::~ALobbyGameMode()
{
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<ALobbyBackGround>("LobbyBackGround");
	Cursor = GetWorld()->SpawnActor<AHoloCursor>("Cursor");
	Logo = GetWorld()->SpawnActor<ALogo>("Logo");

	std::shared_ptr<ALobbyBackAnimationBar> InitBackBar = GetWorld()->SpawnActor<ALobbyBackAnimationBar>("Bar");
	LBar.push_back(InitBackBar);

	FVector BarPos = InitBackBar->GetActorLocation();
	for (int i = 1; i < 47; i++)
	{
		std::shared_ptr<ALobbyBackAnimationBar> SpawnBackBar = GetWorld()->SpawnActor<ALobbyBackAnimationBar>("Bar");
		SpawnBackBar->SetActorLocation({ BarPos.X - (38 * i), BarPos.Y });
		LBar.push_back(SpawnBackBar);
	}

	SpawnMainMenuButton();
}

void ALobbyGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SpawnBackBar(_DeltaTime);
	
	CheckMainButtonSelect();

	LobbyDebugText(_DeltaTime);
}

void ALobbyGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ALobbyGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ALobbyGameMode::SpawnBackBar(float _DeltaTime)
{
	if (0.1f <= DelaySpawnBar)
	{
		std::shared_ptr<ALobbyBackAnimationBar> Bar = GetWorld()->SpawnActor<ALobbyBackAnimationBar>("Bar");
		LBar.push_back(Bar);
		DelaySpawnBar = 0.0f;
	}
	DelaySpawnBar += _DeltaTime;
}

void ALobbyGameMode::SpawnMainMenuButton()
{
	for (int i = 0; i < 2; i++)
	{
		std::shared_ptr<AMainMenuButton> MainMenuButton = GetWorld()->SpawnActor<AMainMenuButton>("MainMenuButton");
		MainMenuButton->SetActorLocation({ 430.0f, 125.0f - (i * 60.0f) });
		VMainButton.push_back(MainMenuButton);
	}

	{
		VMainButton[0]->GetTextWidget()->SetPosition(VMainButton[0]->GetActorLocation());
		VMainButton[0]->GetTextWidget()->SetText("새 게임");
	}

	{
		VMainButton[1]->GetTextWidget()->SetPosition(VMainButton[1]->GetActorLocation());
		VMainButton[1]->GetTextWidget()->SetText("나가기");
	}
}

void ALobbyGameMode::CheckMainButtonSelect()
{
	if (true == IsDown('W'))
	{
		--ButtonSelect;
		if (0 > ButtonSelect)
		{
			ButtonSelect = VMainButton.size() - 1;
		}
	}
	else if (true == IsDown('S'))
	{
		++ButtonSelect;
		if (VMainButton.size() <= ButtonSelect)
		{
			ButtonSelect = 0;
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		if (true == VMainButton[i]->GetIsCursorOn())
		{
			ButtonSelect = i;
		}
		VMainButton[i]->SetIsSelect(false);
	}

	switch (ButtonSelect)
	{
	case 0:
		VMainButton[ButtonSelect]->SetIsSelect(true);
		if (true == IsDown(VK_RETURN))
		{
			GEngine->ChangeLevel("PlayLevel");
		}
		else if (true == VMainButton[ButtonSelect]->GetIsCursorOn())
		{
			if (true == IsDown(VK_LBUTTON))
			{
				GEngine->ChangeLevel("PlayLevel");
			}
		}
		break;
	case 1:
		VMainButton[ButtonSelect]->SetIsSelect(true);
		if (true == IsDown(VK_RETURN))
		{
			GEngine->EngineWindow.Off();
		}
		else if (true == VMainButton[ButtonSelect]->GetIsCursorOn())
		{
			if (true == IsDown(VK_LBUTTON))
			{
				GEngine->EngineWindow.Off();
			}
		}
		break;
	default:
		break;
	}
}

void ALobbyGameMode::LobbyDebugText(float _DeltaTime)
{
	UEngineDebugMsgWindow::PushMsg(std::format("Frame : {}\n", 1.0f / _DeltaTime));
}