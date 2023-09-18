#include "PreCompile.h"
#include "ContentsCore.h"

// ·¹º§
#include "IntroLevel.h"
#include "PlayLevel.h"
#include "BattleLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<IntroLevel>("IntroLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<BattleLevel>("BattleLevel");
	GameEngineCore::ChangeLevel("BattleLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}