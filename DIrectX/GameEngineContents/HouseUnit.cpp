#include "PreCompile.h"
#include "HouseUnit.h"


HouseUnit::HouseUnit()
{

}

HouseUnit::~HouseUnit()
{

}

void HouseUnit::Start()
{
	Transform.SetLocalPosition({640.0f, -380.0f, 200.0f});

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	BodyRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	BodyRenderer->SetPivotType(PivotType::Bottom);

	HairRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Hair);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Hair) });
	//HairRenderer->SetPivotType(PivotType::Bottom);

	//Test = [=](const SpriteData& CurSprite, int _SpriteIndex)
	//	{
	//		// 처음한번 실행.
	//		HairCheck();
	//		return;
	//	};

	GameEngineInput::AddInputObject(this);
}

void HouseUnit::LevelStart(GameEngineLevel* _NextLevel)
{

}

void HouseUnit::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

void HouseUnit::HairCheck()
{

	if (true == IsSleep)
	{
		HairRenderer->Transform.SetWorldRotation({ 0.0f, 0.0f, 90.0f });
		HairRenderer->Transform.SetLocalPosition({ -25.0f, 100.0f, HairRenderer->Transform.GetLocalPosition().Z });
		return;
	}

	HairRenderer->Transform.SetWorldRotation(float4::ZERO);


	// 헤어위치 잡는 작업.
	GameEngineColor Test = GameEngineColor::RED;
	float4 ColorCheck = CheckPos;

	while (GameEngineColor::BLACK != Test)
	{

		Test = BodyRenderer->GetCurSprite().Texture->GetColor(ColorCheck, GameEngineColor::RED);
		ColorCheck.Y += 1.0f;

	}

	float ResultY = (62.0f - ColorCheck.Y) * 3.0f;
	HairRenderer->Transform.SetLocalPosition({ 0.0f, ResultY, HairRenderer->Transform.GetLocalPosition().Z });


}

void HouseUnit::Update(float _Delta)
{
	HairCheck();

	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A', this))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
		BodyRenderer->ChangeAnimation("Run");
	}

	if (GameEngineInput::IsPress('D', this))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
		BodyRenderer->ChangeAnimation("WHat");
	}

	if (GameEngineInput::IsPress('W', this))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
		BodyRenderer->ChangeAnimation("Eat");
	}

	if (GameEngineInput::IsPress('S', this))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q', this))
	{
		IsSleep = false;
		BodyRenderer->ChangeAnimation("Idle");
	}

	if (GameEngineInput::IsPress('E', this))
	{
		IsSleep = true;
		BodyRenderer->ChangeAnimation("Sleep");
	}
}