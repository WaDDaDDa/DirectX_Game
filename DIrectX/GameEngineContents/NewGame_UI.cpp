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
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	NewGameBoxRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);

	NewGameBoxRenderer->SetSprite("new_game_ui_bg.png");
	NewGameBoxRenderer->AutoSpriteSizeOn();
	NewGameBoxRenderer->SetAutoScaleRatio(2.0f);
}

void NewGame_UI::Update(float _Delta)
{

}
