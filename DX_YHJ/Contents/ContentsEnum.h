#pragma once

enum class ERenderOrder
{
	BackGround,
	BackObject,
	Shadow,
	MonsterUp,
	MonsterUIUp,
	Player,
	MonsterDown,
	MonsterUIDown,
	Weapon,
	BackUI = 21,
	UI,
	UIFrame,
	FrontUI,
	Cursor,
};

enum class ECollisionOrder
{
	Player = 1,
	Monster,
	MonsterRender,
	ZoneCheck,
	Weapon,
	Obstacle,
	UIButton,
	Cursor,
};

enum class EUIOrder
{
	Frame,
	PlayInfo,
	Text,
	PauseBack,
	PauseFrame,
	PauseObject,
	PauseText,
	Cursor,
};

enum class EDir
{
	Left,
	Right,
};

enum class EPlayerDir
{
	N,
	NE,
	E,
	SE,
	S,
	SW,
	W,
	NW,
};

enum class EMonsterMoveType
{
	Follow,
	StraightToPlayer,
	StraightToUp,
	StraightToDown,
	StraightToRight,
	StraightToLeft,
	Stop,
};