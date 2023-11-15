#include "PreCompile.h"
#include "Audience.h"


Audience::Audience()
{

}

Audience::~Audience()
{

}

void Audience::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 200.0f });

	long long RandSeed = reinterpret_cast<long long>(this);
	RandSeed++;
	Rand.SetSeed(RandSeed);

	float PosX = Rand.RandomFloat(-600.0f, 600.0f);
	float PosY = Rand.RandomFloat(-400.0f, -250.0f);
	float PosZ = PosY / 100.0f;

	Transform.AddLocalPosition({ PosX , PosY , PosZ});


	HairRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	int HairNum = Rand.RandomInt(0, 9);
	HairRenderer->SetSprite("AudienceHair", HairNum);
	HairRenderer->AutoSpriteSizeOn();
	HairRenderer->SetAutoScaleRatio(2.0f);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f });

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	BodyRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->CreateAnimation("Idle0", "Audience", 0.1f, 0, 4);
	BodyRenderer->CreateAnimation("Idle1", "Audience", 0.1f, 5, 8);
	BodyRenderer->CreateAnimation("Idle2", "Audience", 0.1f, 9, 14);
	BodyRenderer->CreateAnimation("Idle3", "Audience", 0.1f, 15, 22);
	BodyRenderer->CreateAnimation("Idle4", "Audience", 0.1f, 23, 27);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(2.0f);

	// 프레임펑션
	FrameFunction = [=](const SpriteData& CurSprite, int _SpriteIndex)
		{
			// 처음한번 실행.
			HairCheck(CurSprite);
			return;
		};

	BodyRenderer->SetFrameChangeFunctionAll(FrameFunction);

	BodyRenderer->ChangeAnimation("Idle" + std::to_string(Rand.RandomInt(0,4)));
}

void Audience::HairCheck(const SpriteData& _CurSprite)
{
	// 헤어위치 잡는 작업.
	GameEngineColor CurColor = GameEngineColor::RED;
	float4 ColorCheckPos = CheckPos;

	while (GameEngineColor::BLACK != CurColor)
	{

		CurColor = _CurSprite.Texture->GetColor(ColorCheckPos, GameEngineColor::RED);
		ColorCheckPos.Y += 1.0f;
	}

	float ResultY = (55.0f - ColorCheckPos.Y) * 2.0f;
	HairRenderer->Transform.SetLocalPosition({ 0.0f, ResultY, HairRenderer->Transform.GetLocalPosition().Z });

}

void Audience::Update(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		BodyRenderer->ChangeAnimation("Idle" + std::to_string(Rand.RandomInt(0, 4)));
		return;
	}
}

void Audience::LevelStart(GameEngineLevel* _NextLevel)
{

}

void Audience::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}