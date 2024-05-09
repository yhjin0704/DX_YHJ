#include "PreCompile.h"
#include "LobbyGameMode.h"
#include <format>
#include <EngineCore/Camera.h>
#include "LobbyBackGround.h"
#include "PlayGameMode.h"
#include "ContentsValue.h"

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

	std::shared_ptr<ALobbyBackAnimationBar> InitBackBar = GetWorld()->SpawnActor<ALobbyBackAnimationBar>("Bar");
	LBar.push_back(InitBackBar);

	FVector BarPos = InitBackBar->GetActorLocation();
	for (int i = 1; i < 47; i++)
	{
		std::shared_ptr<ALobbyBackAnimationBar> SpawnBackBar = GetWorld()->SpawnActor<ALobbyBackAnimationBar>("Bar");
		SpawnBackBar->SetActorLocation({ BarPos.X - (38 * i), BarPos.Y });
		LBar.push_back(SpawnBackBar);
	}

	Logo = GetWorld()->SpawnActor<ALogo>("Logo");
	SpawnMainMenuButton();
	SpawnLobbyChar();

	CharSelectUI = GetWorld()->SpawnActor<ACharSelectUI>("CharSelectUI");
	CharSelectUI->AllActiveOff();


}

void ALobbyGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SpawnBackBar(_DeltaTime);

	CheckMainButtonSelect();

	if (true != IsMainLobby)
	{
		if (true == IsDown(VK_ESCAPE))
		{
			ReturnMainLobby();
		}
		else if (true == IsDown('P'))
		{
			GEngine->ChangeLevel("PlayLevel");
		}
	}

	LobbyDebugText(_DeltaTime);
}

void ALobbyGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	APlayGameMode::MainPlayer->SetName(SelectCharName);
}

void ALobbyGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ALobbyGameMode::StartCharSelect()
{
	if (true == IsMainLobby)
	{
		Logo->SetActive(false);
		for (VMainButtonIter = VMainButton.begin(); VMainButtonIter != VMainButton.end(); ++VMainButtonIter)
		{
			std::shared_ptr<AMainMenuButton> MainButton = *VMainButtonIter;
			MainButton->AllActiveOff();
		}
		for (VLobbyCharIter = VLobbyChar.begin(); VLobbyCharIter != VLobbyChar.end(); ++VLobbyCharIter)
		{
			std::shared_ptr<ALobbyChar> LobbyChar = *VLobbyCharIter;
			LobbyChar->SetActive(false);
		}

		CharSelectUI->AllActiveOn();

		IsMainLobby = false;
	}
}

void ALobbyGameMode::ReturnMainLobby()
{
	if (true != IsMainLobby)
	{
		Logo->SetActive(true);
		for (VMainButtonIter = VMainButton.begin(); VMainButtonIter != VMainButton.end(); ++VMainButtonIter)
		{
			std::shared_ptr<AMainMenuButton> MainButton = *VMainButtonIter;
			MainButton->AllActiveOn();
		}
		for (VLobbyCharIter = VLobbyChar.begin(); VLobbyCharIter != VLobbyChar.end(); ++VLobbyCharIter)
		{
			std::shared_ptr<ALobbyChar> LobbyChar = *VLobbyCharIter;
			LobbyChar->SetActive(true);
		}

		CharSelectUI->AllActiveOff();

		IsMainLobby = true;
	}
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
	if (true == IsMainLobby)
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
				StartCharSelect();
				//GEngine->ChangeLevel("PlayLevel");
			}
			else if (true == VMainButton[ButtonSelect]->GetIsCursorOn())
			{
				if (true == IsDown(VK_LBUTTON))
				{
					StartCharSelect();
					//GEngine->ChangeLevel("PlayLevel");
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
}

void ALobbyGameMode::SpawnLobbyChar()
{
	for (int i = 0; i < 38; i++)
	{
		std::shared_ptr<ALobbyChar> LobbyChar = GetWorld()->SpawnActor<ALobbyChar>("LobbyChar");
		VLobbyChar.push_back(LobbyChar);
	}

	VLobbyChar[0]->Setting("spr_Title_Ame.png", { -65.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize }, 19);
	VLobbyChar[1]->Setting("spr_Title_bae.png", { -115.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize }, 18);
	VLobbyChar[2]->Setting("spr_Title_Gura.png", { -30.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize }, 17);
	VLobbyChar[3]->Setting("spr_Title_Mumei.png", { -170.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize }, 16);
	VLobbyChar[4]->Setting("spr_Title_Ina.png", { 20.0f * ContentsValue::MultipleSize, -90.0f * ContentsValue::MultipleSize }, 16);
	VLobbyChar[5]->Setting("spr_Title_Fauna.png", { -215.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize }, 15);
	VLobbyChar[6]->Setting("spr_Title_Kiara.png", { 60.0f * ContentsValue::MultipleSize, -80.0f * ContentsValue::MultipleSize }, 15);
	VLobbyChar[7]->Setting("spr_Title_Kronii.png", { -275.0f * ContentsValue::MultipleSize, -70.0f * ContentsValue::MultipleSize }, 14);

	VLobbyChar[8]->Setting("spr_Title_Shion.png", { -100.0f * ContentsValue::MultipleSize, -60.0f * ContentsValue::MultipleSize }, 13);
	VLobbyChar[9]->Setting("spr_Title_Choco.png", { -135.0f * ContentsValue::MultipleSize, -55.0f * ContentsValue::MultipleSize }, 12);
	VLobbyChar[10]->Setting("spr_Title_Irys.png", { -185.0f * ContentsValue::MultipleSize, -55.0f * ContentsValue::MultipleSize }, 13);
	VLobbyChar[11]->Setting("spr_Title_Subaru.png", { -50.0f * ContentsValue::MultipleSize, -60.0f * ContentsValue::MultipleSize }, 12);
	VLobbyChar[12]->Setting("spr_Title_Ayame.png", { -10.0f * ContentsValue::MultipleSize, -45.0f * ContentsValue::MultipleSize }, 13);
	VLobbyChar[13]->Setting("spr_Title_Aqua.png", { 35.0f * ContentsValue::MultipleSize, -40.0f * ContentsValue::MultipleSize }, 12);
	VLobbyChar[14]->Setting("spr_Title_Calli.png", { 70.0f * ContentsValue::MultipleSize, -35.0f * ContentsValue::MultipleSize }, 13);
	VLobbyChar[15]->Setting("spr_Title_Sana.png", { -220.0f * ContentsValue::MultipleSize, -55.0f * ContentsValue::MultipleSize }, 12);
																						 
	VLobbyChar[16]->Setting("spr_Title_Matsuri.png", { -110.0f * ContentsValue::MultipleSize, -5.0f * ContentsValue::MultipleSize }, 11);
	VLobbyChar[17]->Setting("spr_Title_Fubuki.png", { -75.0f * ContentsValue::MultipleSize, -15.0f * ContentsValue::MultipleSize }, 10);
	VLobbyChar[18]->Setting("spr_Title_Mel.png", { -155.0f * ContentsValue::MultipleSize, -5.0f * ContentsValue::MultipleSize }, 10);
	VLobbyChar[19]->Setting("spr_Title_Mio.png", { -35.0f * ContentsValue::MultipleSize, -10.0f * ContentsValue::MultipleSize }, 11);
	VLobbyChar[20]->Setting("spr_Title_Haato.png", { -190.0f * ContentsValue::MultipleSize, 0.0f * ContentsValue::MultipleSize }, 9);
	VLobbyChar[21]->Setting("spr_Title_Okayu.png", { 10.0f * ContentsValue::MultipleSize, 0.0f * ContentsValue::MultipleSize }, 10);
	VLobbyChar[22]->Setting("spr_Title_Aki.png", { -245.0f * ContentsValue::MultipleSize, 5.0f * ContentsValue::MultipleSize }, 8);
	VLobbyChar[23]->Setting("spr_Title_Korone.png", { 50.0f * ContentsValue::MultipleSize, 5.0f * ContentsValue::MultipleSize }, 11);
																					 
	VLobbyChar[24]->Setting("spr_Title_Sora.png", { -100.0f * ContentsValue::MultipleSize, 35.0f * ContentsValue::MultipleSize }, 7);
	VLobbyChar[25]->Setting("spr_Title_Roboco.png", { -140.0f * ContentsValue::MultipleSize, 35.0f * ContentsValue::MultipleSize }, 6);
	VLobbyChar[26]->Setting("spr_Title_Suisei.png", { -50.0f * ContentsValue::MultipleSize, 35.0f * ContentsValue::MultipleSize }, 6);
	VLobbyChar[27]->Setting("spr_Title_Azki.png", { -180.0f * ContentsValue::MultipleSize, 35.0f * ContentsValue::MultipleSize }, 5);
	VLobbyChar[28]->Setting("spr_Title_Miko.png", { -5.0f * ContentsValue::MultipleSize, 40.0f * ContentsValue::MultipleSize }, 5);
																					 
	VLobbyChar[29]->Setting("spr_Title_Hosinoba.png", { -90.0f * ContentsValue::MultipleSize, 80.0f * ContentsValue::MultipleSize }, 0);
	VLobbyChar[30]->Setting("spr_Title_Eopiputin.png", { -130.0f * ContentsValue::MultipleSize, 80.0f * ContentsValue::MultipleSize }, 1);
	VLobbyChar[31]->Setting("spr_Title_Rice.png", { -50.0f * ContentsValue::MultipleSize, 80.0f * ContentsValue::MultipleSize }, 1);
	VLobbyChar[32]->Setting("spr_Title_Olri.png", { -170.0f * ContentsValue::MultipleSize, 80.0f * ContentsValue::MultipleSize }, 0);
	VLobbyChar[33]->Setting("spr_Title_Kanaeru.png", { -5.0f * ContentsValue::MultipleSize, 80.0f * ContentsValue::MultipleSize }, 2);
	VLobbyChar[34]->Setting("spr_Title_Laine.png", { -225.0f * ContentsValue::MultipleSize, 70.0f * ContentsValue::MultipleSize }, 1);
	VLobbyChar[35]->Setting("spr_Title_Cobalskia.png", { 30.0f * ContentsValue::MultipleSize, 60.0f * ContentsValue::MultipleSize }, 3);
	VLobbyChar[36]->Setting("spr_Title_Melpitsa.png", { -260.0f * ContentsValue::MultipleSize, 60.0f * ContentsValue::MultipleSize }, 0);
	VLobbyChar[37]->Setting("spr_Title_Zeta.png", { 75.0f * ContentsValue::MultipleSize, 50.0f * ContentsValue::MultipleSize }, 4);
}

void ALobbyGameMode::LobbyDebugText(float _DeltaTime)
{
	UEngineDebugMsgWindow::PushMsg(std::format("Frame : {}\n", 1.0f / _DeltaTime));
}