#include "PreCompile.h"
#include "LobbyGameMode.h"
#include <format>
#include <EngineCore/Camera.h>
#include "LobbyBackGround.h"
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
	SpawnLobbyChar();
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

void ALobbyGameMode::SpawnLobbyChar()
{
	for (int i = 0; i < 38; i++)
	{
		std::shared_ptr<ALobbyChar> LobbyChar = GetWorld()->SpawnActor<ALobbyChar>("LobbyChar");
		VLobbyChar.push_back(LobbyChar);
	}

	VLobbyChar[0]->Setting("spr_Title_Ame_19.png", { -65.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize });
	VLobbyChar[1]->Setting("spr_Title_bae_18.png", { -115.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize });
	VLobbyChar[2]->Setting("spr_Title_Gura_17.png", { -30.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize });
	VLobbyChar[3]->Setting("spr_Title_Mumei_16.png", { -170.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize });
	VLobbyChar[4]->Setting("spr_Title_Ina_16.png", { 20.0f * ContentsValue::MultipleSize, -90.0f * ContentsValue::MultipleSize });
	VLobbyChar[5]->Setting("spr_Title_Fauna_15.png", { -215.0f * ContentsValue::MultipleSize, -105.0f * ContentsValue::MultipleSize });
	VLobbyChar[6]->Setting("spr_Title_Kiara_15.png", { 60.0f * ContentsValue::MultipleSize, -80.0f * ContentsValue::MultipleSize });
	VLobbyChar[7]->Setting("spr_Title_Kronii_14.png", { -275.0f * ContentsValue::MultipleSize, -70.0f * ContentsValue::MultipleSize });

	VLobbyChar[8]->Setting("spr_Title_Shion_13.png", { -100.0f * ContentsValue::MultipleSize, -60.0f * ContentsValue::MultipleSize });
	VLobbyChar[9]->Setting("spr_Title_Choco_12.png", { -135.0f * ContentsValue::MultipleSize, -55.0f * ContentsValue::MultipleSize });
	VLobbyChar[10]->Setting("spr_Title_Irys_13.png", { -185.0f * ContentsValue::MultipleSize, -55.0f * ContentsValue::MultipleSize });
	VLobbyChar[11]->Setting("spr_Title_Subaru_12.png", { -50.0f * ContentsValue::MultipleSize, -60.0f * ContentsValue::MultipleSize });
	VLobbyChar[12]->Setting("spr_Title_Ayame_13.png", { -10.0f * ContentsValue::MultipleSize, -45.0f * ContentsValue::MultipleSize });
	VLobbyChar[13]->Setting("spr_Title_Aqua_12.png", { 35.0f * ContentsValue::MultipleSize, -40.0f * ContentsValue::MultipleSize });
	VLobbyChar[14]->Setting("spr_Title_Calli_13.png", { 70.0f * ContentsValue::MultipleSize, -35.0f * ContentsValue::MultipleSize });
	VLobbyChar[15]->Setting("spr_Title_Sana_12.png", { -220.0f * ContentsValue::MultipleSize, -55.0f * ContentsValue::MultipleSize });
																						 
	VLobbyChar[16]->Setting("spr_Title_Matsuri_11.png", { -110.0f * ContentsValue::MultipleSize, -5.0f * ContentsValue::MultipleSize });
	VLobbyChar[17]->Setting("spr_Title_Fubuki_10.png", { -75.0f * ContentsValue::MultipleSize, -15.0f * ContentsValue::MultipleSize });
	VLobbyChar[18]->Setting("spr_Title_Mel_10.png", { -155.0f * ContentsValue::MultipleSize, -5.0f * ContentsValue::MultipleSize });
	VLobbyChar[19]->Setting("spr_Title_Mio_11.png", { -35.0f * ContentsValue::MultipleSize, -10.0f * ContentsValue::MultipleSize });
	VLobbyChar[20]->Setting("spr_Title_Haato_9.png", { -190.0f * ContentsValue::MultipleSize, 0.0f * ContentsValue::MultipleSize });
	VLobbyChar[21]->Setting("spr_Title_Okayu_10.png", { 10.0f * ContentsValue::MultipleSize, 0.0f * ContentsValue::MultipleSize });
	VLobbyChar[22]->Setting("spr_Title_Aki_8.png", { -245.0f * ContentsValue::MultipleSize, 5.0f * ContentsValue::MultipleSize });
	VLobbyChar[23]->Setting("spr_Title_Korone_11.png", { 50.0f * ContentsValue::MultipleSize, 5.0f * ContentsValue::MultipleSize });
																					 
	VLobbyChar[24]->Setting("spr_Title_Sora_7.png", { -100.0f * ContentsValue::MultipleSize, 35.0f * ContentsValue::MultipleSize });
	VLobbyChar[25]->Setting("spr_Title_Roboco_6.png", { -140.0f * ContentsValue::MultipleSize, 35.0f * ContentsValue::MultipleSize });
	VLobbyChar[26]->Setting("spr_Title_Suisei_6.png", { -50.0f * ContentsValue::MultipleSize, 35.0f * ContentsValue::MultipleSize });
	VLobbyChar[27]->Setting("spr_Title_Azki_5.png", { -180.0f * ContentsValue::MultipleSize, 35.0f * ContentsValue::MultipleSize });
	VLobbyChar[28]->Setting("spr_Title_Miko_5.png", { -5.0f * ContentsValue::MultipleSize, 40.0f * ContentsValue::MultipleSize });
																					 
	VLobbyChar[29]->Setting("spr_Title_Hosinoba_0.png", { -100.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
	VLobbyChar[30]->Setting("spr_Title_Eopiputin_1.png", { -135.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
	VLobbyChar[31]->Setting("spr_Title_Rice_1.png", { -50.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
	VLobbyChar[32]->Setting("spr_Title_Olri_0.png", { -185.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
	VLobbyChar[33]->Setting("spr_Title_Kanaeru_2.png", { -10.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
	VLobbyChar[34]->Setting("spr_Title_Laine_1.png", { -220.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
	VLobbyChar[35]->Setting("spr_Title_Cobalskia_3.png", { 35.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
	VLobbyChar[36]->Setting("spr_Title_Melpitsa_0.png", { -275.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
	VLobbyChar[37]->Setting("spr_Title_Zeta_4.png", { 70.0f * ContentsValue::MultipleSize, 75.0f * ContentsValue::MultipleSize });
}

void ALobbyGameMode::LobbyDebugText(float _DeltaTime)
{
	UEngineDebugMsgWindow::PushMsg(std::format("Frame : {}\n", 1.0f / _DeltaTime));
}