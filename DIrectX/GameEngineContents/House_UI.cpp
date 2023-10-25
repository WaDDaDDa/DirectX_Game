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



}

void House_UI::Update(float _Delta)
{
	
}
