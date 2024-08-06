#include "PreCompile.h"
#include "HoloCureCore.h"
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineFont.h>
#include "TitleGameMode.h"
#include "LobbyGameMode.h"
#include "PlayGameMode.h"
#include <EngineCore/EngineEditorGUI.h>
#include "PlayGameModeGUI.h"
#include "ContentsValue.h"

UHoloCureCore::UHoloCureCore()
{
}

UHoloCureCore::~UHoloCureCore()
{
}

void UHoloCureCore::Initialize()
{
	UEngineFont::Load("Galmuri7");
	UEngineFont::Load("Galmuri9");
	UEngineFont::Load("Galmuri11");
	UEngineFont::Load("Galmuri14");

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("Resources");
		Dir.Move("Image");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}

		{
			Dir.Move("Player");

			std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
			for (size_t i = 0; i < Directorys.size(); i++)
			{
				std::string Name = Directorys[i].GetFolderName();
				UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			}
		}

		{
			Dir.MoveParent();
			Dir.Move("Monster");

			std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
			for (size_t i = 0; i < Directorys.size(); i++)
			{
				std::string Name = Directorys[i].GetFolderName();
				UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			}
		}

		{
			Dir.MoveParent();
			Dir.Move("Weapons");

			std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
			for (size_t i = 0; i < Directorys.size(); i++)
			{
				std::string Name = Directorys[i].GetFolderName();
				UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			}
		}
	}

	{
		UEngineDirectory NewDir;
		NewDir.MoveToSearchChild("Resources");
		NewDir.Move("Image");
		std::vector<UEngineFile> AllFiles = NewDir.GetAllFile({ ".ico" }, false);
		if (AllFiles.empty() == true)
		{
			WindowIconPath = "";
		}
		else
		{
			WindowIconPath = AllFiles.front().GetFullPath();
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("Resources");
		Dir.Move("Sound");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav", ".mp3" });
		for (UEngineFile& File : Files)
		{
			File.Open(EIOOpenMode::Read, EIODataType::Binary);

			char Arr[100];
			File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}
	}

	ContentsValue::WindowSize = GEngine->EngineWindow.GetWindowScale();
	UEngineEditorGUI::CreateEditorWindow<PlayGameModeGUI>("Weapon");

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<ALobbyGameMode>("LobbyLevel");
	GEngine->CreateLevel<APlayGameMode>("PlayLevel");

	GEngine->ChangeLevel("TitleLevel");
}