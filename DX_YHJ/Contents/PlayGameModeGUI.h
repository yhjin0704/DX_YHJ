#pragma once
#include <EngineCore/EngineDebugMsgWindow.h>

class PlayGameModeGUI : public UEngineDebugMsgWindow
{
	GENERATED_BODY(UEngineDebugMsgWindow)

public:
	// constrcuter destructer
	PlayGameModeGUI();
	~PlayGameModeGUI();

	// delete Function
	PlayGameModeGUI(const PlayGameModeGUI& _Other) = delete;
	PlayGameModeGUI(PlayGameModeGUI&& _Other) noexcept = delete;
	PlayGameModeGUI& operator=(const PlayGameModeGUI& _Other) = delete;
	PlayGameModeGUI& operator=(PlayGameModeGUI&& _Other) noexcept = delete;

protected:
	void Init() override;
	void OnGui(ULevel* Level, float _Delta) override;

private:

};

