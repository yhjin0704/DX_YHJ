#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"

AMonster::AMonster()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	SavedRenderer = CreateDefaultSubObject<USpriteRenderer>("SavedRenderer");
	SavedRenderer->SetupAttachment(Root);
	SavedRenderer->SetAutoSize(ContentsValue::MultipleSize, true);
	SavedRenderer->SetActive(false);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
	
	SetRoot(Root);
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	CreateMonsterAnimation("Shrimp");
	CreateMonsterAnimation("Deadbeat");
	CreateMonsterAnimation("Takodachi");
	CreateMonsterAnimation("KFP");

	Renderer->SetAutoSize(ContentsValue::MultipleSize, true);
	Renderer->ChangeAnimation(Name);
	Renderer->SetOrder(ERenderOrder::MonsterUp);

	SavedRenderer->CreateAnimation("MonsterSavedHeart", "MonsterSavedHeart", 0.1f, false);
	SavedRenderer->SetOrder(ERenderOrder::MonsterUIUp);
	SavedRenderer->ChangeAnimation("MonsterSavedHeart");
}


void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (false == IsSaved)
	{
		Move(_DeltaTime, MoveType);

		if (0 > Dir.X)
		{
			Renderer->SetDir(EEngineDir::Left);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Right);
		}

		CheakSaved();
		CheckHit();
	}
	else
	{
		Saved(_DeltaTime);
	}
	
	CheckPosComparePlayer();
}

void AMonster::SetMonsterStatus(float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType)
{
	Hp = _Hp;
	Atk = _Atk;
	Speed = _Speed;
	CalSpeed = ContentsValue::BaseSpeed * Speed;
	Exp = _Exp;
	MoveType = _MoveType;
}

FVector AMonster::CreateGroupToPlayerDir()
{
	FVector GroupDir = APlayer::PlayerColPos - GetActorLocation();
	GroupDir = GroupDir.Normalize2DReturn();
	return GroupDir;
}

void AMonster::CreateMonsterAnimation(std::string _Name, int _MaxIndex)
{
	Renderer->CreateAnimation(_Name, _Name, 0.1f, true, 0, _MaxIndex);
}

void AMonster::Move(float _DeltaTime, EMonsterMoveType _MoveType)
{
	FVector MonsterPos = GetActorLocation();

	switch (_MoveType)
	{
	case EMonsterMoveType::Follow:
		Dir = APlayer::PlayerColPos - MonsterPos;
		Dir = Dir.Normalize2DReturn();
		break;
	case EMonsterMoveType::StraightToPlayer:
		Dir = ToPlayerDir;
		break;
	case EMonsterMoveType::StraightToUp:
		break;
	case EMonsterMoveType::StraightToDown:
		break;
	case EMonsterMoveType::StraightToRight:
		break;
	case EMonsterMoveType::StraightToLeft:
		break;
	case EMonsterMoveType::Stop:
		break;
	default:
		break;
	}

	AddActorLocation(Dir * _DeltaTime * CalSpeed);
}

void AMonster::CheckPosComparePlayer()
{
	if (APlayer::PlayerColPos.Y <= GetActorLocation().Y)
	{
		Renderer->SetOrder(ERenderOrder::MonsterUp);
		SavedRenderer->SetOrder(ERenderOrder::MonsterUIUp);
	}
	else
	{
		Renderer->SetOrder(ERenderOrder::MonsterDown);
		SavedRenderer->SetOrder(ERenderOrder::MonsterUIDown);
	}
}

void AMonster::CheckHit()
{
	Collision->CollisionEnter(ECollisionOrder::Weapon, [=](std::shared_ptr<UCollision> _Collison)
		{
			
		}
	);
}

void AMonster::CheakSaved()
{
	if ( 0 >= Hp)
	{
		IsSaved = true;
		SavedDir = Renderer->GetDir();
	}
}

void AMonster::Saved(float _DeltaTime)
{
	SavedRenderer->SetActive(true);

	if (EEngineDir::Left == SavedDir)
	{
		Renderer->AddPosition(FVector{ 1.0f, 0.0f } *_DeltaTime * 100.0f * ContentsValue::MultipleSize);
	}
	else if (EEngineDir::Right == SavedDir)
	{
		Renderer->AddPosition(FVector{ -1.0f, 0.0f } *_DeltaTime * 100.0f * ContentsValue::MultipleSize);
	}
	else
	{
		MsgBoxAssert("몬스터의 SavedDir값이 잘못됐습니다.");
		return;
	}

	RendererAlpha -= _DeltaTime;
	Renderer->SetMulColor(float4{ 1.0f, 1.0f, 1.0f, RendererAlpha });

	if (true == SavedRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}