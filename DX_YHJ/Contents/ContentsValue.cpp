#include "PreCompile.h"
#include "ContentsValue.h"

FVector ContentsValue::WindowSize = { 0,0 };
float ContentsValue::MultipleSize = 2.0f;

const float4 ContentsValue::GroundTileSize = {2560.0f * MultipleSize, 2560.0f * MultipleSize };

float4 ContentsValue::PlayLevelMousePos = float4::Zero;

const float ContentsValue::BaseSpeed = 200.0f;
const float ContentsValue::BaseHaste = 1.0f;
const float ContentsValue::BasePUR = 40.0f;
