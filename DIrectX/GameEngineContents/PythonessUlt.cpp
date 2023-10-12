#include "PreCompile.h"
#include "PythonessUlt.h"
#include "PythonessAttack.h"
#include "PythonessHeal.h"

PythonessUlt::PythonessUlt()
{

}

PythonessUlt::~PythonessUlt()
{

}

void PythonessUlt::Start()
{

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	Renderer->CreateAnimation("PythonessUlt_Spwan", "PythonessUltEffect", 0.1f, 0, 8, false);
	Renderer->CreateAnimation("PythonessUlt_Idle", "PythonessUltEffect", 0.2f, 9, 16, false);
	Renderer->CreateAnimation("PythonessUlt_Die", "PythonessUltEffect", 0.1f, 17, 28, false);
	Renderer->ChangeAnimation("PythonessUlt_Spwan");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			//Att = Unit->GetUnitAttack();
			//Att *= 1.0f;

			//if (TeamType::Blue == Unit->MyTeam)
			//{
			//	Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
			//		{
			//			for (size_t i = 0; i < _Collision.size(); i++)
			//			{
			//				// 투사체 발사
			//				GetLevel()->CreateActor<PythonessUltAttack>()->Init(GetDynamic_Cast_This<PythonessUlt>(), _Collision[i]->GetActor()->GetDynamic_Cast_This<GameUnit>());
			//			}
			//			AttCount = 0;
			//		});
			//}
			//else if (TeamType::Red == Unit->MyTeam)
			//{
			//	Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
			//		{
			//			for (size_t i = 0; i < _Collision.size(); i++)
			//			{
			//				// 투사체 발사
			//				GetLevel()->CreateActor<PythonessUltAttack>()->Init(GetDynamic_Cast_This<PythonessUlt>(), _Collision[i]->GetActor()->GetDynamic_Cast_This<GameUnit>());

			//			}
			//			AttCount = 0;

			//		});
			//}
		};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* _Col)
		{

		};

	ChangeState(PythonessUltState::Spwan);
}

void PythonessUlt::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}


void PythonessUlt::Update(float _Delta)
{
	AttackValue += _Delta;

	StateUpdate(_Delta);

}

void PythonessUlt::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PythonessUltState::Spwan:
		return SpwanUpdate(_Delta);
	case PythonessUltState::Idle:
		return IdleUpdate(_Delta);
	case PythonessUltState::Die:
		return DieUpdate(_Delta);
	default:
		break;
	}
}

void PythonessUlt::ChangeState(PythonessUltState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PythonessUltState::Spwan:
			SpwanStart();
			break;
		case PythonessUltState::Idle:
			IdleStart();
			break;
		case PythonessUltState::Die:
			DieStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void PythonessUlt::SpwanStart()
{
	Renderer->ChangeAnimation("PythonessUlt_Spwan");
}

void PythonessUlt::SpwanUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(PythonessUltState::Idle);
		return;
	}
}

void PythonessUlt::IdleStart()
{
	Renderer->ChangeAnimation("PythonessUlt_Idle");
}

void PythonessUlt::IdleUpdate(float _Delta)
{
	HealInter -= _Delta;
	UltInter -= _Delta;

	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(PythonessUltState::Die);
		return;
	}

	if (0.0f >= UltInter)
	{
		GetLevel()->CreateActor<PythonessAttack>()->InitUlt(GetDynamic_Cast_This<PythonessUlt>());
		Unit->NextAggroChange();
		UltInter = 0.1f;
	}

	if (0.0f >= HealInter)
	{
		GetLevel()->CreateActor<PythonessHeal>()->InitUlt(GetDynamic_Cast_This<PythonessUlt>());
		//Unit->NextAggroChange();
		HealInter = 0.1f;
	}


}

void PythonessUlt::DieStart()
{
	Renderer->ChangeAnimation("PythonessUlt_Die");
}

void PythonessUlt::DieUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
		return;
	}

}
