#include "PreCompile.h"
#include "NinjaUlt.h"
#include "GameUnitUI.h"


NinjaUlt::NinjaUlt()
{

}

NinjaUlt::~NinjaUlt()
{

}

void NinjaUlt::Start()
{
	Ninja::Start();

	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Ninja_Idle", "NinjaAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Ninja_Move", "NinjaAni", 0.2f, 5, 12);
		MainSpriteRenderer->CreateAnimation("Ninja_Attack", "NinjaAni", 0.2f, 13, 14, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Attack2", "NinjaAni", 0.2f, 15, 17, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Skill", "NinjaAni", 0.05f, 28, 35, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Skill2", "NinjaAni", 0.1f, 36, 38, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Ult", "NinjaAni", 0.2f, 44, 49, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Die", "NinjaAni", 0.1f, 18, 27, false);

		MainSpriteRenderer->FindAnimation("Ninja_Skill2")->Inter[2] = 0.2;

		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("NinjaSkillEffect", "NinjaEffect", 0.05f, 7, 13, false);
		SkillEffectRenderer->CreateAnimation("NinjaSkillBlack", "NinjaEffect", 0.1f, 0, 0, false);
		SkillEffectRenderer->CreateAnimation("NinjaUltEffect", "NinjaEffect", 0.2f, 22, 27, false);
		SkillEffectRenderer->ChangeAnimation("NinjaSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);
		SkillEffectRenderer->Transform.AddLocalPosition({ 0, -20.0f });
		SkillEffectRenderer->SetPivotType(PivotType::Bottom);

		MainSpriteRenderer->ChangeAnimation("Ninja_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	ChangeState(GameUnitState::Spwan);
	UseUlt = true;
}

void NinjaUlt::Update(float _Delta)
{
	UnitHP -= 10.0f * _Delta;
	GameUnit::Update(_Delta);
}

void NinjaUlt::SpwanStart()
{
	Ninja::SpwanStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Ult");

}


void NinjaUlt::DieStart()
{
	Death();
}
