#pragma once
#include "Ranged.h"

class AFanbeam : public ARanged
{
	GENERATED_BODY(ARanged)

public:
	// constrcuter destructer
	AFanbeam();
	~AFanbeam();

	// delete Function
	AFanbeam(const AFanbeam& _Other) = delete;
	AFanbeam(AFanbeam&& _Other) noexcept = delete;
	AFanbeam& operator=(const AFanbeam& _Other) = delete;
	AFanbeam& operator=(AFanbeam&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void UseLaser(EEngineDir _Dir);
	void CheckHit();

private:
	UCollision* Collision;

	AMonster* HitMonster;
	bool IsMonsterHit = false;
};

