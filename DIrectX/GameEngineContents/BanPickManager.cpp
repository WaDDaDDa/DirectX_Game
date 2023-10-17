#include "PreCompile.h"
#include "BanPickManager.h"
#include "GameUnit.h"

// UI
#include "BanPickBoard.h"
#include "UI_Mouse.h"

// GameUnit
#include "BanPickCard.h"

BanPickManager::BanPickManager()
{

}

BanPickManager::~BanPickManager()
{

}

void BanPickManager::CardIntit()
{
	for (size_t i = 0; i < UnitCount; i++)
	{
		Card[i]->Init(i);
	}
}

void BanPickManager::Start()
{
	GameMouse = GetLevel()->CreateActor<UI_Mouse>();
	GameBoard = GetLevel()->CreateActor<BanPickBoard>();

	for (size_t i = 0; i < UnitCount; i++)
	{
		Card.push_back(GetLevel()->CreateActor<BanPickCard>());
	}

	CardIntit();
}


void BanPickManager::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void BanPickManager::Update(float _Delta)
{

}

void BanPickManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}