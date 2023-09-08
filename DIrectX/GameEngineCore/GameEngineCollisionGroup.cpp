#include "PreCompile.h"
#include "GameEngineCollisionGroup.h"
#include "GameEngineCollision.h"

GameEngineCollisionGroup::GameEngineCollisionGroup() 
{
}

GameEngineCollisionGroup::~GameEngineCollisionGroup() 
{
}



void GameEngineCollisionGroup::AllReleaseCheck()
{
	std::list<std::shared_ptr<class GameEngineCollision>>::iterator StartIter = Collisions.begin();
	std::list<std::shared_ptr<class GameEngineCollision>>::iterator EndIter = Collisions.end();

	for ( ; StartIter != EndIter; )
	{
		if (false == (*StartIter)->IsDeath())
		{
			++StartIter;
			continue;
		}

		StartIter = Collisions.erase(StartIter);
	}
}



bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision)
{
	for (std::shared_ptr<class GameEngineCollision> Collsion : Collisions)
	{
		if (Collsion == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData , Collsion->Transform.ColData, _Collision->GetCollisionType(), Collsion->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos)
{
	CollisionData Data = _Collision->Transform.ColData;

	Data.OBB.Center.x += _NextPos.X;
	Data.OBB.Center.y += _NextPos.Y;
	Data.OBB.Center.z += _NextPos.Z;

	for (std::shared_ptr<class GameEngineCollision> Collsion : Collisions)
	{
		if (Collsion == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ Data , Collsion->Transform.ColData, _Collision->GetCollisionType(), Collsion->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	// static ���������� �����
	// std::list Nodes delete�� �Ѵ�.
	// �����峪 �̷��Ϳ��� ����������
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (std::shared_ptr<class GameEngineCollision> Collsion : Collisions)
	{
		if (Collsion == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData , Collsion->Transform.ColData, _Collision->GetCollisionType(), Collsion->GetCollisionType() }))
		{
			ResultCollision.push_back(Collsion);
		}
	}

	if (0 != ResultCollision.size())
	{
		_Function(ResultCollision);
	}

	return false;

}


bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	CollisionData Data = _Collision->Transform.ColData;

	Data.OBB.Center.x += _NextPos.X;
	Data.OBB.Center.y += _NextPos.Y;
	Data.OBB.Center.z += _NextPos.Z;

	for (std::shared_ptr<class GameEngineCollision> Collsion : Collisions)
	{
		if (Collsion == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ Data , Collsion->Transform.ColData, _Collision->GetCollisionType(), Collsion->GetCollisionType() }))
		{
			ResultCollision.push_back(Collsion);
		}
	}

	if (0 != ResultCollision.size())
	{
		_Function(ResultCollision);
	}

	return false;
}


bool GameEngineCollisionGroup::CollisionEvent(std::shared_ptr<GameEngineCollision> _Collision, const EventParameter& _Event)
{
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (std::shared_ptr<class GameEngineCollision> Collsion : Collisions)
	{
		if (Collsion == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData , Collsion->Transform.ColData, _Collision->GetCollisionType(), Collsion->GetCollisionType() }))
		{
			ResultCollision.push_back(Collsion);
			continue;
		}

		GameEngineCollision* Other = Collsion.get();

		// �ִ� �浹�� ���� ���߳�.
		// �׷��� �浹�� �ߴ����� �ֳ�?   ===>  �浹���̴ٰ� �浹���.
		if (true == _Collision->Others.contains(Other))
		{
			if (_Event.Exit)
			{
				_Event.Exit(Other);
				Other->Others.erase(Other);
				_Collision->Others.erase(Other);
			}
		}
	}

	if (0 != ResultCollision.size())
	{
		// ResultCollision ���� �浹�� �ֵ�.

		for (size_t i = 0; i < ResultCollision.size(); i++)
		{
			GameEngineCollision* Other = ResultCollision[i].get();
			// ���� �浹�� ó���ߴ�. ===> �浹 ù����.
			if (false == _Collision->Others.contains(Other))
			{
				if (_Event.Enter)
				{
					_Event.Enter(Other);
					Other->Others.insert(Other);
					_Collision->Others.insert(Other);
				}
			}
			else  // ���� �浹�� ó���Ѱ� �ƴϰ� �浹�ߴ�.  ==> �浹���̴�.
			{
				if (_Event.Stay)
				{
					_Event.Stay(Other);
				}
			}
		}
	}

	return false;
}

void GameEngineCollisionGroup::PushCollision(std::shared_ptr<GameEngineCollision> _Collision)
{
	if (nullptr == _Collision)
	{
		MsgBoxAssert("�������� �ʴ� �ݸ����� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	Collisions.push_back(_Collision);
}