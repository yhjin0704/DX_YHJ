#pragma once
#include <EngineCore/EngineCore.h>

// Ό³Έν :
class USamCore : public UserCore
{
public:
	// constrcuter destructer
	USamCore();
	~USamCore();

	// delete Function
	USamCore(const USamCore& _Other) = delete;
	USamCore(USamCore&& _Other) noexcept = delete;
	USamCore& operator=(const USamCore& _Other) = delete;
	USamCore& operator=(USamCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;

private:

};

