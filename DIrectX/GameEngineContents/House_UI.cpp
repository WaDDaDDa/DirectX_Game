#include "PreCompile.h"
#include "House_UI.h"
#include "SlotButton.h"
#include "GreenArrow.h"

House_UI::House_UI()
{

}

House_UI::~House_UI()
{

}

void House_UI::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 200.0f });

	// Çì´õ
	HeaderRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	HeaderRenderer->SetSprite("MainUI", 0);
	HeaderRenderer->AutoSpriteSizeOn();
	HeaderRenderer->SetAutoScaleRatio(2.0f);
	HeaderRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });
	HeaderRenderer->Transform.AddLocalPosition({ 0.0f, 325.0f });


}

void House_UI::Update(float _Delta)
{
	
}
