#include "PreCompile.h"
#include "PlayerRecruitmentUI.h"
#include "RecruitCard.h"

PlayerRecruitmentUI::PlayerRecruitmentUI()
{

}

PlayerRecruitmentUI::~PlayerRecruitmentUI()
{

}

void PlayerRecruitmentUI::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -100.0f });
	Transform.AddLocalPosition({ 0.0f, 20.0f });
	// ¹Ú½º
	BoxRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	BoxRenderer->SetSprite("PlayerRecruitment", 5);
	BoxRenderer->AutoSpriteSizeOn();
	BoxRenderer->SetAutoScaleRatio(2.0f);
	BoxRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });
	//BoxRenderer->Transform.AddLocalPosition({ 0.0f, 325.0f });

	Card = GetLevel()->CreateActor<RecruitCard>();
	Card->Transform.AddLocalPosition({ -460.0f, 20.0f });
}

void PlayerRecruitmentUI::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayerRecruitmentUI::Update(float _Delta)
{

}