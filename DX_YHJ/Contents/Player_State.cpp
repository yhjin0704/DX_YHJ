#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>
#include "HoloCursor.h"

void APlayer::StateInit()
{
	State.CreateState("Die");
	State.CreateState("Idle");
	State.CreateState("Run");

	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));

	USpriteRenderer* MyRender = Renderer;

	State.SetStartFunction("Idle", [=]
		{
			MyRender->ChangeAnimation(Name + "_Idle");
		}
	);

	State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));

	State.SetStartFunction("Run", std::bind(&APlayer::RunStart, this));

	State.ChangeState("Idle");
}


void APlayer::Die(float _Update)
{

}

void APlayer::Idle(float _Update)
{
	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		State.ChangeState("Run");
		return;
	}
}

void APlayer::RunStart()
{
	Renderer->ChangeAnimation(Name + "_Run");
}

void APlayer::Run(float _DeltaTime)
{
	Camera = GetWorld()->GetMainCamera();
	
	if (true == IsPress('W') && true == IsPress('A'))
	{
		if (false == AHoloCursor::MouseAimOn)
		{
			Renderer->SetDir(EEngineDir::Left);
		}
		KeyLineMove(_DeltaTime, FVector::Up, FVector::Left);
		PlayerDir = EPlayerDir::NW;
	}
	else if (true == IsPress('W') && true == IsPress('D'))
	{
		if (false == AHoloCursor::MouseAimOn)
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		KeyLineMove(_DeltaTime, FVector::Up, FVector::Right);
		PlayerDir = EPlayerDir::NE;
	}
	else if (true == IsPress('S') && true == IsPress('A'))
	{
		if (false == AHoloCursor::MouseAimOn)
		{
			Renderer->SetDir(EEngineDir::Left);
		}
		KeyLineMove(_DeltaTime, FVector::Down, FVector::Left);
		PlayerDir = EPlayerDir::SW;
	}
	else if (true == IsPress('S') && true == IsPress('D'))
	{
		if (false == AHoloCursor::MouseAimOn)
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		KeyLineMove(_DeltaTime, FVector::Down, FVector::Right);
		PlayerDir = EPlayerDir::SE;
	}
	else if (true == IsPress('A'))
	{
		if (false == AHoloCursor::MouseAimOn)
		{
			Renderer->SetDir(EEngineDir::Left);
		}
		KeyMove(_DeltaTime, FVector::Left, Speed);
		PlayerDir = EPlayerDir::W;
	}
	else if (true == IsPress('D'))
	{
		if (false == AHoloCursor::MouseAimOn)
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		KeyMove(_DeltaTime, FVector::Right, Speed);
		PlayerDir = EPlayerDir::E;
	}
	else if (true == IsPress('W'))
	{
		KeyMove(_DeltaTime, FVector::Up, Speed);
		PlayerDir = EPlayerDir::N;
	}
	else if (true == IsPress('S'))
	{
		KeyMove(_DeltaTime, FVector::Down, Speed);
		PlayerDir = EPlayerDir::S;
	}

	if (true == IsUp('A') || true == IsUp('D') || true == IsUp('W') || true == IsUp('S'))
	{
		State.ChangeState("Idle");
	}
}

void APlayer::KeyMove(float _DeltaTime, float4 _Dir, float _Speed)
{
	AddActorLocation(_Dir * _DeltaTime * _Speed);
	Camera->AddActorLocation(_Dir * _DeltaTime * _Speed);
}

void APlayer::KeyLineMove(float _DeltaTime, float4 _Dir1, float4 _Dir2)
{
	KeyMove(_DeltaTime, _Dir1, LineSpeed);
	KeyMove(_DeltaTime, _Dir2, LineSpeed);
}