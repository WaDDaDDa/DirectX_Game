#include "PreCompile.h"
#include "MonkUlt.h"
#include "MonkShield.h"

MonkUlt::MonkUlt()
{

}

MonkUlt::~MonkUlt()
{

}

void MonkUlt::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Renderer->CreateAnimation("MonkUltEffect", "MonkEffect", 0.1f, 9, 16, false);
	Renderer->CreateAnimation("MonkUltBlack", "MonkEffect", 0.1f, 0, 0, false);
	Renderer->ChangeAnimation("MonkUltEffect");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			if (TeamType::Blue == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							GetLevel()->CreateActor<MonkShield>()->SetUnit(_Collision[i]->GetActor()->GetDynamic_Cast_This<GameUnit>());

						}
					});
			}
			else if (TeamType::Red == Unit->MyTeam)
			{
				Col->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
					{
						for (size_t i = 0; i < _Collision.size(); i++)
						{
							GetLevel()->CreateActor<MonkShield>()->SetUnit(_Collision[i]->GetActor()->GetDynamic_Cast_This<GameUnit>());
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

void MonkUlt::Update(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
	}

	//이벤트 사용.
	if (TeamType::Blue == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}
	else if (TeamType::Red == Unit->MyTeam)
	{
		Col->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
}