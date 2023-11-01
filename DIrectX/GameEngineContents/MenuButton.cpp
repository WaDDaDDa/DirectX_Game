#include "PreCompile.h"
#include "MenuButton.h"


MenuButton::MenuButton()
{

}

MenuButton::~MenuButton()
{

}

void MenuButton::Start()
{
	UI_Button::Start();
	float4 TeamLogoColScale = { 120.0f , 40.0f };
	SetButtonColScale(TeamLogoColScale);
	//Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("Null", "MainUI", 0.1f, 9, 9, false);
	Renderer->CreateAnimation("Null_Stay", "MainUI", 0.1f, 10, 10, false);
	Renderer->CreateAnimation("Slect", "MainUI", 0.1f,11, 11, false);
	Renderer->ChangeAnimation("Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.2f);

	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
}


void MenuButton::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

void MenuButton::IdleStart()
{
	Renderer->ChangeAnimation("Null");
	ButtonText->SetText("Galmuri14", ButtonName, 15.0f, float4::WHITE, Flag);
	IconRenderer->GetColorData().MulColor = { 255.0f / 204.0f, 1.0f, 255.0f / 58.0f };
}

void MenuButton::StayStart()
{
	Renderer->ChangeAnimation("Null_Stay");
	ButtonText->SetText("Galmuri14", ButtonName, 15.0f, { 204.0f / 255.0f, 1.0f, 58.0f / 255.0f }, Flag);
	IconRenderer->GetColorData().MulColor = { 204.0f / 255.0f, 1.0f, 58.0f / 255.0f };
}

void MenuButton::EndStart()
{

	Renderer->ChangeAnimation("Null");
	ButtonText->SetText("Galmuri14", ButtonName, 15.0f, float4::WHITE, Flag);
	IconRenderer->GetColorData().MulColor = { 255.0f / 204.0f, 1.0f, 255.0f / 58.0f };


	//if (false == IsSelect)
	//{
	//	Renderer->ChangeAnimation("Null");
	//}
	//else if (true == IsSelect)
	//{
	//	Renderer->ChangeAnimation("Slect");
	//}
}

void MenuButton::ClickStart()
{
	UI_Button::ClickStart();
	ButtonText->SetText("Galmuri14", ButtonName, 15.0f, float4::WHITE, Flag);

	Renderer->ChangeAnimation("Slect");

	if (false == IsSelect)
	{
		IsSelect = true;
	}
}