#include "PreCompile.h"
#include "HeaderInfo.h"

HeaderInfo::HeaderInfo()
{

}

HeaderInfo::~HeaderInfo()
{

}

void HeaderInfo::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 0.0f, 0.0f , 100.0f });

	BackGround = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	BackGround->CreateAnimation("Null", "MainUI", 0.1f, 16, 16, false);
	BackGround->ChangeAnimation("Null");
	BackGround->SetImageScale({220.0f, 50.0f});

	BackGround->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
}

void HeaderInfo::Update(float _Delta)
{

}