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
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 200.0f });

	GameEngineRandom Rand;
	int Floor = Rand.RandomInt(0, 1);
	if (0 == Floor)
	{
		IsFirstFloor = true;
	}
	else
	{
		IsScendFloor = true;
	}

	FloorCheck();

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	BodyRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	BodyRenderer->SetPivotType(PivotType::Bottom);

	HairRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Hair);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Hair) });
	//HairRenderer->SetPivotType(PivotType::Bottom);

	// 프레임펑션
	FrameFunction = [=](const SpriteData& CurSprite, int _SpriteIndex)
		{
			// 처음한번 실행.
			HairCheck(CurSprite);
			return;
		};


	GameEngineInput::AddInputObject(this);
}

void HouseUnit::LevelStart(GameEngineLevel* _NextLevel)
{


	// 스테이트 Idle
	State.CreateState(HouseUnitEnum::Idle,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			Reset();
			BodyRenderer->ChangeAnimation("Idle");
		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{
			if (3.0f <= State.GetStateTime())
			{
				State.ChangeState(HouseUnitEnum::Run);
				return;
			}

		},
		.End =
		[=](class GameEngineState* _Parent)
		{

		},
		});
	// Run
	State.CreateState(HouseUnitEnum::Run,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			BodyRenderer->ChangeAnimation("Run");
		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{
			float Xpos = Transform.GetLocalPosition().X;
			if (840.0f <= Xpos)
			{
				BodyRenderer->LeftFlip();
				HairRenderer->LeftFlip();
				Transform.SetLocalPositionX(839.9f);
				MoveDir *= -1.0f;
			}
			else if (445.0f >= Xpos)
			{
				BodyRenderer->RightFlip();
				HairRenderer->RightFlip();
				Transform.SetLocalPositionX(445.1f);
				MoveDir *= -1.0f;
			}

			Transform.AddLocalPosition({ MoveDir * _Delta});

		},
		.End =
		[=](class GameEngineState* _Parent)
		{

		},
		});


	State.ChangeState(HouseUnitEnum::Idle);

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

	// 헤어위치 잡는 작업.
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
	State.Update(_Delta);
	FloorCheck();

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