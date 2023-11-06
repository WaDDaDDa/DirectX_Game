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
	BodyRenderer->CreateAnimation("Run", "Character_Coach", 0.2f, 5, 11);
	BodyRenderer->CreateAnimation("Sleep", "Character_Coach", 0.2f, 12, 15);
	BodyRenderer->CreateAnimation("WHat", "Character_Coach", 0.2f, 16, 22);
	BodyRenderer->CreateAnimation("Eat", "Character_Coach", 0.2f, 23, 25);
	BodyRenderer->CreateAnimation("Toilet", "Character_Coach", 0.2f, 26, 26);
	BodyRenderer->CreateAnimation("HandWash", "Character_Coach", 0.2f, 27, 30);
	BodyRenderer->CreateAnimation("Cpu", "Character_Coach", 0.2f, 31, 32);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(3.0f);

	BodyRenderer->SetFrameChangeFunctionAll (FrameFunction);

	// �������� �ٲ� ȣ��Ǵ� �Լ��� �����ġ�� ĳ������ �Ӹ���ġ�� �Ű����� �ְ��ϴ� �Լ��� �����.
	// ���������� ��������.

}

void Coach::LevelStart(GameEngineLevel* _NextLevel)
{
	HouseUnit::LevelStart(_NextLevel);

	HairRenderer->SetSprite("Coach_Hair", TeamInfo::MyInfo.GetHairNum());
	HairRenderer->AutoSpriteSizeOn();
	HairRenderer->SetAutoScaleRatio(3.0f);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f });


	//BodyRenderer->ChangeAnimation("Idle");

}

void Coach::Update(float _Delta)
{
	HouseUnit::Update(_Delta);

}

