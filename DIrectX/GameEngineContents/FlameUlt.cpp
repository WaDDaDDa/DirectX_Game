#include "PreCompile.h"
#include "FlameUlt.h"
#include "FlameEffect.h"


FlameUlt::FlameUlt()
{

}

FlameUlt::~FlameUlt()
{

}

void FlameUlt::Start()
{

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			Att = Unit->GetUnitAttack();
			Att *= 0.5f;

			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(Att);
						}
						AttInter = 0.5f;
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
						AttInter = 0.5f;

					});
			}
		};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

}

void FlameUlt::Update(float _Delta)
{
	AttInter -= _Delta;
	EffectInter -= _Delta;
	//for (size_t i = 0; i < 20; i++)
	//{
	//	GameEngineRandom NewRandom;
	//	float RandX = NewRandom.RandomFloat(-200.0f, 200.0f);
	//	float RandY = NewRandom.RandomFloat(-200.0f, 200.0f);
	//	std::shared_ptr<FlameEffect> Flame = GetLevel()->CreateActor<FlameEffect>();
	//	Flame->Transform.SetWorldPosition(Transform.GetWorldPosition());
	//	Flame->Transform.AddLocalPosition({ RandX , RandY});
	//}

	if (0.0f >= EffectInter)
	{
		GameEngineRandom NewRandom;

		static long long RandSeed = reinterpret_cast<long long>(this);
		RandSeed++;
		NewRandom.SetSeed(RandSeed);

		std::shared_ptr<FlameEffect> Flame = GetLevel()->CreateActor<FlameEffect>();
		float RandX = NewRandom.RandomFloat(-200.0f, 200.0f);
		float RandY = NewRandom.RandomFloat(-200.0f, 200.0f);
		Flame->Transform.SetWorldPosition(Transform.GetWorldPosition());
		Flame->Transform.AddLocalPosition({ RandX , RandY });
		EffectInter = 0.05f;
	}

	if (LifeTime <= GetLiveTime())
	{
		Death();
	}

	//이벤트 사용.
	if (TeamType::Blue == Unit->MyTeam && 0.0f >= AttInter)
	{
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
	else if (TeamType::Red == Unit->MyTeam && 0.0f >= AttInter)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
}