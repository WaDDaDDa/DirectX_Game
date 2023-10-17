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
	Projectile,  // 투사체
	FrontEffect,
	BackUI,
	UI, // UI틀
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
	Button,
	Mouse,
};

enum class TeamType
{
	Red,
	Blue,
};