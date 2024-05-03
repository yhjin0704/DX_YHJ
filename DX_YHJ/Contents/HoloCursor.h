#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

class USpriteRenderer;
class AHoloCursor : public AActor
{
	GENERATED_BODY(AActor)

public:
	static float4 CursorPos;
	static bool MouseAimOn;

	// constrcuter destructer
	AHoloCursor();
	~AHoloCursor();

	// delete Function
	AHoloCursor(const AHoloCursor& _Other) = delete;
	AHoloCursor(AHoloCursor&& _Other) noexcept = delete;
	AHoloCursor& operator=(const AHoloCursor& _Other) = delete;
	AHoloCursor& operator=(AHoloCursor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CursorOFf();
	void ChangeAimMode();
	void CheckAimMode();

private:
	UImage* Renderer;
	UCollision* Collision;
};

