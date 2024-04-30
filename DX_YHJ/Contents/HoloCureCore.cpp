#include "PreCompile.h"
#include "HoloCureCore.h"
#include "PlayGameMode.h"
#include "TitleGameMode.h"
#include <EngineCore/EngineSprite.h>
#include <EnginePlatform/EngineWindow.h>
#include "ContentsValue.h"

UHoloCureCore::UHoloCureCore()
{
}

UHoloCureCore::~UHoloCureCore()
{
}

void UHoloCureCore::Initialize()
{
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
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("Resources");
		Dir.Move("Sound");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav" });
		for (UEngineFile& File : Files)
		{
			UEngineSound::Load(File.GetFullPath());
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

	ContentsValue::WindowSize = GEngine->EngineWindow.GetWindowScale();

	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->ChangeLevel("TitleLevel");
}