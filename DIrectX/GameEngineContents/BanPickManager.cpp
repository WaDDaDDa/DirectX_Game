#include "PreCompile.h"
#include "BanPickManager.h"
#include "GameUnit.h"

// UI
#include "BanPickBoard.h"
#include "UI_Mouse.h"

// GameUnit
#include "BanPickCard.h"

BanPickInfo BanPickInfo::Info;

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
		UnitImage->CreateAnimation(Card[i]->GetUnitNameToString() += "_Idle", Card[i]->GetUnitNameToString() += "CardAni", 0.1f, 0, 0, false);
	}

	CurCard = Card[0];

	UnitImage->AutoSpriteSizeOn();
	UnitImage->SetAutoScaleRatio(2.0f);
	UnitImage->Transform.AddLocalPosition(UnitImagePos);
	UnitImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitImage->ChangeAnimation(CurCard->GetUnitNameToString() += "_Idle");

	UnitSkillImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitSkillImage->AutoSpriteSizeOn();
	UnitSkillImage->SetAutoScaleRatio(2.0f);
	UnitSkillImage->Transform.AddLocalPosition(UnitSkillImagePos);
	UnitSkillImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitSkillImage->SetSprite(CurCard->GetUnitNameToString() += "_skill.png");

	UnitUltImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitUltImage->AutoSpriteSizeOn();
	UnitUltImage->SetAutoScaleRatio(2.0f);
	UnitUltImage->Transform.AddLocalPosition(UnitUltImagePos);
	UnitUltImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitUltImage->SetSprite(CurCard->GetUnitNameToString() += "_ult.png");

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

	// 아이콘
	UniAttIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UniAttIcon->SetSprite("ingame_stat_icon_0.png");
	UniAttIcon->AutoSpriteSizeOn();
	UniAttIcon->SetAutoScaleRatio(2.0f);
	UniAttIcon->Transform.AddLocalPosition(UnitAttIconPos);
	UniAttIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UniAttIcon->SetPivotType(PivotType::LeftTop);

	UniAttSpeedIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UniAttSpeedIcon->SetSprite("ingame_stat_icon_5.png");
	UniAttSpeedIcon->AutoSpriteSizeOn();
	UniAttSpeedIcon->SetAutoScaleRatio(2.0f);
	UniAttSpeedIcon->Transform.AddLocalPosition(UnitAttSpeedIconPos);
	UniAttSpeedIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UniAttSpeedIcon->SetPivotType(PivotType::LeftTop);

	UniAttRangeIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UniAttRangeIcon->SetSprite("ingame_stat_icon_3.png");
	UniAttRangeIcon->AutoSpriteSizeOn();
	UniAttRangeIcon->SetAutoScaleRatio(2.0f);
	UniAttRangeIcon->Transform.AddLocalPosition(UnitAttRangeIconPos);
	UniAttRangeIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UniAttRangeIcon->SetPivotType(PivotType::LeftTop);

	UniDefIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UniDefIcon->SetSprite("ingame_stat_icon_1.png");
	UniDefIcon->AutoSpriteSizeOn();
	UniDefIcon->SetAutoScaleRatio(2.0f);
	UniDefIcon->Transform.AddLocalPosition(UnitDefIconPos);
	UniDefIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UniDefIcon->SetPivotType(PivotType::LeftTop);

	UniHpIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UniHpIcon->SetSprite("ingame_stat_icon_2.png");
	UniHpIcon->AutoSpriteSizeOn();
	UniHpIcon->SetAutoScaleRatio(2.0f);
	UniHpIcon->Transform.AddLocalPosition(UnitHpIconPos);
	UniHpIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UniHpIcon->SetPivotType(PivotType::LeftTop);

	UniSpeedIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UniSpeedIcon->SetSprite("ingame_stat_icon_4.png");
	UniSpeedIcon->AutoSpriteSizeOn();
	UniSpeedIcon->SetAutoScaleRatio(2.0f);
	UniSpeedIcon->Transform.AddLocalPosition(UnitSpeedIconPos);
	UniSpeedIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UniSpeedIcon->SetPivotType(PivotType::LeftTop);

	SkillTimeIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	SkillTimeIcon->SetSprite("patch_icons_1.png");
	SkillTimeIcon->AutoSpriteSizeOn();
	SkillTimeIcon->SetAutoScaleRatio(2.0f);
	SkillTimeIcon->Transform.AddLocalPosition(SkillTimeIconPos);
	SkillTimeIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UltTimeIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UltTimeIcon->SetSprite("patch_icons_1.png");
	UltTimeIcon->AutoSpriteSizeOn();
	UltTimeIcon->SetAutoScaleRatio(2.0f);
	UltTimeIcon->Transform.AddLocalPosition(UltTimeIconPos);
	UltTimeIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	// 블루팀 벤 틀
	BlueBan = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	BlueBan->CreateAnimation("BlueBan", "BanPick", 0.1f, 8, 8, false);
	BlueBan->AutoSpriteSizeOn();
	BlueBan->ChangeAnimation("BlueBan");
	BlueBan->SetAutoScaleRatio(2.0f);
	BlueBan->Transform.AddLocalPosition(BlueBanPos);
	BlueBan->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	// 블루팀 벤 아이콘
	BlueBanIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	BlueBanIcon->CreateAnimation("BanIcon", "BanPick", 0.1f, 5, 5, false);
	BlueBanIcon->AutoSpriteSizeOn();
	BlueBanIcon->ChangeAnimation("BanIcon");
	BlueBanIcon->SetAutoScaleRatio(2.0f);
	BlueBanIcon->Transform.AddLocalPosition(BlueBanIconPos);
	BlueBanIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });

	// 블루팀 유닛
	BlueBanUnit = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	for (size_t i = 0; i < UnitCount; i++)
	{
		BlueBanUnit->CreateAnimation(Card[i]->GetUnitNameToString() += "_Idle", Card[i]->GetUnitNameToString() += "CardAni", 0.1f, 0, 0, false);
	}
	BlueBanUnit->AutoSpriteSizeOn();
	BlueBanUnit->ChangeAnimation(CurCard->GetUnitNameToString() += "_Idle");
	BlueBanUnit->SetAutoScaleRatio(2.0f);
	BlueBanUnit->Transform.AddLocalPosition(BlueBanUnitPos);
	BlueBanUnit->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });

	// 레드팀 벤 틀
	RedBan = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	RedBan->CreateAnimation("BlueBan", "BanPick", 0.1f, 8, 8, false);
	RedBan->AutoSpriteSizeOn();
	RedBan->ChangeAnimation("BlueBan");
	RedBan->SetAutoScaleRatio(2.0f);
	RedBan->Transform.AddLocalPosition(RedBanPos);
	RedBan->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	// 레드팀 벤 아이콘
	RedBanIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	RedBanIcon->CreateAnimation("BanIcon", "BanPick", 0.1f, 5, 5, false);
	RedBanIcon->AutoSpriteSizeOn();
	RedBanIcon->ChangeAnimation("BanIcon");
	RedBanIcon->SetAutoScaleRatio(2.0f);
	RedBanIcon->Transform.AddLocalPosition(RedBanIconPos);
	RedBanIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });

	// 레드팀 유닛
	RedBanUnit = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	for (size_t i = 0; i < UnitCount; i++)
	{
		RedBanUnit->CreateAnimation(Card[i]->GetUnitNameToString() += "_Idle", Card[i]->GetUnitNameToString() += "CardAni", 0.1f, 0, 0, false);
	}
	RedBanUnit->AutoSpriteSizeOn();
	RedBanUnit->ChangeAnimation(CurCard->GetUnitNameToString() += "_Idle");
	RedBanUnit->SetAutoScaleRatio(2.0f);
	RedBanUnit->Transform.AddLocalPosition(RedBanUnitPos);
	RedBanUnit->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BlueBanUnit->Off();
	RedBanUnit->Off();

	// 현재 턴 컬러.
	TurnColor = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	TurnColor->CreateAnimation("Blue", "BanPick", 0.1f, 30, 30, false);
	TurnColor->CreateAnimation("Red", "BanPick", 0.1f, 31, 31, false);
	TurnColor->ChangeAnimation("Blue");
	TurnColor->SetImageScale({1280.0f, 60.0f});
	TurnColor->Transform.AddLocalPosition(TurnColorPos);
	TurnColor->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });

}


void BanPickManager::LevelStart(GameEngineLevel* _PrevLevel)
{
	BanPickInfo::Info.Clear();
	ChangeState(BanPickState::Idle);
}

void BanPickManager::Update(float _Delta)
{
	// CurCard셋팅하는거.
	for (size_t i = 0; i < UnitCount; i++)
	{
		if (true == Card[i]->IsStart)
		{
			CardValueReset();
			CurCard = Card[i];
		}
	}

	if (TeamType::Blue == UI_Mouse::GameMouse->GetPlayerTeam())
	{
		TurnColor->ChangeAnimation("Blue");

	}
	else if (TeamType::Red == UI_Mouse::GameMouse->GetPlayerTeam())
	{
		TurnColor->ChangeAnimation("Red");

	}

	UnitImage->ChangeAnimation(CurCard->GetUnitNameToString() += "_Idle");
	UnitSkillImage->SetSprite(CurCard->GetUnitNameToString() += "_skill.png");
	UnitUltImage->SetSprite(CurCard->GetUnitNameToString() += "_ult.png");

	StateUpdate(_Delta);
}

void BanPickManager::ChangeState(BanPickState _State)
{

	if (_State != State)
	{
		switch (_State)
		{
		case BanPickState::Idle:
			IdleStart();
			break;
		case BanPickState::ChangeBan:
			ChangeBanStart();
			break;
		case BanPickState::Ban:
			BanStart();
			break;
		case BanPickState::Pick:
			PickStart();
			break;
		case BanPickState::ChangePick:
			ChangePickStart();
			break;
		case BanPickState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void BanPickManager::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BanPickState::Idle:
		return IdleUpdate(_Delta);
	case BanPickState::ChangeBan:
		return ChangeBanUpdate(_Delta);
	case BanPickState::Ban:
		return BanUpdate(_Delta);
	case BanPickState::ChangePick:
		return ChangePickUpdate(_Delta);
	case BanPickState::Pick:
		return PickUpdate(_Delta);
	case BanPickState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void BanPickManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BanPickManager::IdleStart()
{

}

void BanPickManager::IdleUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(BanPickState::ChangeBan);
		return;
	}
}

void BanPickManager::ChangeBanStart()
{

}

void BanPickManager::ChangeBanUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(BanPickState::Ban);
		return;
	}
}

void BanPickManager::BanStart()
{

}

void BanPickManager::BanUpdate(float _Delta)
{
	// 처음 들어온 카드 설정
	for (size_t i = 0; i < UnitCount; i++)
	{

		// 벤 구간
		if (true == Card[i]->IsPick && 2 > BanCount)
		{
			CurCard->SetBan();

			if (0 == BanCount)
			{
				BlueBanUnit->ChangeAnimation(CurCard->GetUnitNameToString() += "_Idle");
				BlueBanUnit->On();
			}

			if (1 == BanCount)
			{
				RedBanUnit->ChangeAnimation(CurCard->GetUnitNameToString() += "_Idle");
				RedBanUnit->On();
			}
			BanCount++;
			UI_Mouse::GameMouse->TeamSwitch();
			Card[i]->IsPick = false;
		}
	}

	if (2 == BanCount)
	{
		ChangeState(BanPickState::ChangePick);
		return;
	}

}

void BanPickManager::ChangePickStart()
{

}

void BanPickManager::ChangePickUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(BanPickState::Pick);
		return;
	}
}

void BanPickManager::PickStart()
{

}

void BanPickManager::PickUpdate(float _Delta)
{
	// 처음 들어온 카드 설정
	for (size_t i = 0; i < UnitCount; i++)
	{
		// 챔피언 픽 구간
		if (true == Card[i]->IsPick)
		{
			if (TeamType::Blue == UI_Mouse::GameMouse->GetPlayerTeam())
			{
				BanPickInfo::Info.BlueTeamPick[BluePickCount] = CurCard->GetUnitName();
				CurCard->SetPickNum(BluePickCount);
				BluePickCount++;
			}
			else if (TeamType::Red == UI_Mouse::GameMouse->GetPlayerTeam())
			{
				BanPickInfo::Info.RedTeamPick[RedPickCount] = CurCard->GetUnitName();
				CurCard->SetPickNum(RedPickCount);
				RedPickCount++;
			}

			UI_Mouse::GameMouse->TeamSwitch();
			Card[i]->IsPick = false;
		}
	}

	if (2 == BluePickCount && 2 == RedPickCount)
	{
		GameEngineCore::ChangeLevel("BattleLevel");
		return;
	}
}