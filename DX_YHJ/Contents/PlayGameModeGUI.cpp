#include "PreCompile.h"
#include "PlayGameModeGUI.h"
#include "PlayGameMode.h"
#include "Asacoco.h"
#include "Wamy.h"
#include "Spider.h"
#include "Fanbeam.h"

PlayGameModeGUI::PlayGameModeGUI()
{
}

PlayGameModeGUI::~PlayGameModeGUI()
{
}

void PlayGameModeGUI::Init()
{
	Super::Init();
}

void PlayGameModeGUI::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("Asacoco"))
	{
		APlayGameMode::MainPlayer->AddWeapon<AAsacoco>("Asacoco");
	}
	if (true == ImGui::Button("Wamy"))
	{
		APlayGameMode::MainPlayer->AddWeapon<AWamy>("Wamy");
	}
	if (true == ImGui::Button("Spider"))
	{
		APlayGameMode::MainPlayer->AddWeapon<ASpider>("Spider");
	}
	/*if (true == ImGui::Button("Fanbeam"))
	{
		APlayGameMode::MainPlayer->AddWeapon<AFanbeam>("Fanbeam");
	}*/
}