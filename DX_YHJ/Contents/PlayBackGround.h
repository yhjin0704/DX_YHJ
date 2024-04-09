#pragma once
#include "BackGround.h"

class APlayBackGround : public ABackGround
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayBackGround();
	~APlayBackGround();

	// delete Function
	APlayBackGround(const APlayBackGround& _Other) = delete;
	APlayBackGround(APlayBackGround&& _Other) noexcept = delete;
	APlayBackGround& operator=(const APlayBackGround& _Other) = delete;
	APlayBackGround& operator=(APlayBackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

