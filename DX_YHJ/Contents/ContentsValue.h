#pragma once

// Ό³Έν :
class ContentsValue
{
public:
	static FVector WindowSize;
	static float MultipleSize;

	static UEngineSoundPlayer BGMPlayer;

	static const float4 GroundTileSize;

	static float4 PlayLevelMousePos;

	static const float BaseSpeed;
	static const float BaseHaste;
	static const float BasePUR;

	static void ChangeBGM(std::string_view _BGMName);
};

