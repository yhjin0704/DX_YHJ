#pragma once
#include <EngineCore/Actor.h>

class AVeiwStatusUI : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AVeiwStatusUI();
	~AVeiwStatusUI();

	// delete Function
	AVeiwStatusUI(const AVeiwStatusUI& _Other) = delete;
	AVeiwStatusUI(AVeiwStatusUI&& _Other) noexcept = delete;
	AVeiwStatusUI& operator=(const AVeiwStatusUI& _Other) = delete;
	AVeiwStatusUI& operator=(AVeiwStatusUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

