#include "PreCompile.h"
#include "GreenArrow.h"


GreenArrow::GreenArrow()
{

}

GreenArrow::~GreenArrow()
{

}

void GreenArrow::Start()
{
	UI_Button::Start();
	float4 TeamLogoColScale = { 20.0f , 30.0f };
	SetButtonColScale(TeamLogoColScale);
	Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("Left_Null", "GreenArrow", 0.1f, 0, 0, false);
	Renderer->CreateAnimation("Left_Null_Stay", "GreenArrow", 0.1f, 1, 1, false);
	Renderer->CreateAnimation("Right_Null", "GreenArrow", 0.1f, 3, 3, false);
	Renderer->CreateAnimation("Right_Null_Stay", "GreenArrow", 0.1f, 4, 4, false);
	Renderer->ChangeAnimation("Left_Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);

	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
}

void GreenArrow::IdleStart()
{
	if (false == Dir)
	{
		Renderer->ChangeAnimation("Left_Null");
	}
	else if (true == Dir)
	{
		Renderer->ChangeAnimation("Right_Null");
	}
}

void GreenArrow::StayStart()
{
	if (false == Dir)
	{
		Renderer->ChangeAnimation("Left_Null_Stay");
	}
	else if (true == Dir)
	{
		Renderer->ChangeAnimation("Right_Null_Stay");
	}
}

void GreenArrow::EndStart()
{
	if (false == Dir)
	{
		Renderer->ChangeAnimation("Left_Null");
	}
	else if (true == Dir)
	{
		Renderer->ChangeAnimation("Right_Null");
	}
}

void GreenArrow::ClickStart()
{

}
