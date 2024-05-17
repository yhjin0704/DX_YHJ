#pragma once
#include "Melee.h"
class ASpider : public AMelee
{
	GENERATED_BODY(AMelee)

public:
	// constrcuter destructer
	ASpider();
	~ASpider();

	// delete Function
	ASpider(const ASpider& _Other) = delete;
	ASpider(ASpider&& _Other) noexcept = delete;
	ASpider& operator=(const ASpider& _Other) = delete;
	ASpider& operator=(ASpider&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckHit(float _DeltaTime);

private:
	UCollision* Collision;

	AMonster* HitMonster;
	bool IsMonsterHit = false;
};

