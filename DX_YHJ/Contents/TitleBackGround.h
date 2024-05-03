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

};

