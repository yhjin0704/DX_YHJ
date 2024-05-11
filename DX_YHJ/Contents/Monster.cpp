#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
#include "Weapon.h"

AMonster::AMonster()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	SavedRenderer = CreateDefaultSubObject<USpriteRenderer>("SavedRenderer");
	SavedRenderer->SetupAttachment(Root);
	SavedRenderer->SetAutoSize(ContentsValue::MultipleSize, true);
	SavedRenderer->SetActive(false);

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(Root);
	ShadowRenderer->SetAutoSize(ContentsValue::MultipleSize, true);
	ShadowRenderer->SetPivot(EPivot::BOT);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);

	OverCheckCollision = CreateDefaultSubObject<UCollision>("OverCheckCollision");
	OverCheckCollision->SetupAttachment(Root);
	OverCheckCollision->SetCollisionGroup(ECollisionOrder::MonsterRender);
	OverCheckCollision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetOrder(ERenderOrder::MonsterUp);

	SavedRenderer->CreateAnimation("MonsterSavedHeart", "MonsterSavedHeart", 0.1f, false);
	SavedRenderer->SetOrder(ERenderOrder::MonsterUIUp);
	SavedRenderer->ChangeAnimation("MonsterSavedHeart");

	ShadowRenderer->SetSprite("Shadow_0.png");
	ShadowRenderer->SetOrder(ERenderOrder::Shadow);
}


void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckPosComparePlayer();
	CheckOverPlayer();
	TimeOutDestory(_DeltaTime);
}

void AMonster::SetMonsterStatus(int _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _WillTimeOutDestroy, float _TimeOutDestoryDelay)
{
	Hp = _Hp;
	Atk = _Atk;
	Speed = _Speed;
	CalSpeed = ContentsValue::BaseSpeed * Speed;
	Exp = _Exp;
	MoveType = _MoveType;
	WillTimeOutDestory = _WillTimeOutDestroy;
	TimeOutDestoryDelay = _TimeOutDestoryDelay;
}

FVector AMonster::CreateGroupToPlayerDir()
{
	FVector GroupDir = APlayer::PlayerColPos - GetActorLocation();
	GroupDir = GroupDir.Normalize2DReturn();
	return GroupDir;
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

void AMonster::CheckOverPlayer()
{
	OverCheckCollision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			Renderer->SetMulColor(float4{ 1.0f, 1.0f, 1.0f, 0.5f });
		}
	);

	OverCheckCollision->CollisionExit(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			Renderer->SetMulColor(float4::One);
		}
	);
}

void AMonster::CheckSaved()
{
	if (0 >= Hp)
	{
		IsSaved = true;
		SavedDir = Renderer->GetDir();
	}
}

void AMonster::Saved(float _DeltaTime)
{
	SavedRenderer->SetActive(true);
	ShadowRenderer->SetActive(false);

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

void AMonster::TimeOutDestory(float _DeltaTime)
{
	if (true == WillTimeOutDestory)
	{
		TimeOutDestoryDelay -= _DeltaTime;
		if (0.0f >= TimeOutDestoryDelay)
		{
			Renderer->SetActive(false);
			SavedRenderer->SetActive(true);
			if (true == SavedRenderer->IsCurAnimationEnd())
			{
				Destroy();
			}
		}
	}
}