#include "PreCompile.h"
#include "BundleButton.h"


BundleButton::BundleButton()
{

}

BundleButton::~BundleButton()
{

}

void BundleButton::Start()
{
	UI_Button::Start();
	float4 TeamLogoColScale = { 130.0f , 40.0f };
	SetButtonColScale(TeamLogoColScale);
	Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("Null", "MainUI", 0.1f, 9, 9, false);
	Renderer->CreateAnimation("Null_Stay", "MainUI", 0.1f, 10, 10, false);
	Renderer->CreateAnimation("Slect", "MainUI", 0.1f,11, 11, false);
	Renderer->ChangeAnimation("Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.2f);

	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
}

void BundleButton::LevelEnd(GameEngineLevel* _NextLevel)
{

}


void BundleButton::IdleStart()
{
	Renderer->ChangeAnimation("Null");
	ButtonText->SetText("Galmuri14", ButtonName, 16.0f, float4::WHITE, Flag);
}

void BundleButton::StayStart()
{
	Renderer->ChangeAnimation("Null_Stay");
	ButtonText->SetText("Galmuri14", ButtonName, 16.0f, { 204.0f / 255.0f, 1.0f, 58.0f / 255.0f }, Flag);

}

void BundleButton::EndStart()
{
	ButtonText->SetText("Galmuri14", ButtonName, 16.0f, float4::WHITE, Flag);

	Renderer->ChangeAnimation("Null");


	//if (false == IsSelect)
	//{
	//	Renderer->ChangeAnimation("Null");
	//}
	//else if (true == IsSelect)
	//{
	//	Renderer->ChangeAnimation("Slect");
	//}
}

void BundleButton::ClickStart()
{
	UI_Button::ClickStart();

	Renderer->ChangeAnimation("Slect");
	ButtonText->SetText("Galmuri14", ButtonName, 16.0f, float4::WHITE, Flag);

	if (false == IsSelect)
	{
		IsSelect = true;
	}
}