#include "PreCompile.h"
#include "BanPickCard.h"

BanPickCard::BanPickCard()
{

}

BanPickCard::~BanPickCard()
{

}

void BanPickCard::Start()
{
	{
		// 싱글 스프라이트 로드
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Stadium\\Unit_Icon");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		// 초상화 로드
		GameEngineSprite::CreateSingle("Archer_Icon.png");
		GameEngineSprite::CreateSingle("Knight_Icon.png");
		GameEngineSprite::CreateSingle("Monk_Icon.png");
		GameEngineSprite::CreateSingle("Fighter_Icon.png");
		GameEngineSprite::CreateSingle("Ninja_Icon.png");
		GameEngineSprite::CreateSingle("Priest_Icon.png");
		GameEngineSprite::CreateSingle("Pyromancer_Icon.png");
		GameEngineSprite::CreateSingle("Pythoness_Icon.png");
		GameEngineSprite::CreateSingle("Swordman_Icon.png");
	}

	Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	// Card 배경
	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("BanPickCard_Null", "BanPick", 0.1f, 15, 15, false);
	Renderer->CreateAnimation("BanPickCard_Blue", "BanPick", 0.1f, 9, 9, false);
	Renderer->CreateAnimation("BanPickCard_Red", "BanPick", 0.1f, 10, 10, false);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	Renderer->ChangeAnimation("BanPickCard_Null");

	// Unit이미지
	UnitImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitImage->CreateAnimation("Archer_Idle", "ArcherAni", 0.2f, 0, 0);
	UnitImage->CreateAnimation("Archer_Stay", "ArcherAni", 0.2f, 0, 4);
	UnitImage->AutoSpriteSizeOn();
	UnitImage->SetAutoScaleRatio(2.0f);
	UnitImage->Transform.AddLocalPosition(UnitImagePos);
	UnitImage->SetPivotType(PivotType::Bottom);
	UnitImage->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitImage->ChangeAnimation("Archer_Idle");

	ChangeState(BanPickState::Idle);
}

void BanPickCard::LevelStart(GameEngineLevel* _PrevLevel)
{

}


void BanPickCard::Init()
{

}

void BanPickCard::Update(float _Delta)
{
	StateUpdate(_Delta);
}


void BanPickCard::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BanPickState::Idle:
		return IdleUpdate(_Delta);
	case BanPickState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void BanPickCard::ChangeState(BanPickState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BanPickState::Idle:
			IdleStart();
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

void BanPickCard::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BanPickCard::MaxStart()
{

}

void BanPickCard::MaxUpdate(float _Delta)
{

}

void BanPickCard::IdleStart()
{

}

void BanPickCard::IdleUpdate(float _Delta)
{

}

