#include "PreCompile.h"
#include "SlotButton.h"


SlotButton::SlotButton()
{

}

SlotButton::~SlotButton()
{

}


void SlotButton::Start()
{
	UI_Button::Start();
	float4 TeamLogoColScale = { 60.0f , 60.0f };
	SetButtonColScale(TeamLogoColScale);
	Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("Null", "ButtonSlot", 0.1f, 0, 0, false);
	Renderer->CreateAnimation("Null_Stay", "ButtonSlot", 0.1f, 1, 1, false);
	Renderer->CreateAnimation("Slect", "ButtonSlot", 0.1f, 2, 2, false);
	Renderer->CreateAnimation("Slect_Stay", "ButtonSlot", 0.1f, 3, 3, false);
	Renderer->ChangeAnimation("Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);

	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
}

void SlotButton::IdleStart()
{
	if (false == IsSelect)
	{
		Renderer->ChangeAnimation("Null");
	}
	else if (true == IsSelect)
	{
		Renderer->ChangeAnimation("Slect");
	}
}

void SlotButton::StayStart()
{
	if (false == IsSelect)
	{
		Renderer->ChangeAnimation("Null_Stay");
	}
	else if (true == IsSelect)
	{
		Renderer->ChangeAnimation("Slect_Stay");
	}
}

void SlotButton::EndStart()
{
	if (false == IsSelect)
	{
		Renderer->ChangeAnimation("Null");
	}
	else if (true == IsSelect)
	{
		Renderer->ChangeAnimation("Slect");
	}
}

void SlotButton::ClickStart()
{
	if (false == IsSelect)
	{
		IsSelect = true;
	}
}
