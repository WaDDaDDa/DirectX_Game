#include "PreCompile.h"
#include "ContentsCore.h"
#include "ContentsControlWindow.h"

// ·¹º§
#include "IntroLevel.h"
#include "PlayLevel.h"
#include "BanPickLevel.h"
#include "BattleLevel.h"
#include "MainLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");

	GameEngineCore::CreateLevel<IntroLevel>("IntroLevel");
	GameEngineCore::CreateLevel<MainLevel>("MainLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<BanPickLevel>("BanPickLevel");
	GameEngineCore::CreateLevel<BattleLevel>("BattleLevel");
	GameEngineCore::ChangeLevel("MainLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}