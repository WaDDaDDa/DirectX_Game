#include "PreCompile.h"
#include "PriestUlt.h"
#include "PriestHealEffect.h"


PriestUlt::PriestUlt()
{

}

PriestUlt::~PriestUlt()
{

}

void PriestUlt::Start()
{
	AttRangeRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	AttRangeRenderer->CreateAnimation("PriestUltEffect_AttRange", "PriestEffect", 0.1f, 29, 29, false);
	AttRangeRenderer->ChangeAnimation("PriestUltEffect_AttRange");
	AttRangeRenderer->SetImageScale({ 0.0f, 0.0f });

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			Att = Unit->GetUnitAttack();
			Att *= 0.3f;

			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->HealHP(Att);
						}
						AttInter = 0.2f;
					});
			}
			else if (TeamType::Red == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->HealHP(Att);
						}
						AttInter = 0.2f;
					});
			}
		};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

}

void PriestUlt::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void PriestUlt::Update(float _Delta)
{
	AttInter -= _Delta;
	EffectInter -= _Delta;
	RangeValue += _Delta;

	if (RangeValue >= 1.0f)
	{
		RangeValue = 1.0f;
	}

	{
		float Test = std::lerp(0.0f, Scale.X, RangeValue);

		AttRangeRenderer->SetImageScale({ Test , Test });

	}

	if (0.0f >= EffectInter)
	{
		GameEngineRandom NewRandom;

		static long long RandSeed = reinterpret_cast<long long>(this);
		RandSeed++;
		NewRandom.SetSeed(RandSeed);

		std::shared_ptr<PriestHealEffect> HealEffect = GetLevel()->CreateActor<PriestHealEffect>();
		float RandX = NewRandom.RandomFloat(-200.0f, 200.0f);
		float RandY = NewRandom.RandomFloat(-200.0f, 200.0f);
		HealEffect->Transform.SetWorldPosition(Transform.GetWorldPosition());
		HealEffect->Transform.AddLocalPosition({ RandX , RandY });
		EffectInter = 0.05f;
	}

	if (LifeTime <= GetLiveTime())
	{
		Death();
		return;
	}

	//이벤트 사용.
	if (TeamType::Blue == Unit->MyTeam && 0.0f >= AttInter)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
	else if (TeamType::Red == Unit->MyTeam && 0.0f >= AttInter)
	{
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
}