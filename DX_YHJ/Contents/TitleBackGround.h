#pragma once
#include "BackGround.h"

class ATitleBackGround : public ABackGround
{
	GENERATED_BODY(ABackGround)

public:
	// constrcuter destructer
	ATitleBackGround();
	~ATitleBackGround();

	// delete Function
	ATitleBackGround(const ATitleBackGround& _Other) = delete;
	ATitleBackGround(ATitleBackGround&& _Other) noexcept = delete;
	ATitleBackGround& operator=(const ATitleBackGround& _Other) = delete;
	ATitleBackGround& operator=(ATitleBackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* FadeRenderer;

	float CheckTitleTime = 0.0f;

	int Sequence = 0;
	int FadeSequence = 0;

	float FadeAlpha = 0.0f;
	bool IsFadeIn = false;
	bool IsFadeOut = false;

	void TitleChange(float _DeltaTime, std::string _SpriteName, float _Time = 2.0f);

	void FadeIn(float _DeltaTime);
	void FadeOut(float _DeltaTime);
};

