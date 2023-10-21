#include "PreCompile.h"
#include "NewGame_UI.h"


NewGame_UI::NewGame_UI()
{

}

NewGame_UI::~NewGame_UI()
{

}


void NewGame_UI::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	NewGameBoxRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);

	NewGameBoxRenderer->SetSprite("new_game_ui_bg.png");
	NewGameBoxRenderer->AutoSpriteSizeOn();
	NewGameBoxRenderer->SetAutoScaleRatio(2.0f);
	NewGameBoxRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
}

void NewGame_UI::Update(float _Delta)
{

}
