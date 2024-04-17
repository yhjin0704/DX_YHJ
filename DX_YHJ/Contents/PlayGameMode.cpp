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

	// 카메라 세팅
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	float4 CameraPos = PlayerStartPos;
	CameraPos.Z = -500.0f;
	Camera->SetActorLocation(CameraPos);
	
	// 플레이어 생성
	Player = GetWorld()->SpawnActor<APlayer>("Player");
	Player->SetName("Kronii");
	Player->SetActorLocation(PlayerStartPos);

	// 커서 생성
	Cursor = GetWorld()->SpawnActor<AHoloCursor>("Cursor");
	AHoloCursor::MouseAimOn = false;
	AHoloCursor::CursorPos = GEngine->EngineWindow.GetScreenMousePos();
	Cursor->SetActorLocation(AHoloCursor::CursorPos);

	// 지면 생성
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

	AHoloCursor::CursorPos = GEngine->EngineWindow.GetScreenMousePos();
	ContentsValue::PlayLevelMousePos = FVector{ APlayer::PlayerPos.X + AHoloCursor::CursorPos.X - 640, APlayer::PlayerPos.Y - AHoloCursor::CursorPos.Y + 360 };
	Cursor->SetActorLocation(ContentsValue::PlayLevelMousePos);

	InfinityGroundCheck();

	if (PlayTime > 60.0f)
	{
		if (SpawnTerm <= 0)
		{
			SpawnMonster("KFP", 1.0f, 20.0f, 2.0f, 1.0f, 3.0f, true, 10);
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
			SpawnMonster("Takodachi", 1.0f, 80.0f, 4.0f, 0.4f, 8.0f);
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
			SpawnMonster("Deadbeat", 1.0f, 40.0f, 4.0f, 0.4f, 7.0f);
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
			SpawnMonster("Shrimp", 1.0f, 8.0f, 2.0f, 0.35f, 6.0f, false, 10);
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

void APlayGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void APlayGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
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

void APlayGameMode::SpawnMonster(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, bool _Group, int _Quantity)
{
	if (0 >= _Quantity)
	{
		MsgBoxAssert("스폰하려는 몬스터의 수가 0 이하 입니다.");
		return;
	}
	
	for (int i = 0; i < _Quantity; i++)
	{
		std::shared_ptr<AMonster> Monster;

		Monster = GetWorld()->SpawnActor<AMonster>(_Name);
		Monster->GetRenderer()->SetAutoSize(_Size, true);
		Monster->GetRenderer()->ChangeAnimation(_Name);
		Monster->SetMonsterStatus(_Hp, _Atk, _Speed, _Exp);
		Monster->SetActorLocation(RandomLocation(_Group));
	}
	GroupSpawn = false;
}

float4 APlayGameMode::RandomLocation(bool _Group)
{
	float4 MonsterPos;
	if (false == _Group)
	{
		MonsterPos = APlayer::PlayerPos;

		MonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
		MonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
	}
	else
	{
		if (false == GroupSpawn)
		{
			GroupMonsterPos = APlayer::PlayerPos; 

			GroupMonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
			GroupMonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;

			GroupSpawn = true;
		}

		MonsterPos = GroupMonsterPos;

		MonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 10.0f;
		MonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 10.0f;
	}
	
	return MonsterPos;
}

void APlayGameMode::PlayDebugText()
{
	AGameMode* ThisLevel = dynamic_cast<AGameMode*>(this);

	FIntPoint Index = PosToIndex(APlayer::PlayerPos);
	CurIndex = Index;
	
	//플레이어 위치
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerPos : X : {}, Y : {}", APlayer::PlayerPos.X, APlayer::PlayerPos.Y));
	//플레이어가 있는 BackGround
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
	//마지막으로 움직인 방향
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerDir : {}", PlayerDir));
	//마우스모드 각도
	UEngineDebugMsgWindow::PushMsg(std::format("Angle : {}", Player->GetAngle()));
}