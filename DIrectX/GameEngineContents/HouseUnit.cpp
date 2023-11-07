#include "PreCompile.h"
#include "HouseUnit.h"
#include "House.h"

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
	int Floor = Rand.RandomInt(1,1);
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

	ShowerRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	ShowerRenderer->Transform.AddLocalPosition({ 0.0f, 70.0f, -static_cast<float>(ContentsOrder::FrontEffect) });
	ShowerRenderer->SetPivotType(PivotType::Bottom);
	ShowerRenderer->AutoSpriteSizeOn();
	ShowerRenderer->SetAutoScaleRatio(3.0f);
	ShowerRenderer->CreateAnimation("ShowerOn", "Shower", 0.1f ,1, 7, false);
	ShowerRenderer->CreateAnimation("Showering", "Shower", 0.1f ,8, 11, true);
	ShowerRenderer->CreateAnimation("ShowerEnd", "Shower", 0.1f ,12, 19, false);
	ShowerRenderer->CreateAnimation("ShowerOff", "Shower", 0.1f ,0, 0, false);
	ShowerRenderer->SetEndEvent("ShowerOn", [=](GameEngineRenderer* _Renderer) {ShowerRenderer->ChangeAnimation("Showering"); });
	ShowerRenderer->Off();

	// ���������
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
	// ������Ʈ Idle
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
			if (1.0f <= State.GetStateTime())
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

			Transform.AddLocalPosition({ MoveDir * MoveSpeed * _Delta});

		},
		.End =
		[=](class GameEngineState* _Parent)
		{

		},
		});

	// ToFurniture
	State.CreateState(HouseUnitEnum::ToFurniture,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			BodyRenderer->ChangeAnimation("Run");

			float4 XDir = House::FirstFloorFurniture[FurnitureNum]->Pos.X - Transform.GetWorldPosition().X;
			XDir.Normalize();
			MoveDir = XDir.X;

		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{
			DirCheck();

			Transform.AddLocalPosition({ MoveDir * MoveSpeed * _Delta });

			if (Arrive(House::FirstFloorFurniture[FurnitureNum]))
			{
				State.ChangeState(PrevState);
				return;
			}
		},
		.End =
		[=](class GameEngineState* _Parent)
		{
			MoveDir = 1.0f;
			FlipReset();
		},
		});

	// ToStairs
	State.CreateState(HouseUnitEnum::ToStairs,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			BodyRenderer->ChangeAnimation("Run");

			// ���� 1���̸� 1�����ִ� ��� ���������� �����Ѵ�.
			if (true == IsFirstFloor)
			{
				float4 XDir = FirstStairsPos.X - Transform.GetWorldPosition().X;
				XDir.Normalize();
				MoveDir = XDir.X;
			}
			else if (true == IsScendFloor)
			{
				float4 XDir = ScendStairsPos.X - Transform.GetWorldPosition().X;
				XDir.Normalize();
				MoveDir = XDir.X;
			}
		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{
			DirCheck();
			
			Transform.AddLocalPosition({ MoveDir * MoveSpeed * _Delta});

			if (Arrive(FirstStairsPos) && true == IsFirstFloor)
			{
				State.ChangeState(HouseUnitEnum::UseStairs);
				return;
			}
			else if (Arrive(ScendStairsPos) && true == IsScendFloor)
			{
				State.ChangeState(HouseUnitEnum::UseStairs);
				return;
			}

		},
		.End =
		[=](class GameEngineState* _Parent)
		{
			MoveDir = 1.0f;
			FlipReset();
		},
		});

	// UseStairs
	State.CreateState(HouseUnitEnum::UseStairs,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			BodyRenderer->ChangeAnimation("Run");

			if (true == IsFirstFloor)
			{
				float4 XDir = ScendStairsPos - FirstStairsPos;
				XDir.Normalize();
				MoveDir = XDir;
				IsFirstFloor = false;
				IsScendFloor = true;
			}
			else if (true == IsScendFloor)
			{
				float4 XDir = FirstStairsPos - ScendStairsPos;
				XDir.Normalize();
				MoveDir = XDir;
				IsFirstFloor = true;
				IsScendFloor = false;
			}
		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{
			DirCheck();

			Transform.AddLocalPosition({ MoveDir * MoveSpeed * _Delta});

			if (Arrive(FirstStairsPos) && true == IsFirstFloor)
			{
				State.ChangeState(HouseUnitEnum::ToFurniture);
				return;
			}
			else if (Arrive(ScendStairsPos) && true == IsScendFloor)
			{
				State.ChangeState(HouseUnitEnum::ToFurniture);
				return;
			}

		},
		.End =
		[=](class GameEngineState* _Parent)
		{
			MoveDir = 1.0f;
			FlipReset();
			FloorCheck();
		},
		});

	// PlayGame
	State.CreateState(HouseUnitEnum::PlayGame,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			IsCpuPlay = true;
			BodyRenderer->ChangeAnimation("Cpu");
			GameEngineRandom Rand;
			FurnitureNum = Rand.RandomInt(0, 5);
		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{
			// �̿��� ������ ĳ������ ������ �����ʴٸ� ����� �̿��Ϸ� �����Ѵ�.
			if (IsFirstFloor != House::FirstFloorFurniture[FurnitureNum]->IsFirstFloor)
			{
				PrevState = HouseUnitEnum::PlayGame;
				State.ChangeState(HouseUnitEnum::ToStairs);
				return;
			}
			else if (IsFirstFloor == House::FirstFloorFurniture[FurnitureNum]->IsFirstFloor && false == Arrive(House::FirstFloorFurniture[FurnitureNum]))
			{
				PrevState = HouseUnitEnum::PlayGame;
				State.ChangeState(HouseUnitEnum::ToFurniture);
				return;
			}

			if (2.0f <= State.GetStateTime())
			{
				State.ChangeState(HouseUnitEnum::Idle);
				return;
			}

		},
		.End =
		[=](class GameEngineState* _Parent)
		{
			Reset();
		},
		});

	// Toilet
	State.CreateState(HouseUnitEnum::Toilet,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			BodyRenderer->ChangeAnimation("Toilet");
			FurnitureNum = 6;

			// �̿��� ������ ĳ������ ������ �����ʴٸ� ����� �̿��Ϸ� �����Ѵ�.
			if (IsFirstFloor != House::FirstFloorFurniture[FurnitureNum]->IsFirstFloor)
			{
				PrevState = HouseUnitEnum::Toilet;
				State.ChangeState(HouseUnitEnum::ToStairs);
				return;
			}
			else if (IsFirstFloor == House::FirstFloorFurniture[FurnitureNum]->IsFirstFloor && false == Arrive(House::FirstFloorFurniture[FurnitureNum]))
			{
				PrevState = HouseUnitEnum::Toilet;
				State.ChangeState(HouseUnitEnum::ToFurniture);
				return;
			}
		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{

			Transform.SetLocalPositionX(House::FirstFloorFurniture[FurnitureNum]->Pos.X - 20.0f );

			if (3.0f <= State.GetStateTime())
			{
				State.ChangeState(HouseUnitEnum::HandWash);
				return;
			}

		},
		.End =
		[=](class GameEngineState* _Parent)
		{

		},
		});

	// HandWash
	State.CreateState(HouseUnitEnum::HandWash,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			BodyRenderer->ChangeAnimation("HandWash");
			//House::FirstFloorFurniture[FurnitureNum]->Renderer->ChangeAnimation("Use");
			Transform.SetLocalPositionX(House::FirstFloorFurniture[FurnitureNum]->Pos.X + 10.0f);
		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{
			if (1.0f <= State.GetStateTime())
			{
				State.ChangeState(HouseUnitEnum::Idle);
				return;
			}

		},
		.End =
		[=](class GameEngineState* _Parent)
		{
			//House::FirstFloorFurniture[FurnitureNum]->Renderer->ChangeAnimation("Idle");
		},
		});

	// Shower
	State.CreateState(HouseUnitEnum::Shower,
		{
		.Start =
		[=](class GameEngineState* _Parent)
		{
			BodyRenderer->ChangeAnimation("Idle");
			ShowerRenderer->On();
			ShowerRenderer->ChangeAnimation("ShowerOn");
			FurnitureNum = 7;

			// �̿��� ������ ĳ������ ������ �����ʴٸ� ����� �̿��Ϸ� �����Ѵ�.
			if (IsFirstFloor != House::FirstFloorFurniture[FurnitureNum]->IsFirstFloor)
			{
				PrevState = HouseUnitEnum::Shower;
				State.ChangeState(HouseUnitEnum::ToStairs);
				return;
			}
			else if (IsFirstFloor == House::FirstFloorFurniture[FurnitureNum]->IsFirstFloor && false == Arrive(House::FirstFloorFurniture[FurnitureNum]))
			{
				PrevState = HouseUnitEnum::Shower;
				State.ChangeState(HouseUnitEnum::ToFurniture);
				return;
			}
		},
		.Stay =
		[=](float _Delta, class GameEngineState* _Parent)
		{
			if (ShowerRenderer->CurAnimation() == ShowerRenderer->FindAnimation("Showering") && 2.0f <= State.GetStateTime())
			{
				ShowerRenderer->ChangeAnimation("ShowerEnd");
				return;
			}

			if (ShowerRenderer->CurAnimation() == ShowerRenderer->FindAnimation("ShowerEnd") && true == ShowerRenderer->IsCurAnimationEnd())
			{
				State.ChangeState(HouseUnitEnum::Idle);
				return;
			}

		},
		.End =
		[=](class GameEngineState* _Parent)
		{
			ShowerRenderer->Off();
			ShowerRenderer->ChangeAnimation("ShowerOff");
		},
		});


	State.ChangeState(HouseUnitEnum::Idle);
	FloorCheck();
}

void HouseUnit::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

bool HouseUnit::Arrive(const std::shared_ptr<class Furniture>& _Furniture)
{
	float Test = _Furniture->Pos.X - Transform.GetWorldPosition().X;
	if (Test <= 1.0f && Test >= -1.0f)
	{
		return true;
	}

	return false;
}

bool HouseUnit::Arrive(float4 _Pos)
{
	float Test = _Pos.X - Transform.GetWorldPosition().X;
	if (Test <= 1.0f && Test >= -1.0f)
	{
		return true;
	}

	return false;
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
	State.Update(_Delta);

	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A', this))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
		BodyRenderer->ChangeAnimation("HandWash");
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

	if (GameEngineInput::IsDown('S', this))
	{
		State.ChangeState(HouseUnitEnum::Shower);
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