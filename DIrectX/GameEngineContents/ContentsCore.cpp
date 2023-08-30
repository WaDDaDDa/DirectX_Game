#include "PreCompile.h"
#include "ContentsCore.h"

// ����
#include "IntroLevel.h"
#include "PlayLevel.h"

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
	GameEngineCore::ChangeLevel("IntroLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}