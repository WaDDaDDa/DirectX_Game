#include "PreCompile.h"
#include "SwordmanUltEffect.h"
#include "GameUnit.h"


SwordmanUltEffect::SwordmanUltEffect()
{

}

SwordmanUltEffect::~SwordmanUltEffect()
{

}

void SwordmanUltEffect::Start()
{

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	Renderer->CreateAnimation("SwordmanUltEffect", "SwordmanEffect", 0.1f, 22, 28, false);
	Renderer->CreateAnimation("SwordmanUltBlack", "SwordmanEffect", 0.1f, 23, 23, false);
	Renderer->ChangeAnimation("SwordmanUltEffect");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);
	Renderer->SetPivotType(PivotType::Left);

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// 궁극기 대미지
			float Att = Unit->GetUnitAttack();
			Att *= 5.0f;
			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
						}
					});
			}
			else if (TeamType::Red == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
						}
					});
			}
		};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			
		};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			
		};
}

void SwordmanUltEffect::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void SwordmanUltEffect::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}


void SwordmanUltEffect::Update(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Death();
	}

	//이벤트 사용.
	if (TeamType::Blue == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
	else if (TeamType::Red == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
}