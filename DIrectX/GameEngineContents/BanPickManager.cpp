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

void BanPickManager::CardValueReset()
{
	for (size_t i = 0; i < UnitCount; i++)
	{
		Card[i]->IsStart = false;
	}
}


void BanPickManager::Start()
{
	GameBoard = GetLevel()->CreateActor<BanPickBoard>();

	for (size_t i = 0; i < UnitCount; i++)
	{
		Card.push_back(GetLevel()->CreateActor<BanPickCard>());
	}

	CardIntit();

	UnitImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	for (size_t i = 0; i < UnitCount; i++)
	{
		UnitImage->CreateAnimation(Card[i]->GetUnitName() += "_Idle", Card[i]->GetUnitName() += "CardAni", 0.1f, 0, 0, false);
	}

	CurCard = Card[0];

	UnitImage->AutoSpriteSizeOn();
	UnitImage->SetAutoScaleRatio(2.0f);
	UnitImage->Transform.AddLocalPosition(UnitImagePos);
	UnitImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitImage->ChangeAnimation(CurCard->GetUnitName() += "_Idle");

	UnitSkillImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitSkillImage->AutoSpriteSizeOn();
	UnitSkillImage->SetAutoScaleRatio(2.0f);
	UnitSkillImage->Transform.AddLocalPosition(UnitSkillImagePos);
	UnitSkillImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitSkillImage->SetSprite(CurCard->GetUnitName() += "_skill.png");

	UnitUltImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitUltImage->AutoSpriteSizeOn();
	UnitUltImage->SetAutoScaleRatio(2.0f);
	UnitUltImage->Transform.AddLocalPosition(UnitUltImagePos);
	UnitUltImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitUltImage->SetSprite(CurCard->GetUnitName() += "_ult.png");

	UniAttBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UniAttBox->CreateAnimation("AttBox", "BanPick", 0.1f, 14, 14, false);
	UniAttBox->AutoSpriteSizeOn();
	UniAttBox->SetAutoScaleRatio(2.0f);
	UniAttBox->Transform.AddLocalPosition(UnitAttBoxPos);
	UniAttBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UniAttBox->ChangeAnimation("AttBox");
	UniAttBox->SetPivotType(PivotType::LeftTop);

	UniAttSpeedBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UniAttSpeedBox->CreateAnimation("AttSpeedBox", "BanPick", 0.1f, 14, 14, false);
	UniAttSpeedBox->AutoSpriteSizeOn();
	UniAttSpeedBox->SetAutoScaleRatio(2.0f);
	UniAttSpeedBox->Transform.AddLocalPosition(UnitAttSpeedBoxPos);
	UniAttSpeedBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UniAttSpeedBox->ChangeAnimation("AttSpeedBox");
	UniAttSpeedBox->SetPivotType(PivotType::LeftTop);

	UniAttRangeBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UniAttRangeBox->CreateAnimation("AttRangeBox", "BanPick", 0.1f, 14, 14, false);
	UniAttRangeBox->AutoSpriteSizeOn();
	UniAttRangeBox->SetAutoScaleRatio(2.0f);
	UniAttRangeBox->Transform.AddLocalPosition(UnitAttRangeBoxPos);
	UniAttRangeBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UniAttRangeBox->ChangeAnimation("AttRangeBox");
	UniAttRangeBox->SetPivotType(PivotType::LeftTop);

	UniDefBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UniDefBox->CreateAnimation("DefBox", "BanPick", 0.1f, 14, 14, false);
	UniDefBox->AutoSpriteSizeOn();
	UniDefBox->SetAutoScaleRatio(2.0f);
	UniDefBox->Transform.AddLocalPosition(UnitDefBoxPos);
	UniDefBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UniDefBox->ChangeAnimation("DefBox");
	UniDefBox->SetPivotType(PivotType::LeftTop);

	UniHpBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UniHpBox->CreateAnimation("HpBox", "BanPick", 0.1f, 14, 14, false);
	UniHpBox->AutoSpriteSizeOn();
	UniHpBox->SetAutoScaleRatio(2.0f);
	UniHpBox->Transform.AddLocalPosition(UnitHpBoxPos);
	UniHpBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UniHpBox->ChangeAnimation("HpBox");
	UniHpBox->SetPivotType(PivotType::LeftTop);

	UniSpeedBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UniSpeedBox->CreateAnimation("SpeedBox", "BanPick", 0.1f, 14, 14, false);
	UniSpeedBox->AutoSpriteSizeOn();
	UniSpeedBox->SetAutoScaleRatio(2.0f);
	UniSpeedBox->Transform.AddLocalPosition(UnitSpeedBoxPos);
	UniSpeedBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UniSpeedBox->ChangeAnimation("SpeedBox");
	UniSpeedBox->SetPivotType(PivotType::LeftTop);
}


void BanPickManager::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void BanPickManager::Update(float _Delta)
{
	// 카드의 팀정보 바꾸는것
	for (size_t i = 0; i < UnitCount; i++)
	{
		if (true == Card[i]->IsSelect)
		{
			continue;
		}

		Card[i]->SetPlayerTeam(UI_Mouse::GameMouse->GetPlayerTeam());
	}

	// 처음 들어온 카드 설정
	for (size_t i = 0; i < UnitCount; i++)
	{
		if (CurCard == Card[i])
		{
			continue;
		}

		if (true == Card[i]->IsStart)
		{
			CardValueReset();
			CurCard = Card[i];
		}
	}

	UnitImage->ChangeAnimation(CurCard->GetUnitName() += "_Idle");
	UnitSkillImage->SetSprite(CurCard->GetUnitName() += "_skill.png");
	UnitUltImage->SetSprite(CurCard->GetUnitName() += "_ult.png");

}

void BanPickManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}