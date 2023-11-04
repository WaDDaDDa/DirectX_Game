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

	FrameFunction = [=](const SpriteData& CurSprite, int _SpriteIndex)
		{
			// ó���ѹ� ����.
			HairCheck(CurSprite);
			return;
		};

	GameEngineInput::AddInputObject(this);
}

void HouseUnit::LevelStart(GameEngineLevel* _NextLevel)
{

}

void HouseUnit::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

void HouseUnit::HairCheck(const SpriteData& _CurSprite)
{
	HairRenderer->Transform.SetWorldRotation(float4::ZERO);

	if (true == IsSleep)
	{
		HairRenderer->Transform.SetWorldRotation({ 0.0f, 0.0f, 90.0f });
		HairRenderer->Transform.SetLocalPosition({ -25.0f, 100.0f, HairRenderer->Transform.GetLocalPosition().Z });
		return;
	}

	if (true == IsCpuPlay)
	{
		HairRenderer->Transform.SetLocalPosition({ -5.0f, 120.0f, HairRenderer->Transform.GetLocalPosition().Z });
		return;
	}

	// �����ġ ��� �۾�.
	GameEngineColor CurColor = GameEngineColor::RED;
	float4 ColorCheckPos = CheckPos;

	while (GameEngineColor::BLACK != CurColor)
	{

		CurColor = _CurSprite.Texture->GetColor(ColorCheckPos, GameEngineColor::RED);
		ColorCheckPos.Y += 1.0f;
	}

	float ResultY = (62.0f - ColorCheckPos.Y) * 3.0f;
	HairRenderer->Transform.SetLocalPosition({ 0.0f, ResultY, HairRenderer->Transform.GetLocalPosition().Z });


}

void HouseUnit::Update(float _Delta)
{
	//	HairCheck();

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