#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>

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
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();

	
	if (true == IsPress('W') && true == IsPress('A'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Up * _DeltaTime * LineSpeed);
		Renderer->SetDir(EEngineDir::Left);
		AddActorLocation(FVector::Left * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * LineSpeed);
		PlayerDir = EPlayerDir::NW;
	}
	else if (true == IsPress('W') && true == IsPress('D'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Up * _DeltaTime * LineSpeed);
		Renderer->SetDir(EEngineDir::Right);
		AddActorLocation(FVector::Right * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Right * _DeltaTime * LineSpeed);
		PlayerDir = EPlayerDir::NE;
	}
	else if (true == IsPress('S') && true == IsPress('A'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Down * _DeltaTime * LineSpeed);
		Renderer->SetDir(EEngineDir::Left);
		AddActorLocation(FVector::Left * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * LineSpeed);
		PlayerDir = EPlayerDir::SW;
	}
	else if (true == IsPress('S') && true == IsPress('D'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Down * _DeltaTime * LineSpeed);
		Renderer->SetDir(EEngineDir::Right);
		AddActorLocation(FVector::Right * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Right * _DeltaTime * LineSpeed);
		PlayerDir = EPlayerDir::SE;
	}
	else if (true == IsPress('A'))
	{
		Renderer->SetDir(EEngineDir::Left);
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * Speed);
		PlayerDir = EPlayerDir::W;
	}
	else if (true == IsPress('D'))
	{
		Renderer->SetDir(EEngineDir::Right);
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Right * _DeltaTime * Speed);
		PlayerDir = EPlayerDir::E;
	}
	else if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Up * _DeltaTime * Speed);
		PlayerDir = EPlayerDir::N;
	}
	else if (true == IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Down * _DeltaTime * Speed);
		PlayerDir = EPlayerDir::S;
	}

	if (true == IsUp('A') || true == IsUp('D') || true == IsUp('W') || true == IsUp('S'))
	{
		State.ChangeState("Idle");
	}
}
