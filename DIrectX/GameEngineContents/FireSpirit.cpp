#include "PreCompile.h"
#include "FireSpirit.h"
#include "FireSpiritAttack.h"


FireSpirit::FireSpirit()
{

}

FireSpirit::~FireSpirit()
{

}

void FireSpirit::Start()
{

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	Renderer->CreateAnimation("FireSpirit_Spwan", "FireSpiritAni", 0.1f, 0, 6, false);
	Renderer->CreateAnimation("FireSpirit_Idle", "FireSpiritAni", 0.2f, 7, 9, true);
	Renderer->CreateAnimation("FireSpirit_Attack1", "FireSpiritAni", 0.2f, 10, 11, false);
	Renderer->CreateAnimation("FireSpirit_Attack2", "FireSpiritAni", 0.2f, 12, 13, false);
	Renderer->CreateAnimation("FireSpirit_Die", "FireSpiritAni", 0.2f, 15, 19, false);
	Renderer->ChangeAnimation("FireSpirit_Spwan");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);

	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	EffectRenderer->CreateAnimation("FireSpiritEffect_Spwan", "FireSpiritEffect", 0.1f, 0, 7, false);
	EffectRenderer->ChangeAnimation("FireSpiritEffect_Spwan");
	EffectRenderer->AutoSpriteSizeOn();
	EffectRenderer->SetAutoScaleRatio(1.3f);

	AttRangeRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	AttRangeRenderer->CreateAnimation("FireSpiritEffect_AttRange", "FireSpiritEffect", 0.1f, 32, 32, false);
	AttRangeRenderer->ChangeAnimation("FireSpiritEffect_AttRange");
	AttRangeRenderer->SetImageScale({0.0f, 0.0f});

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			Att = Unit->GetUnitAttack();
			Att *= 1.0f;

			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							// 투사체 발사
							GetLevel()->CreateActor<FireSpiritAttack>()->Init(GetDynamic_Cast_This<FireSpirit>(), _Collision[i]->GetActor()->GetDynamic_Cast_This<GameUnit>());
						}
						AttCount = 0;
					});
			}
			else if (TeamType::Red == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							// 투사체 발사
							GetLevel()->CreateActor<FireSpiritAttack>()->Init(GetDynamic_Cast_This<FireSpirit>(), _Collision[i]->GetActor()->GetDynamic_Cast_This<GameUnit>());

						}
						AttCount = 0;

					});
			}
		};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

	ChangeState(FireSpiritState::Spwan);
}

void FireSpirit::Update(float _Delta)
{
	AttackValue += _Delta;
	LifeTime -= _Delta;

	StateUpdate(_Delta);

	if (0.0f >= LifeTime)
	{
		ChangeState(FireSpiritState::Die);
		return;
	}

}

void FireSpirit::StateUpdate(float _Delta)
{
	switch (State)
	{
	case FireSpiritState::Spwan:
		return SpwanUpdate(_Delta);
	case FireSpiritState::Idle:
		return IdleUpdate(_Delta);
	case FireSpiritState::Attack1:
		return Attack1Update(_Delta);
	case FireSpiritState::Attack2:
		return Attack2Update(_Delta);
	case FireSpiritState::Die:
		return DieUpdate(_Delta);
	default:
		break;
	}
}

void FireSpirit::ChangeState(FireSpiritState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case FireSpiritState::Spwan:
			SpwanStart();
			break;
		case FireSpiritState::Idle:
			IdleStart();
			break;
		case FireSpiritState::Attack1:
			Attack1Start();
			break;
		case FireSpiritState::Attack2:
			Attack2Start();
			break;
		case FireSpiritState::Die:
			DieStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void FireSpirit::SpwanStart()
{
	Renderer->ChangeAnimation("FireSpirit_Spwan");
}

void FireSpirit::SpwanUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(FireSpiritState::Idle);
		return;
	}

	RangeValue += _Delta * 2.0f;

	if (RangeValue >= 1.0f)
	{
		RangeValue = 1.0f;
	}

	{
		float Test = std::lerp(0.0f, Scale.X, RangeValue);

		AttRangeRenderer->SetImageScale({ Test , Test });

	}
}

void FireSpirit::IdleStart()
{
	Renderer->ChangeAnimation("FireSpirit_Idle");
}

void FireSpirit::IdleUpdate(float _Delta)
{
	if (TeamType::Blue == MyTeam)
	{
		// 공격
		if (Col->Collision(CollisionOrder::RedTeamBody) && AttackSpeed <= AttackValue)
		{
			ChangeState(FireSpiritState::Attack1);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// 공격
		if (Col->Collision(CollisionOrder::BlueTeamBody) && AttackSpeed <= AttackValue)
		{
			ChangeState(FireSpiritState::Attack1);
			return;
		}
	}
}

void FireSpirit::Attack1Start()
{
	Renderer->ChangeAnimation("FireSpirit_Attack1");
	AttCount = 1;
	AttackValue = 0.0f;
}

void FireSpirit::Attack1Update(float _Delta)
{
	ChangeDir();

	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(FireSpiritState::Attack2);
		return;
	}
}

void FireSpirit::Attack2Start()
{
	Renderer->ChangeAnimation("FireSpirit_Attack2");

}

void FireSpirit::Attack2Update(float _Delta)
{
	ChangeDir();

	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(FireSpiritState::Idle);
		return;
	}

	//이벤트 사용.
	if (TeamType::Blue == MyTeam && 1 == AttCount)
	{
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
	else if (TeamType::Red == MyTeam && 1 == AttCount)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
}

void FireSpirit::DieStart()
{
	Renderer->ChangeAnimation("FireSpirit_Die");
	RangeValue = 0.0f;
}

void FireSpirit::DieUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
		return;
	}

	RangeValue += _Delta * 2.0f;

	if (RangeValue >= 1.0f)
	{
		RangeValue = 1.0f;
	}

	{
		float Test = std::lerp(Scale.X, 0.0f, RangeValue);

		AttRangeRenderer->SetImageScale({ Test , Test });

	}

}
