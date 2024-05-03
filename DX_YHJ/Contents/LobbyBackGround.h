#pragma once
#include "BackGround.h"

class ALobbyBackGround : public ABackGround
{
	GENERATED_BODY(ABackGround)

public:
	// constrcuter destructer
	ALobbyBackGround();
	~ALobbyBackGround();

	// delete Function
	ALobbyBackGround(const ALobbyBackGround& _Other) = delete;
	ALobbyBackGround(ALobbyBackGround&& _Other) noexcept = delete;
	ALobbyBackGround& operator=(const ALobbyBackGround& _Other) = delete;
	ALobbyBackGround& operator=(ALobbyBackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

