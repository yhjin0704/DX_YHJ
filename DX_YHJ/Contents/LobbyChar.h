#pragma once
#include <Enginecore/Actor.h>

class USpriteRenderer;
class ALobbyChar : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALobbyChar();
	~ALobbyChar();

	// delete Function
	ALobbyChar(const ALobbyChar& _Other) = delete;
	ALobbyChar(ALobbyChar&& _Other) noexcept = delete;
	ALobbyChar& operator=(const ALobbyChar& _Other) = delete;
	ALobbyChar& operator=(ALobbyChar&& _Other) noexcept = delete;

	void Setting(std::string _Image, FVector _Pos, int _RenderOrder);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;

	float MoveTime = 0;
	float MoveMaxTime;
	float4 MoveDir = FVector::Down * 10.0f;
	float UpSpeed = 3.0f;
	float DownSpeed = 3.0f;

	void Move(float _DeltaTime);
};

