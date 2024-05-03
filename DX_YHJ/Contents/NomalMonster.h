#pragma once
#include "Monster.h"

class ANomalMonster : public AMonster
{
	GENERATED_BODY(AMonster)

public:
	// constrcuter destructer
	ANomalMonster();
	~ANomalMonster();

	// delete Function
	ANomalMonster(const ANomalMonster& _Other) = delete;
	ANomalMonster(ANomalMonster&& _Other) noexcept = delete;
	ANomalMonster& operator=(const ANomalMonster& _Other) = delete;
	ANomalMonster& operator=(ANomalMonster&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateMonsterAnimation(std::string _Name, int _MaxIndex = 2);
};

