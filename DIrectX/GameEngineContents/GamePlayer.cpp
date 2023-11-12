#include "PreCompile.h"
#include "GamePlayer.h"
#include "TeamInfo.h"

GamePlayer::GamePlayer()
{

}

GamePlayer::~GamePlayer()
{

}

void GamePlayer::Start()
{
	HouseUnit::Start();

	BodyRenderer->CreateAnimation("Idle", "GamePlayer", 0.1f, 0, 4);
	BodyRenderer->CreateAnimation("Run", "GamePlayer", 0.1f, 5, 12);
	BodyRenderer->CreateAnimation("Sleep", "GamePlayer", 0.1f, 25, 28);
	BodyRenderer->CreateAnimation("Eat", "GamePlayer", 0.1f, 29, 35, false);
	BodyRenderer->CreateAnimation("Eatting", "GamePlayer", 0.1f, 36, 38);
	BodyRenderer->CreateAnimation("Toilet", "GamePlayer", 0.1f, 39, 39);
	BodyRenderer->CreateAnimation("HandWash", "GamePlayer", 0.1f, 40, 43);
	BodyRenderer->CreateAnimation("Cpu", "GamePlayer", 0.1f, 44, 51);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(3.0f);

	BodyRenderer->SetFrameChangeFunctionAll (FrameFunction);

	int HairNum = Rand.RandomInt(1, 29);

	HairRenderer->SetSprite("Coach_Hair", HairNum);
	HairRenderer->AutoSpriteSizeOn();
	HairRenderer->SetAutoScaleRatio(3.0f);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f });

	Spec.Random();

	NameText = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	NameText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	NameText->Transform.AddLocalPosition({ 0.0f, 60.0f });
	NameText->SetText("Galmuri14", Spec.Name, 20.0f, float4::WHITE, FW1_CENTER);
	// 프레임이 바뀔때 호출되는 함수에 헤어위치를 캐릭터의 머리위치에 옮겨질수 있게하는 함수를 만든다.
	// 엔딩레벨도 만들어야함.
}

void GamePlayer::LevelStart(GameEngineLevel* _NextLevel)
{
	HouseUnit::LevelStart(_NextLevel);

	//BodyRenderer->ChangeAnimation("Idle");

}

void GamePlayer::Update(float _Delta)
{
	HouseUnit::Update(_Delta);
}

