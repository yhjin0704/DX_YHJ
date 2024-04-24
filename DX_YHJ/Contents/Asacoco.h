#pragma once
#include "Ranged.h"

class AAsacoco : public ARanged
{
	GENERATED_BODY(ARanged)

public:
	// constrcuter destructer
	AAsacoco();
	~AAsacoco();

	// delete Function
	AAsacoco(const AAsacoco& _Other) = delete;
	AAsacoco(AAsacoco&& _Other) noexcept = delete;
	AAsacoco& operator=(const AAsacoco& _Other) = delete;
	AAsacoco& operator=(AAsacoco&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

