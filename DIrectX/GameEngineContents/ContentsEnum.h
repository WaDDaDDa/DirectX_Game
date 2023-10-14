#pragma once


enum class ContentsOrder
{
	BackGround,
	Water,
	Map,
	BackEffect,
	BackEffect2,
	HPLayer1,
	HPLayer2,
	HPLayer3,
	HPLayer4,
	Unit,
	Projectile,  // ����ü
	FrontEffect,
	UI, // UIƲ
	UIImage,
	Text,
};

enum class CollisionOrder
{
	RedTeamBody,
	BlueTeamBody,
	UnitBody,
	RedTeamAttackRange,
	BlueTeamAttackRange,
	RedTeamSkillRange,
	BlueTeamSkillRange,
	RedTeamUltRange,
	BlueTeamUltRange,
	RedTeamAttack,
	BlueTeamAttack,
	UnitAttack,
	UnitTarget,
	TestType,
};

enum class TeamType
{
	Red,
	Blue,
};