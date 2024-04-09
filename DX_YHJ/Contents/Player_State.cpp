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
			MyRender->ChangeAnimation("Kronii Idle");
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
	Renderer->ChangeAnimation("Kronii Run");
}

void APlayer::Run(float _DeltaTime)
{
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	float Speed = 500.0f;

	if (true == IsPress('A'))
	{
		SetActorScale3D(FVector(-64.0f, 64.0f, 100.0f));
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (true == IsPress('D'))
	{
		SetActorScale3D(FVector(64.0f, 64.0f, 100.0f));
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (true == IsPress(VK_NUMPAD1))
	{
		// AddActorRotation(float4{0.0f, 0.0f, 1.0f} * 360.0f * _DeltaTime);
		// Color.X += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD2))
	{
		Color.X -= _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD4))
	{
		Color.Y += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD5))
	{
		Color.Y -= _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD7))
	{
		Color.Z += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD8))
	{
		Color.Z -= _DeltaTime;
	}

	if (true == IsUp('A')|| true == IsUp('D')|| true == IsUp('W')|| true == IsUp('S'))
	{
		State.ChangeState("Idle");
	}
}
