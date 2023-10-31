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

void MenuButton::IdleStart()
{
	Renderer->ChangeAnimation("Null");
}

void MenuButton::StayStart()
{
	Renderer->ChangeAnimation("Null_Stay");
}

void MenuButton::EndStart()
{

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

void MenuButton::ClickStart()
{
	UI_Button::ClickStart();

	Renderer->ChangeAnimation("Slect");

	if (false == IsSelect)
	{
		IsSelect = true;
	}
}