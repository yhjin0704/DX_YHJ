#pragma once
class SpawnMonster
{
public:
	// constrcuter destructer
	SpawnMonster();
	~SpawnMonster();

	// delete Function
	SpawnMonster(const SpawnMonster& _Other) = delete;
	SpawnMonster(SpawnMonster&& _Other) noexcept = delete;
	SpawnMonster& operator=(const SpawnMonster& _Other) = delete;
	SpawnMonster& operator=(SpawnMonster&& _Other) noexcept = delete;

protected:

private:

};

