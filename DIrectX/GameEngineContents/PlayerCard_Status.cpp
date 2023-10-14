#include "PreCompile.h"
#include "PlayerCard.h"
#include "PlayerCard_Status.h"
#include "GameUnit.h"

PlayerCard_Status::PlayerCard_Status()
{

}

PlayerCard_Status::~PlayerCard_Status()
{

}

void PlayerCard_Status::Start()
{

}

void PlayerCard_Status::LevelStart(GameEngineLevel* _PrevLevel)
{

}


void PlayerCard_Status::Init()
{

	// Status Ʋ
	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("PlayerCard_StatusBlue", "PlayerCard", 0.1f, 0, 0, false);
	Renderer->CreateAnimation("PlayerCard_StatusRed", "PlayerCard", 0.1f, 1, 1, false);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	float4 CardPos = PCard->Transform.GetLocalPosition();

	if (TeamType::Blue == PCard->GetUnit()->MyTeam)
	{
		StartPos.X = 118.0f;
		Transform.SetLocalPosition(CardPos + StartPos);
		Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

		Renderer->ChangeAnimation("PlayerCard_StatusBlue");

	}
	else if (TeamType::Red == PCard->GetUnit()->MyTeam)
	{
		StartPos.X = -118.0f;

		Transform.SetLocalPosition(CardPos + StartPos);
		Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

		Renderer->ChangeAnimation("PlayerCard_StatusRed");

	}
}

void PlayerCard_Status::Update(float _Delta)
{

}

void PlayerCard_Status::LevelEnd(GameEngineLevel* _NextLevel)
{

}