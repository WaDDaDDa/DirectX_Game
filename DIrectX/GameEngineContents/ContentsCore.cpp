#include "PreCompile.h"
#include "ContentsCore.h"
#include "ContentsControlWindow.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

// ����
#include "IntroLevel.h"
#include "PlayLevel.h"
#include "BanPickLevel.h"
#include "BattleLevel.h"
#include "MainLevel.h"
#include "StadiumLevel.h"
#include "ContentResources.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	ContentResources::ContentResourcesInit();

	GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");
	GameEngineGUI::CreateGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	GameEngineCore::CreateLevel<IntroLevel>("IntroLevel");
	GameEngineCore::CreateLevel<MainLevel>("MainLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<BanPickLevel>("BanPickLevel");
	GameEngineCore::CreateLevel<BattleLevel>("BattleLevel");
	GameEngineCore::CreateLevel<StadiumLevel>("StadiumLevel");
	GameEngineCore::ChangeLevel("BanPickLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}