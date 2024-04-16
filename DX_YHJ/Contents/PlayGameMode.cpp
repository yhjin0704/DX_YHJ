#include "PreCompile.h"
#include "PlayGameMode.h"
#include "ContentsValue.h"
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineBase/EngineRandom.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	float4 MapScale = UEngineTexture::FindRes("Holo_Stage_1_Back_Ground.png")->GetScale();

	CurIndex = { 0, 0 };
	float4 PlayerStartPos = IndexToCenterPos(CurIndex);

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	float4 CameraPos = PlayerStartPos;
	CameraPos.Z = -500.0f;
	Camera->SetActorLocation(CameraPos);

	Player = GetWorld()->SpawnActor<APlayer>("Player");
	Player->SetName("Kronii");

	float4 ImageScale = { 64.0f, 64.0f, 0.0f };

	Player->SetActorScale3D(ImageScale);
	Player->SetActorLocation(PlayerStartPos);

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			std::shared_ptr<APlayBackGround> BackGround = GetWorld()->SpawnActor<APlayBackGround>("PlayBackGround");

			BackGround->SetActorScale3D(ContentsValue::GroundTileSize);

			FIntPoint Point;
			Point.X = x;
			Point.Y = y;

			float4 Pos;
			Pos.X = ContentsValue::GroundTileSize.X * x;
			Pos.Y = ContentsValue::GroundTileSize.Y * y;

			Pos.X += ContentsValue::GroundTileSize.hX();
			Pos.Y += ContentsValue::GroundTileSize.hY();
			BackGround->SetActorLocation(Pos);

			BackGroundVector.push_back(BackGround);
		}
	}
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	InfinityGroundCheck();

	if (PlayTime > 60.0f)
	{
		if (SpawnTerm <= 0)
		{
			SpawnMonster("KFP", 1.0f, 20.0f, 2.0f, 1.0f, 3.0f, RandomLocation());
			SpawnTerm = 5.0f;
		}
		else
		{
			SpawnTerm -= _DeltaTime;
		}
	}
	else if (PlayTime > 40.0f)
	{
		if (SpawnTerm <= 0)
		{
			SpawnMonster("Takodachi", 1.0f, 80.0f, 4.0f, 0.4f, 8.0f, RandomLocation());
			SpawnTerm = 5.0f;
		}
		else
		{
			SpawnTerm -= _DeltaTime;
		}
	}
	else if (PlayTime > 20.0f)
	{
		if (SpawnTerm <= 0)
		{
			SpawnMonster("Deadbeat", 1.0f, 40.0f, 4.0f, 0.4f, 7.0f, RandomLocation());
			SpawnTerm = 5.0f;
		}
		else
		{
			SpawnTerm -= _DeltaTime;
		}
	}
	else
	{
		if (SpawnTerm <= 0)
		{
			SpawnMonster("Shrimp", 1.0f, 8.0f, 2.0f, 0.35f, 6.0f, RandomLocation());
			SpawnTerm = 5.0f;
		}
		else
		{
			SpawnTerm -= _DeltaTime;
		}
	}

	PlayTime += _DeltaTime;
	PlayDebugText();
}

float4 APlayGameMode::IndexToCenterPos(FIntPoint _Index)
{
	float4 Pos;
	Pos.X = ContentsValue::GroundTileSize.X * _Index.X;
	Pos.Y = ContentsValue::GroundTileSize.Y * _Index.Y;

	Pos.X += ContentsValue::GroundTileSize.hX();
	Pos.Y += ContentsValue::GroundTileSize.hY();

	return Pos;
}

FIntPoint APlayGameMode::PosToIndex(float4 _Pos)
{
	FIntPoint Index;

	float4 Location = _Pos;

	float4 Pos;
	Pos.X = Location.X / ContentsValue::GroundTileSize.X;
	Pos.Y = Location.Y / ContentsValue::GroundTileSize.Y;

	if (0 >= Pos.X)
	{
		Pos.X += -1;
	}
	if (0 >= Pos.Y)
	{
		Pos.Y += -1;
	}

	Index.X = Pos.X;
	Index.Y = Pos.Y;
	return Index;
}

void APlayGameMode::InfinityGroundCheck()
{
	FIntPoint Index = PosToIndex(APlayer::PlayerPos);

	if (Index.X != CurIndex.X || Index.Y != CurIndex.Y)
	{
		int GroundCount = 0;

		float4 MovePos;
		MovePos.X = Index.X * ContentsValue::GroundTileSize.X;
		MovePos.Y = Index.Y * ContentsValue::GroundTileSize.Y;

		for (int y = -1; y < 2; y++)
		{
			for (int x = -1; x < 2; x++)
			{
				std::shared_ptr<APlayBackGround> BackGround = BackGroundVector[GroundCount];

				BackGround->SetActorScale3D(ContentsValue::GroundTileSize);
				FIntPoint Point;
				Point.X = x;
				Point.Y = y;

				float4 Pos;
				Pos.X = ContentsValue::GroundTileSize.X * x;
				Pos.Y = ContentsValue::GroundTileSize.Y * y;

				Pos.X += ContentsValue::GroundTileSize.hX();
				Pos.Y += ContentsValue::GroundTileSize.hY();
				BackGround->SetActorLocation(Pos + MovePos);
				++GroundCount;
			}
		}

		CurIndex = Index;
	}
}

void APlayGameMode::SpawnMonster(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, float4 _Location)
{
	std::shared_ptr<AMonster> Monster;

	Monster = GetWorld()->SpawnActor<AMonster>(_Name);
	Monster->GetRenderer()->SetAutoSize(_Size, true);
	Monster->GetRenderer()->ChangeAnimation(_Name);
	Monster->SetMonsterStatus(_Hp, _Atk, _Speed, _Exp);
	Monster->SetActorLocation(_Location);
}

float4 APlayGameMode::RandomLocation()
{
	float4 MonsterPos = APlayer::PlayerPos;
	MonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
	MonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
	
	return MonsterPos;
}

void APlayGameMode::PlayDebugText()
{
	AGameMode* ThisLevel = dynamic_cast<AGameMode*>(this);

	FIntPoint Index = PosToIndex(APlayer::PlayerPos);
	CurIndex = Index;
	
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerPos : X : {}, Y : {}", APlayer::PlayerPos.X, APlayer::PlayerPos.Y));
	UEngineDebugMsgWindow::PushMsg(std::format("BackGroundIndex : {}, {}", Index.X, Index.Y));
	
	std::string PlayerDir = "";
	switch (Player->GetPlayerDir())
	{
	case EPlayerDir::N:
		PlayerDir = "N";
		break;
	case EPlayerDir::NE:
		PlayerDir = "NE";
		break;
	case EPlayerDir::NW:
		PlayerDir = "NW";
		break;
	case EPlayerDir::E:
		PlayerDir = "E";
		break;
	case EPlayerDir::W:
		PlayerDir = "W";
		break;
	case EPlayerDir::S:
		PlayerDir = "S";
		break;
	case EPlayerDir::SE:
		PlayerDir = "SE";
		break;
	case EPlayerDir::SW:
		PlayerDir = "SW";
		break;
	default:
		break;
	}
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerDir : {}", PlayerDir));
}