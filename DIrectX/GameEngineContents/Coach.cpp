#include "PreCompile.h"
#include "Coach.h"
#include "TeamInfo.h"

Coach::Coach()
{

}

Coach::~Coach()
{

}

void Coach::Start()
{
	HouseUnit::Start();

	BodyRenderer->CreateAnimation("Idle", "Character_Coach", 0.2f, 0, 4);
	BodyRenderer->CreateAnimation("Sleep", "Character_Coach", 0.2f, 12, 15);
	BodyRenderer->ChangeAnimation("Idle");
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(3.0f);

}

void Coach::LevelStart(GameEngineLevel* _NextLevel)
{
	HairRenderer->SetSprite("Coach_Hair", TeamInfo::MyInfo.GetHairNum());
	HairRenderer->AutoSpriteSizeOn();
	HairRenderer->SetAutoScaleRatio(3.0f);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 100.0f });
}

void Coach::Update(float _Delta)
{
	HouseUnit::Update(_Delta);
}

