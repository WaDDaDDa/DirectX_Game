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

	BodyRenderer->CreateAnimation("Idle", "Character_Coach", 0.1f, 0, 4);
	BodyRenderer->CreateAnimation("Run", "Character_Coach", 0.1f, 5, 11);
	BodyRenderer->CreateAnimation("Sleep", "Character_Coach", 0.1f, 12, 15);
	BodyRenderer->CreateAnimation("Eat", "Character_Coach", 0.1f, 16, 22, false);
	BodyRenderer->CreateAnimation("Eatting", "Character_Coach", 0.1f, 23, 25);
	BodyRenderer->CreateAnimation("Toilet", "Character_Coach", 0.1f, 26, 26);
	BodyRenderer->CreateAnimation("HandWash", "Character_Coach", 0.1f, 27, 30);
	BodyRenderer->CreateAnimation("Cpu", "Character_Coach", 0.1f, 31, 32);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(3.0f);

	BodyRenderer->SetFrameChangeFunctionAll (FrameFunction);

	NameText = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	NameText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	NameText->Transform.AddLocalPosition({ 0.0f, 60.0f });
	NameText->SetText("Galmuri14", TeamInfo::MyInfo.GetCoachName(), 20.0f, float4{27.0f, 144.0f, 255.0f}, FW1_CENTER);

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

