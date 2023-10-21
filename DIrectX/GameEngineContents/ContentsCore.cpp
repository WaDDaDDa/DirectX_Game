#include "PreCompile.h"
#include "ContentsCore.h"
#include "ContentsControlWindow.h"

// ����
#include "IntroLevel.h"
#include "PlayLevel.h"
#include "BanPickLevel.h"
#include "BattleLevel.h"

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
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<BanPickLevel>("BanPickLevel");
	GameEngineCore::CreateLevel<BattleLevel>("BattleLevel");
	GameEngineCore::ChangeLevel("IntroLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}