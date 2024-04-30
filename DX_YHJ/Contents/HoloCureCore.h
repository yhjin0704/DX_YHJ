#pragma once
#include <EngineCore/EngineCore.h>

class UHoloCureCore : public UserCore
{
public:
	// constrcuter destructer
	UHoloCureCore();
	~UHoloCureCore();

	// delete Function
	UHoloCureCore(const UHoloCureCore& _Other) = delete;
	UHoloCureCore(UHoloCureCore&& _Other) noexcept = delete;
	UHoloCureCore& operator=(const UHoloCureCore& _Other) = delete;
	UHoloCureCore& operator=(UHoloCureCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;

private:
	std::string WindowIconPath;
};

