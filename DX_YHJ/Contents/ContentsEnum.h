#pragma once

enum class ERenderOrder
{
	BackGround,
	BackObject,
	MonsterUp,
	MonsterUIUp,
	Player,
	MonsterDown,
	MonsterUIDown,
	Weapon,
	UI = 20,
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