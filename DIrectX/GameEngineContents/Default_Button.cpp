#include "PreCompile.h"
#include "Default_Button.h"


Default_Button::Default_Button()
{

}

Default_Button::~Default_Button()
{

}


void Default_Button::Start()
{
	UI_Button::Start();
	float4 TeamLogoColScale = { 140.0f , 45.0f };
	SetButtonColScale(TeamLogoColScale);
	Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("Null", "DefaultButton", 0.1f, 0, 0, false);
	Renderer->CreateAnimation("Null_Stay", "DefaultButton", 0.1f, 1, 1, false);
	Renderer->CreateAnimation("Important", "DefaultButton", 0.1f, 6, 6, false);
	Renderer->CreateAnimation("Important_Stay", "DefaultButton", 0.1f, 7, 7, false);
	Renderer->ChangeAnimation("Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);

	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
}

void Default_Button::IdleStart()
{
	if (false == IsImportant)
	{
		Renderer->ChangeAnimation("Null");
	}
	else if (true == IsImportant)
	{
		Renderer->ChangeAnimation("Important");
	}
}

void Default_Button::StayStart()
{
	if (false == IsImportant)
	{
		Renderer->ChangeAnimation("Null_Stay");
	}
	else if (true == IsImportant)
	{
		Renderer->ChangeAnimation("Important_Stay");
	}
}

void Default_Button::EndStart()
{
	if (false == IsImportant)
	{
		Renderer->ChangeAnimation("Null");
	}
	else if (true == IsImportant)
	{
		Renderer->ChangeAnimation("Important");
	}
}

void Default_Button::ClickStart()
{
	UI_Button::ClickStart();

	if (false == IsImportant)
	{
		IsImportant = true;
	}
}
