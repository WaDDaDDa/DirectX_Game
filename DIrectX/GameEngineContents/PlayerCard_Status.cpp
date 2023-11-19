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

	InfoText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	InfoText->SetText("Galmuri14", "Info", 16.0f, float4::WHITE, FW1_CENTER);
	InfoText->Transform.AddLocalPosition({ -2.0f, 68.0f, -static_cast<float>(ContentsOrder::Text) });

	KillText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	KillText->SetText("Galmuri14", "K", 14.0f, float4::WHITE, FW1_CENTER);
	KillText->Transform.AddLocalPosition({ -24.0f, 42.0f, -static_cast<float>(ContentsOrder::Text) });

	DeathText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	DeathText->SetText("Galmuri14", "D", 14.0f, float4::WHITE, FW1_CENTER);
	DeathText->Transform.AddLocalPosition({ 0.0f, 42.0f, -static_cast<float>(ContentsOrder::Text) });

	AsistText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	AsistText->SetText("Galmuri14", "A", 14.0f, float4::WHITE, FW1_CENTER);
	AsistText->Transform.AddLocalPosition({ 24.0f, 42.0f, -static_cast<float>(ContentsOrder::Text) });

	KillInfo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	KillInfo->SetText("Galmuri14", "0", 14.0f, float4::WHITE, FW1_CENTER);
	KillInfo->Transform.AddLocalPosition({ -24.0f, 22.0f, -static_cast<float>(ContentsOrder::Text) });

	DeathInfo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	DeathInfo->SetText("Galmuri14", "0", 14.0f, float4::WHITE, FW1_CENTER);
	DeathInfo->Transform.AddLocalPosition({ 0.0f, 22.0f, -static_cast<float>(ContentsOrder::Text) });

	AsistInfo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	AsistInfo->SetText("Galmuri14", "0", 14.0f, float4::WHITE, FW1_CENTER);
	AsistInfo->Transform.AddLocalPosition({ 24.0f, 22.0f, -static_cast<float>(ContentsOrder::Text) });

	AttInfo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	AttInfo->SetText("Galmuri14", "0", 16.0f, float4::WHITE, FW1_CENTER);
	AttInfo->Transform.AddLocalPosition({ 10.0f, -6.0f, -static_cast<float>(ContentsOrder::Text) });

	DefInfo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	DefInfo->SetText("Galmuri14", "0", 16.0f, float4::WHITE, FW1_CENTER);
	DefInfo->Transform.AddLocalPosition({ 10.0f, -30.0f, -static_cast<float>(ContentsOrder::Text) });

	HealInfo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	HealInfo->SetText("Galmuri14", "0", 16.0f, float4::WHITE, FW1_CENTER);
	HealInfo->Transform.AddLocalPosition({ 10.0f, -54.0f, -static_cast<float>(ContentsOrder::Text) });

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
	KillInfo->SetText("Galmuri14", std::to_string(PCard->GetUnit()->GetKillCount()), 14.0f, float4::WHITE, FW1_CENTER);
	DeathInfo->SetText("Galmuri14", std::to_string(PCard->GetUnit()->GetDieCount()), 14.0f, float4::WHITE, FW1_CENTER);

	std::string AttInfoText = GameEngineString::Format("{:.0f}", PCard->GetUnit()->GetAttDamage());
	std::string DefInfoText = GameEngineString::Format("{:.0f}", PCard->GetUnit()->GetDefDamage());
	std::string HealInfoText = GameEngineString::Format("{:.0f}", PCard->GetUnit()->GetHealling());

	AttInfo->SetText("Galmuri14", AttInfoText, 16.0f, float4::WHITE, FW1_CENTER);
	DefInfo->SetText("Galmuri14", DefInfoText, 16.0f, float4::WHITE, FW1_CENTER);
	HealInfo->SetText("Galmuri14", HealInfoText, 16.0f, float4::WHITE, FW1_CENTER);

}

void PlayerCard_Status::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}