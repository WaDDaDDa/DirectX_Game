#include "PreCompile.h"
#include "GameUnitUI.h"
#include "GameUnit.h"

GameUnitUI::GameUnitUI()
{

}

GameUnitUI::~GameUnitUI()
{

}

void GameUnitUI::Start()
{


}

void GameUnitUI::InitUniUI()
{
	// 궁극기 온/오프 테두리
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::HPLayer1);
	Renderer->CreateAnimation("GameUnitUltOn", "UnitHPBar", 0.1f, 8, 8, false);
	Renderer->CreateAnimation("GameUnitUltOff", "UnitHPBar", 0.1f, 7, 7, false);
	Renderer->ChangeAnimation("GameUnitUltOn");
	Renderer->SetImageScale({ 18.0f,18.0f });
	Renderer->SetPivotType(PivotType::Left);
	Renderer->Transform.AddLocalPosition({ -40.5f, -30.0f });

	// 바탕
	Renderer5 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::HPLayer1);
	Renderer5->CreateAnimation("GameUnitHPLayer1", "UnitHPBar", 0.1f, 0, 0, false);
	Renderer5->ChangeAnimation("GameUnitHPLayer1");
	Renderer5->SetImageScale({ 50.0f,9.0f });
	Renderer5->SetPivotType(PivotType::Left);
	Renderer5->Transform.AddLocalPosition({ -24.0f, -27.0f });

	// mp
	Renderer2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::HPLayer1);
	Renderer2->CreateAnimation("GameUnitHPLayer1", "UnitHPBar", 0.1f, 2, 2, false);
	Renderer2->ChangeAnimation("GameUnitHPLayer1");
	Renderer2->SetImageScale({ 1.0f,3.0f });
	Renderer2->SetPivotType(PivotType::Left);
	Renderer2->Transform.AddLocalPosition({ -24.0f, -30.5f });

	// hp
	Renderer3 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::HPLayer1);
	Renderer3->CreateAnimation("GameUnitHPLayer2Red", "UnitHPBar", 0.1f, 3, 3, false);
	Renderer3->CreateAnimation("GameUnitHPLayer2Blue", "UnitHPBar", 0.1f, 4, 4, false);
	if (Unit->MyTeam == TeamType::Red)
	{
		Renderer3->ChangeAnimation("GameUnitHPLayer2Red");
	}
	else if (Unit->MyTeam == TeamType::Blue)
	{
		Renderer3->ChangeAnimation("GameUnitHPLayer2Blue");
	}
	Renderer3->SetImageScale({ 48.5f,3.0f });
	Renderer3->SetPivotType(PivotType::Left);
	Renderer3->Transform.AddLocalPosition({ -24.0f, -25.0f });

	// 틀
	Renderer4 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::HPLayer1);
	Renderer4->CreateAnimation("GameUnitHPLayer4", "UnitHPBar", 0.1f, 5, 5, false);
	Renderer4->ChangeAnimation("GameUnitHPLayer4");
	Renderer4->SetImageScale({ 50.0f,9.0f });
	Renderer4->SetPivotType(PivotType::Left);
	Renderer4->Transform.AddLocalPosition({ -24.0f, -27.0f });

	// 그림자
	Renderer6 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Renderer6->CreateAnimation("GameUnitShadow", "UnitHPBar", 0.1f, 6, 6, false);
	Renderer6->ChangeAnimation("GameUnitShadow");
	Renderer6->AutoSpriteSizeOn();
	Renderer6->SetAutoScaleRatio(1.3f);
	Renderer6->SetPivotType(PivotType::Bottom);
	Renderer6->Transform.AddLocalPosition({ 0.0f, -22.0f });
	//궁극기 아이콘
	Renderer7 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::HPLayer1);
	Renderer7->SetSprite(Unit->GetUnitName() += "_ult.png");
	Renderer7->SetImageScale({ 12.0f,12.0f });
	Renderer7->Transform.AddLocalPosition({ -31.5f, -30.0f });
}


void GameUnitUI::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void GameUnitUI::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}


void GameUnitUI::Update(float _Delta)
{

	Transform.SetWorldPosition(Unit->Transform.GetWorldPosition());

	{// mp 회복 부분
		MPValue += _Delta / Unit->GetSkillCooltime();
		if (MPValue >= 1.0f)
		{
			MPValue = 1.0f;
		}
		float Test = std::lerp(0.0f, 50.0f, MPValue);
		Renderer2->SetImageScale({ Test, 3.0f });


		if (GameUnitState::Skill == Unit->GetState())
		{
			MPValue = 0.0f;
			Renderer2->SetImageScale({ 0.0f,3.0f });
		}
	}

	{// hp 소모 부분
		float HPrate = Unit->GetHPRate();
		float Test = std::lerp(48.5f, 0.0f, 1.0f - HPrate);
		Renderer3->SetImageScale({ Test, 3.0f });
		if (Unit->GetHP() <= 0.0f)
		{
			Renderer3->SetImageScale({ 0.0f, 3.0f });
		}

		//Renderer3->SetImageScale({ 48.5f,3.0f });
	}

	if (true == Unit->ImDie)
	{
		AllRendererOff();
	}
	else if (false == Unit->ImDie)
	{
		AllRendererOn();
	}

	if (true == Unit->UseUlt)
	{
		Renderer->ChangeAnimation("GameUnitUltOff");
	}
	else if (false == Unit->UseUlt)
	{
		Renderer->ChangeAnimation("GameUnitUltOn");
	}
}