#include "PreCompile.h"
#include "ProceedButton.h"


ProceedButton::ProceedButton()
{

}

ProceedButton::~ProceedButton()
{

}

void ProceedButton::Start()
{
	UI_Button::Start();
	float4 TeamLogoColScale = { 130.0f , 40.0f };
	SetButtonColScale(TeamLogoColScale);
	//Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("Null", "MainUI", 0.1f, 12, 12, false);
	Renderer->CreateAnimation("Null_Stay", "MainUI", 0.1f, 13, 13, false);
	Renderer->ChangeAnimation("Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.2f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	Arrow = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	Arrow->CreateAnimation("Slect", "MainUI", 0.1f,14, 14, false);
	Arrow->ChangeAnimation("Slect");
	Arrow->AutoSpriteSizeOn();
	Arrow->SetAutoScaleRatio(2.2f);
	Arrow->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	Arrow->Transform.AddLocalPosition({ 70.0f});

}

void ProceedButton::LevelEnd(GameEngineLevel* _NextLevel)
{

}


void ProceedButton::IdleStart()
{
	Renderer->ChangeAnimation("Null");
	ButtonText->SetText("Galmuri14", ButtonName, 20.0f, float4::ZERO, Flag);

}

void ProceedButton::StayStart()
{
	Renderer->ChangeAnimation("Null_Stay");
	ButtonText->SetText("Galmuri14", ButtonName, 20.0f, float4::WHITE, Flag);
	Arrow->Transform.AddLocalPosition({ 0.0f });
	ArrowDelta = 0.0f;
}

void ProceedButton::StayUpdate(float _Delta)
{
	ArrowDelta += _Delta * 3.0f;

	if (1.0f > ArrowDelta)
	{
		float Test = std::lerp(50.0f, 70.0f, ArrowDelta);
		Arrow->Transform.SetLocalPosition({ Test, Arrow->Transform.GetLocalPosition().Y, Arrow->Transform.GetLocalPosition().Z });

	}
	else if (1.0f <= ArrowDelta)
	{
		Arrow->Transform.SetLocalPosition({ 70.0f, Arrow->Transform.GetLocalPosition().Y, Arrow->Transform.GetLocalPosition().Z });
	}
	
	if (2.0f <= ArrowDelta)
	{
		ArrowDelta = 0.0f;
	}

}


void ProceedButton::EndStart()
{
	ButtonText->SetText("Galmuri14", ButtonName, 20.0f, float4::ZERO, Flag);

	Renderer->ChangeAnimation("Null");
	Arrow->Transform.SetLocalPosition({ 70.0f, Arrow->Transform.GetLocalPosition().Y, Arrow->Transform.GetLocalPosition().Z });


	//if (false == IsSelect)
	//{
	//	Renderer->ChangeAnimation("Null");
	//}
	//else if (true == IsSelect)
	//{
	//	Renderer->ChangeAnimation("Slect");
	//}
}

void ProceedButton::ClickStart()
{
	UI_Button::ClickStart();

	Renderer->ChangeAnimation("Slect");
	ButtonText->SetText("Galmuri14", ButtonName, 20.0f, float4::WHITE, Flag);

	if (false == IsSelect)
	{
		IsSelect = true;
	}
}