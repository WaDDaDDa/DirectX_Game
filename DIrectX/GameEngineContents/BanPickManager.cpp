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
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		Card[i]->Init(i);
	}
}

void BanPickManager::CardValueReset()
{
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		Card[i]->IsStart = false;
	}
}


void BanPickManager::Start()
{
	GameBoard = GetLevel()->CreateActor<BanPickBoard>();

	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		Card.push_back(GetLevel()->CreateActor<BanPickCard>());
	}

	CardIntit();

	UnitImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		UnitImage->CreateAnimation(Card[i]->GetUnitNameToString() += "_Idle", Card[i]->GetUnitNameToString() += "CardAni", 0.1f, 0, 0, false);
	}

	CurCard = Card[0];

	// 캐릭터 카드 생성. 내선수, 적선수 반복 해야함.
	// GetLevel()->CreateActor<CharacterCard>();

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

	// SkillText
	SkillText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	SkillText->SetText("Galmuri14", "기술", 16.0f, float4::WHITE, FW1_CENTER);
	SkillText->Transform.AddLocalPosition(SkillTextPos);
	SkillText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	
	UnitSkillText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//UnitSkillText->SetText("Galmuri14", CurCard->UnitStat.SkillText.data(), 12.0f, float4::WHITE, FW1_LEFT);
	UnitSkillText->Transform.AddLocalPosition(UnitSkillTextPos);
	UnitSkillText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	// UltText
	UltText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UltText->SetText("Galmuri14", "궁극기", 16.0f, float4::WHITE, FW1_CENTER);
	UltText->Transform.AddLocalPosition(UltTextPos);
	UltText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UnitUltText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//UnitUltText->SetText("Galmuri14", CurCard->UnitStat.UltText.data(), 12.0f, float4::WHITE, FW1_LEFT);
	UnitUltText->Transform.AddLocalPosition(UnitUltTextPos);
	UnitUltText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UnitUltImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitUltImage->AutoSpriteSizeOn();
	UnitUltImage->SetAutoScaleRatio(2.0f);
	UnitUltImage->Transform.AddLocalPosition(UnitUltImagePos);
	UnitUltImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitUltImage->SetSprite(CurCard->GetUnitNameToString() += "_ult.png");

	UnitAttBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UnitAttBox->CreateAnimation("AttBox", "BanPick", 0.1f, 14, 14, false);
	UnitAttBox->AutoSpriteSizeOn();
	UnitAttBox->SetAutoScaleRatio(2.0f);
	UnitAttBox->Transform.AddLocalPosition(UnitAttBoxPos);
	UnitAttBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UnitAttBox->ChangeAnimation("AttBox");
	UnitAttBox->SetPivotType(PivotType::LeftTop);

	UnitAttSpeedBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UnitAttSpeedBox->CreateAnimation("AttSpeedBox", "BanPick", 0.1f, 14, 14, false);
	UnitAttSpeedBox->AutoSpriteSizeOn();
	UnitAttSpeedBox->SetAutoScaleRatio(2.0f);
	UnitAttSpeedBox->Transform.AddLocalPosition(UnitAttSpeedBoxPos);
	UnitAttSpeedBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UnitAttSpeedBox->ChangeAnimation("AttSpeedBox");
	UnitAttSpeedBox->SetPivotType(PivotType::LeftTop);

	UnitAttRangeBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UnitAttRangeBox->CreateAnimation("AttRangeBox", "BanPick", 0.1f, 14, 14, false);
	UnitAttRangeBox->AutoSpriteSizeOn();
	UnitAttRangeBox->SetAutoScaleRatio(2.0f);
	UnitAttRangeBox->Transform.AddLocalPosition(UnitAttRangeBoxPos);
	UnitAttRangeBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UnitAttRangeBox->ChangeAnimation("AttRangeBox");
	UnitAttRangeBox->SetPivotType(PivotType::LeftTop);

	UnitDefBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UnitDefBox->CreateAnimation("DefBox", "BanPick", 0.1f, 14, 14, false);
	UnitDefBox->AutoSpriteSizeOn();
	UnitDefBox->SetAutoScaleRatio(2.0f);
	UnitDefBox->Transform.AddLocalPosition(UnitDefBoxPos);
	UnitDefBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UnitDefBox->ChangeAnimation("DefBox");
	UnitDefBox->SetPivotType(PivotType::LeftTop);

	UnitHpBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UnitHpBox->CreateAnimation("HpBox", "BanPick", 0.1f, 14, 14, false);
	UnitHpBox->AutoSpriteSizeOn();
	UnitHpBox->SetAutoScaleRatio(2.0f);
	UnitHpBox->Transform.AddLocalPosition(UnitHpBoxPos);
	UnitHpBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UnitHpBox->ChangeAnimation("HpBox");
	UnitHpBox->SetPivotType(PivotType::LeftTop);

	UnitSpeedBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	UnitSpeedBox->CreateAnimation("SpeedBox", "BanPick", 0.1f, 14, 14, false);
	UnitSpeedBox->AutoSpriteSizeOn();
	UnitSpeedBox->SetAutoScaleRatio(2.0f);
	UnitSpeedBox->Transform.AddLocalPosition(UnitSpeedBoxPos);
	UnitSpeedBox->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UI) });
	UnitSpeedBox->ChangeAnimation("SpeedBox");
	UnitSpeedBox->SetPivotType(PivotType::LeftTop);

	// 아이콘
	UnitAttIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UnitAttIcon->SetSprite("ingame_stat_icon_0.png");
	UnitAttIcon->AutoSpriteSizeOn();
	UnitAttIcon->SetAutoScaleRatio(2.0f);
	UnitAttIcon->Transform.AddLocalPosition(UnitAttIconPos);
	UnitAttIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UnitAttIcon->SetPivotType(PivotType::LeftTop);

	UnitAttSpeedIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UnitAttSpeedIcon->SetSprite("ingame_stat_icon_5.png");
	UnitAttSpeedIcon->AutoSpriteSizeOn();
	UnitAttSpeedIcon->SetAutoScaleRatio(2.0f);
	UnitAttSpeedIcon->Transform.AddLocalPosition(UnitAttSpeedIconPos);
	UnitAttSpeedIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UnitAttSpeedIcon->SetPivotType(PivotType::LeftTop);

	UnitAttRangeIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UnitAttRangeIcon->SetSprite("ingame_stat_icon_3.png");
	UnitAttRangeIcon->AutoSpriteSizeOn();
	UnitAttRangeIcon->SetAutoScaleRatio(2.0f);
	UnitAttRangeIcon->Transform.AddLocalPosition(UnitAttRangeIconPos);
	UnitAttRangeIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UnitAttRangeIcon->SetPivotType(PivotType::LeftTop);

	UnitDefIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UnitDefIcon->SetSprite("ingame_stat_icon_1.png");
	UnitDefIcon->AutoSpriteSizeOn();
	UnitDefIcon->SetAutoScaleRatio(2.0f);
	UnitDefIcon->Transform.AddLocalPosition(UnitDefIconPos);
	UnitDefIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UnitDefIcon->SetPivotType(PivotType::LeftTop);

	UnitHpIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UnitHpIcon->SetSprite("ingame_stat_icon_2.png");
	UnitHpIcon->AutoSpriteSizeOn();
	UnitHpIcon->SetAutoScaleRatio(2.0f);
	UnitHpIcon->Transform.AddLocalPosition(UnitHpIconPos);
	UnitHpIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UnitHpIcon->SetPivotType(PivotType::LeftTop);

	UnitSpeedIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UnitSpeedIcon->SetSprite("ingame_stat_icon_4.png");
	UnitSpeedIcon->AutoSpriteSizeOn();
	UnitSpeedIcon->SetAutoScaleRatio(2.0f);
	UnitSpeedIcon->Transform.AddLocalPosition(UnitSpeedIconPos);
	UnitSpeedIcon->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });
	UnitSpeedIcon->SetPivotType(PivotType::LeftTop);

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

	// 스탯 제목
	AttText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	AttText->SetText("Galmuri14", "공격력", 16.0f, float4::WHITE, FW1_LEFT);
	AttText->Transform.AddLocalPosition(AttTextPos);
	AttText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	AttSpeedText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	AttSpeedText->SetText("Galmuri14", "공격 속도", 16.0f, float4::WHITE, FW1_LEFT);
	AttSpeedText->Transform.AddLocalPosition(AttSpeedTextPos);
	AttSpeedText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	AttRangeText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	AttRangeText->SetText("Galmuri14", "사거리", 16.0f, float4::WHITE, FW1_LEFT);
	AttRangeText->Transform.AddLocalPosition(AttRangeTextPos);
	AttRangeText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	DefText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	DefText->SetText("Galmuri14", "방어력", 16.0f, float4::WHITE, FW1_LEFT);
	DefText->Transform.AddLocalPosition(DefTextPos);
	DefText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	HpText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	HpText->SetText("Galmuri14", "체력", 16.0f, float4::WHITE, FW1_LEFT);
	HpText->Transform.AddLocalPosition(HpTextPos);
	HpText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	SpeedText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	SpeedText->SetText("Galmuri14", "이동 속도", 16.0f, float4::WHITE, FW1_LEFT);
	SpeedText->Transform.AddLocalPosition(SpeedTextPos);
	SpeedText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	// 유닛 스탯 제목
	UnitAttText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//UnitAttText->SetText("Galmuri14", float4::FloatToString(CurCard->UnitStat.UnitAtt), 16.0f, float4::WHITE, FW1_CENTER);
	UnitAttText->Transform.AddLocalPosition(UnitAttTextPos);
	UnitAttText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UnitAttSpeedText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//UnitAttSpeedText->SetText("Galmuri14", float4::FloatToString(CurCard->UnitStat.AttackSpeed), 16.0f, float4::WHITE, FW1_CENTER);
	UnitAttSpeedText->Transform.AddLocalPosition(UnitAttSpeedTextPos);
	UnitAttSpeedText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UnitAttRangeText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//UnitAttRangeText->SetText("Galmuri14", float4::FloatToString(CurCard->UnitStat.AttackRange.X), 16.0f, float4::WHITE, FW1_CENTER);
	UnitAttRangeText->Transform.AddLocalPosition(UnitAttRangeTextPos);
	UnitAttRangeText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UnitDefText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//UnitDefText->SetText("Galmuri14", float4::FloatToString(CurCard->UnitStat.UnitDef), 16.0f, float4::WHITE, FW1_CENTER);
	UnitDefText->Transform.AddLocalPosition(UnitDefTextPos);
	UnitDefText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UnitHpText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//UnitHpText->SetText("Galmuri14", float4::FloatToString(CurCard->UnitStat.UnitHP), 16.0f, float4::WHITE, FW1_CENTER);
	UnitHpText->Transform.AddLocalPosition(UnitHpTextPos);
	UnitHpText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UnitSpeedText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//UnitSpeedText->SetText("Galmuri14", float4::FloatToString(CurCard->UnitStat.UnitSpeed), 16.0f, float4::WHITE, FW1_CENTER);
	UnitSpeedText->Transform.AddLocalPosition(UnitSpeedTextPos);
	UnitSpeedText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	SkillTimeText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//SkillTimeText->SetText("Galmuri14", float4::FloatToString(CurCard->UnitStat.SkillCooltime) += "초", 16.0f, float4::WHITE, FW1_LEFT);
	SkillTimeText->Transform.AddLocalPosition(SkillTimeTextPos);
	SkillTimeText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

	UltTimeText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	UltTimeText->SetText("Galmuri14", "1회/SET", 16.0f, float4::WHITE, FW1_LEFT);
	UltTimeText->Transform.AddLocalPosition(UltTimeTextPos);
	UltTimeText->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::Text) });

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
	BlueBanUnit->SetMaskTexture("TestMask.png", MaskMode::DynamicMask);
	BlueBanUnit->RenderBaseInfoValue.MaskPivot = { 0.0f, 35.0f };
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
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
	RedBanUnit->SetMaskTexture("TestMask.png", MaskMode::DynamicMask);
	RedBanUnit->RenderBaseInfoValue.MaskPivot = { 0.0f, 35.0f };
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
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

	// 블루벤 유닛이름
	BlueBanUnitText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	BlueBanUnitText->Transform.AddLocalPosition(BlueBanUnitTextPos);
	BlueBanUnitText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	BlueBanUnitText->Off();

	// 레드벤 유닛이름
	RedBanUnitText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	RedBanUnitText->Transform.AddLocalPosition(RedBanUnitTextPos);
	RedBanUnitText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	RedBanUnitText->Off();
	
	BansText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	BansText->Transform.AddLocalPosition(BansTextPos);
	BansText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	BansText->SetText("Galmuri14", "BANS", 40.0f, float4::WHITE, FW1_CENTER);

	// 현재 턴 컬러.
	TurnColor = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	TurnColor->CreateAnimation("Blue", "BanPick", 0.1f, 30, 30, false);
	TurnColor->CreateAnimation("Red", "BanPick", 0.1f, 31, 31, false);
	TurnColor->ChangeAnimation("Blue");
	TurnColor->SetImageScale({1280.0f, 60.0f});
	TurnColor->Transform.AddLocalPosition(TurnColorPos);
	TurnColor->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });

	NoticeText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	NoticeText->Transform.AddLocalPosition({ 640.0f, -110.0f, -static_cast<float>(ContentsOrder::UI) });
	NoticeText->SetText("Galmuri14", "금지할 챔피언을 선택하세요", 32.0f, float4::WHITE, FW1_CENTER);

}


void BanPickManager::LevelStart(GameEngineLevel* _PrevLevel)
{
	BanPickInfo::Info.Clear();
	ChangeState(BanPickState::Idle);
}

void BanPickManager::Update(float _Delta)
{
	// CurCard셋팅하는거.
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		if (true == Card[i]->IsStart && false == Cputurn)
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

	UnitSkillText->SetText("Galmuri14", CurCard->UnitStat.SkillText.data(), 16.0f, float4::WHITE, FW1_LEFT);
	UnitUltText->SetText("Galmuri14", CurCard->UnitStat.UltText.data(), 16.0f, float4::WHITE, FW1_LEFT);
	// 유닛 스탯 제목
	std::string AttText = GameEngineString::Format("{:.0f}", CurCard->UnitStat.UnitAtt);
	std::string AttSpeedText = GameEngineString::Format("{:.1f}", CurCard->UnitStat.AttackSpeed);
	std::string AttRangeText = GameEngineString::Format("{:.0f}", CurCard->UnitStat.AttackRange.X);
	std::string DefText = GameEngineString::Format("{:.0f}", CurCard->UnitStat.UnitDef);
	std::string HpText = GameEngineString::Format("{:.0f}", CurCard->UnitStat.UnitHP);
	std::string SpeedText = GameEngineString::Format("{:.0f}", CurCard->UnitStat.UnitSpeed);
	std::string CoolTimeText = GameEngineString::Format("{:.0f}", CurCard->UnitStat.SkillCooltime);

	UnitAttText->SetText("Galmuri14", AttText, 16.0f, float4::WHITE, FW1_CENTER);
	UnitAttSpeedText->SetText("Galmuri14", AttSpeedText, 16.0f, float4::WHITE, FW1_CENTER);
	UnitAttRangeText->SetText("Galmuri14", AttRangeText, 16.0f, float4::WHITE, FW1_CENTER);
	UnitDefText->SetText("Galmuri14", DefText, 16.0f, float4::WHITE, FW1_CENTER);
	UnitHpText->SetText("Galmuri14", HpText, 16.0f, float4::WHITE, FW1_CENTER);
	UnitSpeedText->SetText("Galmuri14", SpeedText, 16.0f, float4::WHITE, FW1_CENTER);
	SkillTimeText->SetText("Galmuri14", CoolTimeText += "초", 16.0f, float4::WHITE, FW1_LEFT);

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
		case BanPickState::BlueBan:
			BlueBanStart();
			break;
		case BanPickState::RedBan:
			RedBanStart();
			break;
		case BanPickState::BluePick:
			BluePickStart();
			break;
		case BanPickState::RedPick:
			RedPickStart();
			break;
		case BanPickState::ChangePick:
			ChangePickStart();
			break;
		case BanPickState::TurnChange:
			TurnChangeStart();
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
	case BanPickState::BlueBan:
		return BlueBanUpdate(_Delta);
	case BanPickState::RedBan:
		return RedBanUpdate(_Delta);
	case BanPickState::ChangePick:
		return ChangePickUpdate(_Delta);
	case BanPickState::BluePick:
		return BluePickUpdate(_Delta);
	case BanPickState::RedPick:
		return RedPickUpdate(_Delta);
	case BanPickState::TurnChange:
		return TurnChangeUpdate(_Delta);
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
	UI_Mouse::GameMouse->MouseCol->Off();
}

void BanPickManager::IdleUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.5f)
	{
		ChangeState(BanPickState::ChangeBan);
		return;
	}
}

void BanPickManager::ChangeBanStart()
{
	UI_Mouse::GameMouse->MouseCol->Off();

}

void BanPickManager::ChangeBanUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.5f)
	{
		ChangeState(BanPickState::BlueBan);
		return;
	}
}

void BanPickManager::BlueBanStart()
{
	UI_Mouse::GameMouse->MouseCol->On();
	Cputurn = false;

}

void BanPickManager::BlueBanUpdate(float _Delta)
{

	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		// 벤 구간
		if (true == Card[i]->IsPick && 1 > BanCount)
		{
			CurCard->SetBan();

			if (0 == BanCount)
			{
				BlueBanUnit->ChangeAnimation(CurCard->GetUnitNameToString() += "_Idle");
				BlueBanUnit->On();
				BlueBanUnitText->SetText("Galmuri14", CurCard->UnitStat.KoreaName.data(), 12.0f, float4::WHITE, FW1_CENTER);
				BlueBanUnitText->On();
			}

			BanCount++;
			UI_Mouse::GameMouse->TeamSwitch();
			Card[i]->IsPick = false;
		}
	}

	if (1 == BanCount)
	{
		ChangeState(BanPickState::TurnChange);
		return;
	}

}

void BanPickManager::RedBanStart()
{
	UI_Mouse::GameMouse->MouseCol->Off();
	Cputurn = true;
}

void BanPickManager::RedBanUpdate(float _Delta)
{
	// 처음 들어온 카드 설정

	if (true == Cputurn)
	{
		GameEngineRandom Rand;
		int CardNum = Rand.RandomInt(0, UnitCount - 1);
		while (false != Card[static_cast<size_t>(CardNum)]->IsSelect)
		{
			CardNum = Rand.RandomInt(0, UnitCount -1);
		}

		Card[static_cast<size_t>(CardNum)]->IsPick = true;
		CurCard = Card[static_cast<size_t>(CardNum)];
	}

	
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		// 벤 구간
		if (true == Card[i]->IsPick && 2 > BanCount)
		{
			CurCard->SetBan();

			if (1 == BanCount)
			{
				RedBanUnit->ChangeAnimation(CurCard->GetUnitNameToString() += "_Idle");
				RedBanUnit->On();
				RedBanUnitText->SetText("Galmuri14", CurCard->UnitStat.KoreaName.data(), 12.0f, float4::WHITE, FW1_CENTER);
				RedBanUnitText->On();
			}

			BanCount++;
			UI_Mouse::GameMouse->TeamSwitch();
			Card[i]->IsPick = false;
			Card[i]->IsSelect = true;

		}
	}

	if (2 == BanCount)
	{
		ChangeState(BanPickState::TurnChange);
		return;
	}

}

void BanPickManager::ChangePickStart()
{
	UI_Mouse::GameMouse->MouseCol->Off();
	NoticeText->SetText("Galmuri14", "사용할 챔피언을 선택하세요", 32.0f, float4::WHITE, FW1_CENTER);

}

void BanPickManager::ChangePickUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.5f)
	{
		ChangeState(BanPickState::BluePick);
		return;
	}
}

void BanPickManager::BluePickStart()
{
	UI_Mouse::GameMouse->MouseCol->On();
	Cputurn = false;
}

void BanPickManager::BluePickUpdate(float _Delta)
{
	// 처음 들어온 카드 설정
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		if (true == Card[i]->IsPick)
		{
			if (TeamType::Blue == UI_Mouse::GameMouse->GetPlayerTeam())
			{
				BanPickInfo::Info.BlueTeamPick[BluePickCount] = CurCard->GetUnitName();
				CurCard->SetPickNum(BluePickCount);
				BluePickCount++;
			}

			UI_Mouse::GameMouse->TeamSwitch();
			Card[i]->IsPick = false;

			if (2 >= BluePickCount)
			{
				ChangeState(BanPickState::TurnChange);
				return;
			}
		}
	}

	//if (2 == BluePickCount && 2 == RedPickCount)
	//{
	//	GameEngineCore::ChangeLevel("BattleLevel");
	//	return;
	//}
}

void BanPickManager::RedPickStart()
{
	UI_Mouse::GameMouse->MouseCol->Off();
	Cputurn = true;
}

void BanPickManager::RedPickUpdate(float _Delta)
{
	if (true == Cputurn)
	{
		GameEngineRandom Rand;
		int CardNum = Rand.RandomInt(0, UnitCount - 1);
		while (false != Card[CardNum]->IsSelect)
		{
			CardNum = Rand.RandomInt(0, UnitCount - 1);
		}

		Card[CardNum]->IsPick = true;
		CurCard = Card[CardNum]; 
	}

	// 처음 들어온 카드 설정
	for (size_t i = 0; i < static_cast<size_t>(UnitCount); i++)
	{
		if (true == Card[i]->IsPick)
		{
			if (TeamType::Red == UI_Mouse::GameMouse->GetPlayerTeam())
			{
				BanPickInfo::Info.RedTeamPick[RedPickCount] = CurCard->GetUnitName();
				CurCard->SetPickNum(RedPickCount);
				RedPickCount++;
			}

			UI_Mouse::GameMouse->TeamSwitch();
			Card[i]->IsPick = false;
			Card[i]->IsSelect = true;

			if (2 >= RedPickCount)
			{
				ChangeState(BanPickState::TurnChange);
				return;
			}
		}
	}

	//if (2 == BluePickCount && 2 == RedPickCount)
	//{
	//	GameEngineCore::ChangeLevel("BattleLevel");
	//	return;
	//}
}

void BanPickManager::TurnChangeStart()
{
	UI_Mouse::GameMouse->MouseCol->Off();
}

void BanPickManager::TurnChangeUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		if (1 == BanCount)
		{
			ChangeState(BanPickState::RedBan);
			return;
		}

		if (2 == BanCount && 0 == BluePickCount)
		{
			ChangeState(BanPickState::ChangePick);
			return;
		}

		if (1 == BluePickCount && 0 == RedPickCount)
		{
			ChangeState(BanPickState::RedPick);
			return;
		}

		if (1 == BluePickCount && 1 == RedPickCount)
		{
			ChangeState(BanPickState::BluePick);
			return;
		}

		if (2 == BluePickCount && 1 == RedPickCount)
		{
			ChangeState(BanPickState::RedPick);
			return;
		}

		if (2 == BluePickCount && 2 == RedPickCount)
		{
			GameEngineCore::ChangeLevel("BattleLevel");
			return;
		}
	}
	
}