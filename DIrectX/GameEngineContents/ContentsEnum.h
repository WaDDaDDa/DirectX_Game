#pragma once


enum class ContentsOrder
{
	BackGround,
	Water,
	Map,
	BackEffect,
	Unit,
	FrontEffect,
	UI,
	Text,
};

enum class CollisionOrder
{
	RedTeamBody,
	BlueTeamBody,
	UnitBody,
	RedTeamAttackRange,
	BlueTeamAttackRange,
	RedTeamAttack,
	BlueTeamAttack,
	UnitAttack,
	UnitTarget,
};

enum class TeamType
{
	Red,
	Blue,
};